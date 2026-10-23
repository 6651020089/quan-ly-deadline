from flask import Flask, render_template, request, jsonify
import sqlite3, os, json, datetime, secrets
from flask import Response
app=Flask(__name__)
DB=os.environ.get('DB_PATH',os.path.join(os.path.dirname(__file__),'congviec.db'))
ADMIN_USER=os.environ.get('ADMIN_USER','admin')
ADMIN_PASSWORD=os.environ.get('ADMIN_PASSWORD','')
if os.environ.get('REQUIRE_AUTH')=='1' and not ADMIN_PASSWORD:
 raise RuntimeError('Set ADMIN_PASSWORD')
@app.before_request
def auth_guard():
 if request.path=='/health' or not ADMIN_PASSWORD:return None
 auth=request.authorization
 if not auth or not (secrets.compare_digest(auth.username or '',ADMIN_USER) and secrets.compare_digest(auth.password or '',ADMIN_PASSWORD)):
  return Response('Login required',401,{'WWW-Authenticate':'Basic realm="Study Planner"'})
 if request.method in ('POST','PATCH','DELETE','PUT'):
  origin=request.headers.get('Origin')
  if origin and origin.rstrip('/')!=request.host_url.rstrip('/'):
   return jsonify(error='Invalid origin'),403
@app.after_request
def secure(resp):
 resp.headers['X-Content-Type-Options']='nosniff'
 resp.headers['X-Frame-Options']='DENY'
 resp.headers['Cache-Control']='no-store'
 return resp

def connect():
 os.makedirs(os.path.dirname(os.path.abspath(DB)),exist_ok=True)
 c=sqlite3.connect(DB,timeout=30);c.row_factory=sqlite3.Row;return c
def init():
 with connect() as c:
  c.execute('CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, name TEXT NOT NULL, subject TEXT NOT NULL, deadline TEXT NOT NULL, priority INTEGER NOT NULL, completed INTEGER NOT NULL DEFAULT 0)')
  c.execute('CREATE TABLE IF NOT EXISTS history (id INTEGER PRIMARY KEY AUTOINCREMENT, action TEXT NOT NULL, before_json TEXT, after_json TEXT, created_at TEXT DEFAULT CURRENT_TIMESTAMP)')
def snapshot(c,id):
 r=c.execute('SELECT * FROM tasks WHERE id=?',(id,)).fetchone();return dict(r) if r else None
def log(c,action,before,after):
 c.execute('INSERT INTO history(action,before_json,after_json) VALUES(?,?,?)',(action,json.dumps(before,ensure_ascii=False) if before else None,json.dumps(after,ensure_ascii=False) if after else None))
@app.get('/health')
def health():return jsonify(status='ok')
@app.get('/')
def home():return render_template('index.html')
@app.get('/api/tasks')
def tasks():
 with connect() as c:return jsonify([dict(x) for x in c.execute('SELECT * FROM tasks ORDER BY deadline,id')])
@app.post('/api/tasks')
def add():
 d=request.get_json(silent=True) or {}
 try:
  id=int(d['id']);name=str(d['name']).strip();subject=str(d['subject']).strip();deadline=str(d['deadline']);priority=int(d['priority']);datetime.date.fromisoformat(deadline)
  if id<1 or len(name)>150 or len(subject)>100 or not name or not subject or priority not in (1,2,3):raise ValueError()
  with connect() as c:
   c.execute('INSERT INTO tasks(id,name,subject,deadline,priority,completed) VALUES(?,?,?,?,?,0)',(id,name,subject,deadline,priority));log(c,'them',None,snapshot(c,id))
  return jsonify(ok=True)
 except sqlite3.IntegrityError:return jsonify(error='Mã công việc đã tồn tại'),409
 except (ValueError,KeyError,TypeError):return jsonify(error='Thông tin không hợp lệ'),400
@app.patch('/api/tasks/<int:id>')
def edit(id):
 d=request.get_json(silent=True) or {}
 try:
  with connect() as c:
   before=snapshot(c,id)
   if not before:return jsonify(error='Không tìm thấy công việc'),404
   allowed={'name','subject','deadline','priority','completed'}
   vals={k:v for k,v in d.items() if k in allowed}
   if not vals:return jsonify(error='Không có thông tin cập nhật'),400
   if 'priority' in vals:
    vals['priority']=int(vals['priority'])
    if vals['priority'] not in (1,2,3):raise ValueError()
   if 'completed' in vals:vals['completed']=int(bool(vals['completed']))
   if 'deadline' in vals:datetime.date.fromisoformat(vals['deadline'])
   for k in ('name','subject'):
    if k in vals:
     vals[k]=str(vals[k]).strip()
     if not vals[k] or len(vals[k])>(150 if k=="name" else 100):raise ValueError()
   c.execute('UPDATE tasks SET '+','.join(k+'=?' for k in vals)+' WHERE id=?',(*vals.values(),id));log(c,'sua',before,snapshot(c,id))
  return jsonify(ok=True)
 except (ValueError,TypeError):return jsonify(error='Thông tin không hợp lệ'),400
@app.delete('/api/tasks/<int:id>')
def delete(id):
 with connect() as c:
  before=snapshot(c,id)
  if not before:return jsonify(error='Không tìm thấy công việc'),404
  c.execute('DELETE FROM tasks WHERE id=?',(id,));log(c,'xoa',before,None)
 return jsonify(ok=True)
@app.get('/api/history')
def history():
 with connect() as c:return jsonify([dict(x) for x in c.execute('SELECT * FROM history ORDER BY id DESC LIMIT 100')])
@app.post('/api/undo')
def undo():
 with connect() as c:
  h=c.execute('SELECT * FROM history ORDER BY id DESC LIMIT 1').fetchone()
  if not h:return jsonify(error='Không có thao tác để hoàn tác'),400
  before=json.loads(h['before_json']) if h['before_json'] else None
  after=json.loads(h['after_json']) if h['after_json'] else None
  if after:c.execute('DELETE FROM tasks WHERE id=?',(after['id'],))
  if before:c.execute('INSERT INTO tasks(id,name,subject,deadline,priority,completed) VALUES(:id,:name,:subject,:deadline,:priority,:completed)',before)
  c.execute('DELETE FROM history WHERE id=?',(h['id'],))
 return jsonify(ok=True)
@app.delete('/api/history')
def clear_history():
 with connect() as c:c.execute('DELETE FROM history')
 return jsonify(ok=True)
@app.get('/api/export')
def export():
 with connect() as c:data=[dict(x) for x in c.execute('SELECT * FROM tasks ORDER BY id')]
 return app.response_class(json.dumps(data,ensure_ascii=False,indent=2),mimetype='application/json',headers={'Content-Disposition':'attachment; filename=congviec.json'})
init()
if __name__=='__main__':app.run(host='127.0.0.1',port=5000,debug=False)
