"""Copy contents to PythonAnywhere Web > WSGI configuration file.
Set ADMIN_PASSWORD in the real WSGI file, never commit your password to GitHub.
"""
import os
import sys

USERNAME = 'YOUR_PYTHONANYWHERE_USERNAME'
PROJECT = '/home/' + USERNAME + '/so_tay_github'
if PROJECT not in sys.path:
    sys.path.insert(0, PROJECT)

os.environ['DB_PATH'] = '/home/' + USERNAME + '/congviec.db'
os.environ['ADMIN_USER'] = 'admin'
os.environ['ADMIN_PASSWORD'] = 'REPLACE_WITH_YOUR_OWN_STRONG_PASSWORD'
os.environ['REQUIRE_AUTH'] = '1'

from app import app as application
