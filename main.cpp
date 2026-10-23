#include<bits/stdc++.h>
using namespace std;

// ======================================================
// 1. CẤU TRÚC CÔNG VIỆC
// ======================================================

const int MAX = 1000;

struct CongViec{
    int ma;
    string ten;
    string monHoc;
    string hanChot;
    int doUuTien;
    bool daHoanThanh;
};

CongViec danhSachCongViec[MAX];
int soLuongCongViec = 0;


// PHAN CUA: NGUYEN ANH QUAN
// 2. DANH SÁCH LIÊN KẾT ĐƠN

typedef struct node{
int data;
struct node *next;
}Node;
typedef struct slist{
public:
Node *head;
Node *tail;
int size;
void init();
Node *createNode(int x);
void themDau(int x);
void themCuoi(int x);
Node *timTheoMa(int x);
bool xoaTheoMa(int x);
void hienthi();
int soluong();
}Slist;
void Slist::init(){
head =NULL;
tail=NULL;
size =0;
}
Node *Slist::createNode(int x){
Node *p = new Node;
p->data=x;
p->next=NULL;
return p;
}

void Slist::themDau(int x){
Node *p =createNode(x);
if(head ==NULL){
head = p;
tail =p;
}
else{
p->next =head;
head=p;
}
size ++;
}
void Slist::themCuoi(int x){
Node *p= createNode(x);
if(head==NULL){
head=p;
tail=p;
}
else{
tail->next=p;
tail=p;
}
size++;
}
Node *Slist::timTheoMa(int x){
Node *p= head;
 while(p != NULL){
if(p->data==x){
return p;
}
p=p->next;
}
return NULL;
}

bool Slist::xoaTheoMa(int x){
    if(head == NULL){
        return false;
    }

    if(head->data == x){
        Node *p = head;
        head = head->next;
        delete p;
        size--;

        if(head == NULL){
            tail = NULL;
        }

        return true;
    }

    Node *p = head;

    while(p->next != NULL){
        if(p->next->data == x){
            Node *q = p->next;
            p->next = q->next;

            if(q == tail){
                tail = p;
            }

            delete q;
            size--;
            return true;
        }

        p = p->next;
    }

    return false;
} // Đóng hàm xoaTheoMa tại đây


void Slist::hienthi(){
    if(head == NULL){
        cout << "\nDanh sach rong!\n";
        return;
    }

    Node *p = head;

    cout << "\n========== DANH SACH CONG VIEC ==========\n";

    while(p != NULL){
        int ma = p->data;

        for(int i = 0; i < soLuongCongViec; i++){
            if(danhSachCongViec[i].ma == ma){
                cout << "\nMa: " << danhSachCongViec[i].ma;
                cout << "\nTen: " << danhSachCongViec[i].ten;
                cout << "\nMon hoc: " << danhSachCongViec[i].monHoc;
                cout << "\nHan chot: " << danhSachCongViec[i].hanChot;
                cout << "\nDo uu tien: " << danhSachCongViec[i].doUuTien;

                cout << "\nTrang thai: ";

                if(danhSachCongViec[i].daHoanThanh){
                    cout << "Da hoan thanh";
                }
                else{
                    cout << "Chua hoan thanh";
                }

                cout << "\n------------------------------------------";
                break;
            }
        }

        p = p->next;
    }

    cout << "\n";
}

int Slist::soluong(){
    return size;
}

int timViTriCongViec(int ma){

    for(int i = 0; i < soLuongCongViec; i++){

        if(danhSachCongViec[i].ma == ma){

            return i;
        }
    }

    return -1;
}

bool xoaCongViecTrongMang(int ma){
    int viTri = timViTriCongViec(ma);
    if(viTri == -1){
        return false;
    }
    for(int i = viTri; i < soLuongCongViec - 1; i++){
        danhSachCongViec[i] =
        danhSachCongViec[i + 1];
    }
    soLuongCongViec--;
    return true;
}



// PHAN CUA: LE MINH QUY
// 4. HÀNG ĐỢI DEADLINE

typedef struct nodeQueue{
      CongViec data;
     struct nodeQueue *next;
}NodeQueue;
typedef struct hangdoi{
     public:
     NodeQueue *head;
     NodeQueue *tail;
     int size;
     void khoiTao();
     bool rong();
     void them(CongViec cv);
     CongViec layRa();
     void hienThi();
     void xoaHet();
     int soLuong();    
}HangDoiDeadline;
// Khởi tạo  Queue
void HangDoiDeadline::khoiTao(){
     head=NULL;
     tail=NULL;
     size=0;   
}
// Kiểm tra rỗng
bool HangDoiDeadline::rong(){
     return head=NULL;
}
// Thêm vào cuối Queue
void HangDoiDeadline::them(CongViec cv){
     NodeQueue *p= new NodeQueue;
     p->data=cv;
     p->next=NULL;
     if(head == NULL){
        head=p;
        tail=p;
 }
     else {
      tail->next=p;
      tail=p;
     }
  size++;
}
CongViec HangDoiDeadline::layRa(){
      CongViec rong;
      rong.ma=-1;
     if (head==NULL){
        return rong;
}
     NodeQueue *p= head;
     CongViec cv = p->data;
     head = head ->next;
     delete p;
     size--; 
     if ( head == NULL){
        tail = NULL;
   }
      return cv;
}
void HangDoiDeadline::hienThi(){
       if (head == NULL){
           cout<<" \nHang doi rong!\n";
       return ;
}
    NodeQueue *p = head ;
    cout <<"\n========== HANG DOI DEADLINE ==========\n";
    
  while(p != NULL){

        cout << "\nMa: "
             << p->data.ma;

        cout << "\nTen: "
             << p->data.ten;

        cout << "\nMon: "
             << p->data.monHoc;

        cout << "\nHan: "
             << p->data.hanChot;

        cout << "\n---------------------------------------";

        p = p->next;
    }
    cout << "\n";
}
void HangDoiDeadline::xoaHet(){
    while(head != NULL){
        NodeQueue *p = head;
        head = head->next;
        delete p;
    }
    tail = NULL;
    size = 0;
}
int HangDoiDeadline::soLuong(){
    return size;
}

//phần của Quế Minh 
// 5. NGĂN XẾP LỊCH SỬ
// ======================================================

struct LichSu{

    string hanhDong;

    CongViec congViec;
};


typedef struct nodeStack{

    LichSu data;

    struct nodeStack *next;

}NodeStack;


typedef struct nganxep{

public:

    NodeStack *top;

    int size;

    void khoiTao();

    bool rong();

    void them(LichSu x);

    LichSu layRa();

    void hienThi();

    void xoaHet();

    int soLuong();

}NganXepLichSu;


// Khởi tạo Stack
void NganXepLichSu::khoiTao(){


    top = NULL;

    size = 0;
}
// Kiểm tra rỗng
bool NganXepLichSu::rong(){

    return top == NULL;
}
// Thêm vào Stack
void NganXepLichSu::them(LichSu x){

    NodeStack *p = new NodeStack;

    p->data = x;

    p->next = top;

    top = p;

    size++;
}
// Lấy phần tử trên cùng
LichSu NganXepLichSu::layRa(){

    LichSu rong;

    rong.hanhDong = "";

    rong.congViec.ma = -1;


    if(top == NULL){

        return rong;
    }


    NodeStack *p = top;

    LichSu x = p->data;

    top = top->next;

    delete p;

    size--;

    return x;
}
// Hiển thị Stack
void NganXepLichSu::hienThi(){

    if(top == NULL){

        cout << "\nLich su rong!\n";

        return;
    }


    NodeStack *p = top;

    cout << "\n========== LICH SU ==========\n";


    while(p != NULL){

        cout << "\nHanh dong: "
             << p->data.hanhDong;

        cout << "\nMa cong viec: "
             << p->data.congViec.ma;

        cout << "\nTen: "
             << p->data.congViec.ten;

        cout << "\n------------------------------";

        p = p->next;
    }

    cout << "\n";
}
// Xóa Stack
void NganXepLichSu::xoaHet(){

    while(top != NULL){

        NodeStack *p = top;

        top = top->next;

        delete p;
    }

    size = 0;
}


// Số lượng
int NganXepLichSu::soLuong(){

    return size;
}


// PHAN CUA: PHAM THI HAI YEN
// 6. CÂY NHỊ PHÂN TÌM KIẾM BST

typedef struct nutcay{

    CongViec data;

    struct nutcay *left;

    struct nutcay *right;

}NutCay;


typedef struct caydeadline{
public:
    NutCay *root;
    int size;

    void khoiTao();
    NutCay *taoNut(CongViec cv);
    NutCay *themNode(NutCay *p, CongViec cv);
    void them(CongViec cv);

    void duyetLNR(NutCay *p);
    void duyetNLR(NutCay *p);
    void duyetLRN(NutCay *p);

    void tangDan();
    void giamDan();

    void hienThi();

    void xoaCay(NutCay *p);
    void xoaHet();
}CayDeadline;


// Khởi tạo cây
void CayDeadline::khoiTao(){

    root = NULL;

    size = 0;
}


// Tạo Node
NutCay *CayDeadline::taoNut(CongViec cv){

    NutCay *p = new NutCay;

    p->data = cv;

    p->left = NULL;

    p->right = NULL;

    return p;
}


// Thêm Node vào BST
NutCay *CayDeadline::themNode(
    NutCay *p,
    CongViec cv
){

    if(p == NULL){

        size++;

        return taoNut(cv);
    }


    if(cv.hanChot < p->data.hanChot){

        p->left =
        themNode(p->left, cv);
    }
    else{

        p->right =
        themNode(p->right, cv);
    }


    return p;
}


// Thêm vào cây
void CayDeadline::them(CongViec cv){

    root = themNode(root, cv);
}


// Duyệt LNR
void CayDeadline::duyetLNR(NutCay *p){

    if(p == NULL){

        return;
    }


    duyetLNR(p->left);


    cout << "\nMa: "
         << p->data.ma;

    cout << " | Ten: "
         << p->data.ten;

    cout << " | Han: "
         << p->data.hanChot;


    duyetLNR(p->right);
}


// Duyệt NLR
void CayDeadline::duyetNLR(NutCay *p){

    if(p == NULL){

        return;
    }


    cout << "\nMa: "
         << p->data.ma;

    cout << " | Ten: "
         << p->data.ten;

    cout << " | Han: "
         << p->data.hanChot;


    duyetNLR(p->left);

    duyetNLR(p->right);
}


// Duyệt LRN
void CayDeadline::duyetLRN(NutCay *p){

    if(p == NULL){

        return;
    }


    duyetLRN(p->left);

    duyetLRN(p->right);


    cout << "\nMa: "
         << p->data.ma;

    cout << " | Ten: "
         << p->data.ten;

    cout << " | Han: "
         << p->data.hanChot;
}


// Deadline tăng dần
void CayDeadline::tangDan(){

    cout << "\n========== DEADLINE TANG DAN ==========\n";

    duyetLNR(root);

    cout << "\n";
}


// Deadline giảm dần
void CayDeadline::giamDan(){

    cout << "\n========== DEADLINE GIAM DAN ==========\n";

    // RNL
    stack<NutCay*> nganXep;

    NutCay *p = root;


    while(p != NULL || !nganXep.empty()){

        while(p != NULL){

            nganXep.push(p);

            p = p->right;
        }


        p = nganXep.top();

        nganXep.pop();


        cout << "\nMa: "
             << p->data.ma;

        cout << " | Ten: "
             << p->data.ten;

        cout << " | Han: "
             << p->data.hanChot;


        p = p->left;
    }

    cout << "\n";
}
void CayDeadline::hienThi(){
    if(root == NULL){
        cout << "Cay dang rong!\n";
        return;
    }

    cout << "\nDANH SACH CONG VIEC THEO DEADLINE TANG DAN:\n";
    duyetLNR(root);
}

// Xóa cây
void CayDeadline::xoaCay(NutCay *p){

    if(p == NULL){

        return;
    }


    xoaCay(p->left);

    xoaCay(p->right);

    delete p;
}


// Xóa toàn bộ cây
void CayDeadline::xoaHet(){

    xoaCay(root);

    root = NULL;

    size = 0;
}


// PHAN CUA: HOANG MINH QUAN
// 7. CÁC HÀM TÌM KIẾM

// Chuyển chữ thường
string vietThuong(string s){

    for(int i = 0; i < s.length(); i++){

        s[i] = tolower(s[i]);
    }

    return s;
}

// In công việc
void inTask(CongViec cv){

    cout << "\nMa: "
         << cv.ma;

    cout << "\nTen: "
         << cv.ten;

    cout << "\nMon hoc: "
         << cv.monHoc;

    cout << "\nHan chot: "
         << cv.hanChot;

    cout << "\nDo uu tien: "
         << cv.doUuTien;

    cout << "\nTrang thai: ";


    if(cv.daHoanThanh){

        cout << "Da hoan thanh";
    }
    else{

        cout << "Chua hoan thanh";
    }

    cout << "\n--------------------------------------";
}
// Tìm theo tên
void timTheoTen(
    Slist &danhSach,
    string tuKhoa
){

    Node *p = danhSach.head;

    bool timThay = false;

    tuKhoa = vietThuong(tuKhoa);


    while(p != NULL){

        int ma = p->data;

        int viTri = timViTriCongViec(ma);


        if(viTri != -1){

            string ten =
            vietThuong(
                danhSachCongViec[viTri].ten
            );


            if(
                ten.find(tuKhoa)
                != string::npos
            ){

                inTask(
                    danhSachCongViec[viTri]
                );

                timThay = true;
            }
        }


        p = p->next;
    }


    if(!timThay){

        cout << "\nKhong tim thay!\n";
    }
}
// Tìm theo môn
void timTheoMon(
    Slist &danhSach,
    string mon
){

    Node *p = danhSach.head;

    bool timThay = false;

    mon = vietThuong(mon);


    while(p != NULL){

        int ma = p->data;

        int viTri = timViTriCongViec(ma);


        if(viTri != -1){

            string tenMon =
            vietThuong(
                danhSachCongViec[viTri].monHoc
            );


            if(
                tenMon.find(mon)
                != string::npos
            ){

                inTask(
                    danhSachCongViec[viTri]
                );

                timThay = true;
            }
        }


        p = p->next;
    }


    if(!timThay){

        cout << "\nKhong tim thay!\n";
    }
}

// ======================================================
// 8. HÀM LỌC
// ======================================================

// Lọc theo trạng thái
void locTheoTrangThai(
    Slist &danhSach,
    bool trangThai
){

    Node *p = danhSach.head;

    bool timThay = false;


    while(p != NULL){

        int ma = p->data;

        int viTri =
        timViTriCongViec(ma);


        if(viTri != -1){

            if(
                danhSachCongViec[viTri]
                .daHoanThanh
                == trangThai
            ){

                inTask(
                    danhSachCongViec[viTri]
                );

                timThay = true;
            }
        }


        p = p->next;
    }


    if(!timThay){

        cout << "\nKhong co cong viec phu hop!\n";
    }
}

// Lọc theo ưu tiên
void locTheoUuTien(
    Slist &danhSach,
    int muc
){

    Node *p = danhSach.head;

    bool timThay = false;


    while(p != NULL){

        int ma = p->data;

        int viTri =
        timViTriCongViec(ma);


        if(viTri != -1){

            if(
                danhSachCongViec[viTri]
                .doUuTien
                == muc
            ){

                inTask(
                    danhSachCongViec[viTri]
                );

                timThay = true;
            }
        }


        p = p->next;
    }


    if(!timThay){

        cout << "\nKhong co cong viec phu hop!\n";
    }
}

// ======================================================
// 9. THỐNG KÊ
// ======================================================

int demDaHoanThanh(Slist &danhSach){

    int dem = 0;

    Node *p = danhSach.head;


    while(p != NULL){

        int viTri =
        timViTriCongViec(p->data);


        if(viTri != -1){

            if(
                danhSachCongViec[viTri]
                .daHoanThanh
            ){

                dem++;
            }
        }


        p = p->next;
    }


    return dem;
}


int demChuaHoanThanh(Slist &danhSach){

    int dem = 0;

    Node *p = danhSach.head;


    while(p != NULL){

        int viTri =
        timViTriCongViec(p->data);


        if(viTri != -1){

            if(
                !danhSachCongViec[viTri]
                .daHoanThanh
            ){

                dem++;
            }
        }


        p = p->next;
    }


    return dem;
}


int demTheoUuTien(
    Slist &danhSach,
    int muc
){

    int dem = 0;

    Node *p = danhSach.head;


    while(p != NULL){

        int viTri =
        timViTriCongViec(p->data);


        if(viTri != -1){

            if(
                danhSachCongViec[viTri]
                .doUuTien
                == muc
            ){

                dem++;
            }
        }


        p = p->next;
    }


    return dem;
}


// Thống kê
void thongKe(Slist &danhSach){

    cout << "\n========== THONG KE ==========\n";


    cout << "\nTong so cong viec: "
         << danhSach.soluong();


    cout << "\nDa hoan thanh: "
         << demDaHoanThanh(danhSach);


    cout << "\nChua hoan thanh: "
         << demChuaHoanThanh(danhSach);


    cout << "\n\nTheo do uu tien:";


    for(int i = 1; i <= 3; i++){

        cout << "\nUu tien "
             << i
             << ": "
             << demTheoUuTien(
                    danhSach,
                    i
                );
    }


    cout << "\n";
}
// PHAN TICH HOP CHUNG CUA NHOM - QUAN LY CONG VIEC
// 10. LỚP QUẢN LÝ
// Kiểm tra năm nhuận
bool laNamNhuan(int nam) {
    return (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
}

// Kiểm tra định dạng YYYY-MM-DD và tính hợp lệ của ngày tháng
bool kiemTraNgayHopLe(string s) {
    // 1. Độ dài chuẩn phải là 10 ký tự (YYYY-MM-DD)
    if (s.length() != 10) return false;
    if (s[4] != '-' || s[7] != '-') return false;

    // 2. Kiểm tra các vị trí khác phải là chữ số
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(s[i])) return false;
    }

    // 3. Tách Năm, Tháng, Ngày
    int nam = stoi(s.substr(0, 4));
    int thang = stoi(s.substr(5, 2));
    int ngay = stoi(s.substr(8, 2));

    // 4. Kiểm tra giới hạn Năm và Tháng
    if (nam < 1 || thang < 1 || thang > 12 || ngay < 1) return false;

    // 5. Số ngày tối đa của từng tháng
    int ngayTrongThang[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (thang == 2 && laNamNhuan(nam)) {
        ngayTrongThang[2] = 29;
    }

    // 6. Kiểm tra ngày vượt quá số ngày tối đa trong tháng
    if (ngay > ngayTrongThang[thang]) return false;

    return true;
}
struct QuanLyCongViec{
    Slist danhSach;
    HangDoiDeadline hangDoi;
    NganXepLichSu lichSu;
    CayDeadline cay;

    int idTiepTheo;

    void khoiTao();
    void capNhatHangDoi();
    void capNhatCay();

    void themCongViec();
    void xoaCongViec();
    void hoanThanh();

    void timKiem();
    void loc();

    void hienThiHangDoi();
    void xuLyThongBao();

    void hienThiCay();
    void sapXepDeadline();

    void hienThiLichSu();
    void xoaLichSu();
    void hoanTac();

    void thongKeCongViec();
    void menu();
};


void QuanLyCongViec::khoiTao(){

    danhSach.init();

    hangDoi.khoiTao();

    lichSu.khoiTao();

    cay.khoiTao();


    // Mã đầu tiên là 1
    idTiepTheo = 1;


    // Chưa có công việc
    soLuongCongViec = 0;
}



// ======================================================
// CẬP NHẬT QUEUE
// ======================================================


// Ý tưởng:
//
// Xóa Queue cũ
//     ↓
// Duyệt toàn bộ công việc
//     ↓
// Nếu chưa hoàn thành
//     ↓
// Đưa vào Queue
//
// Vì vậy Queue luôn được xây dựng lại
// dựa trên dữ liệu hiện tại.
void QuanLyCongViec::capNhatHangDoi(){

    // Xóa Queue cũ
    hangDoi.xoaHet();


    // Bắt đầu từ Linked List
    Node *p = danhSach.head;


    // Duyệt danh sách mã
    while(p != NULL){

        // Tìm vị trí công việc trong mảng
        int viTri =
        timViTriCongViec(p->data);


        if(viTri != -1){

            // Chỉ đưa công việc CHƯA hoàn thành vào Queue
            if(
                !danhSachCongViec[viTri]
                .daHoanThanh
            ){

                hangDoi.them(
                    danhSachCongViec[viTri]
                );
            }
        }


        // Sang Node tiếp theo
        p = p->next;
    }
}



// ======================================================
// CẬP NHẬT BST
// ======================================================


// Ý tưởng:
//
// Xóa cây cũ
//     ↓
// Duyệt Linked List
//     ↓
// Lấy từng công việc
//     ↓
// Đưa vào BST
//
// BST được xây lại từ dữ liệu hiện tại.
void QuanLyCongViec::capNhatCay(){

    // Xóa cây cũ
    cay.xoaHet();


    // Bắt đầu từ Linked List
    Node *p = danhSach.head;


    // Duyệt toàn bộ danh sách
    while(p != NULL){

        // Tìm công việc trong mảng
        int viTri =
        timViTriCongViec(p->data);


        if(viTri != -1){

            // Thêm công việc vào BST
            cay.them(
                danhSachCongViec[viTri]
            );
        }


        p = p->next;
    }
}



// ======================================================
// THÊM CÔNG VIỆC
// ======================================================

void QuanLyCongViec::themCongViec(){

    // Không cho thêm quá 1000 công việc
    if(soLuongCongViec >= MAX){

        cout << "\nDa dat toi da 1000 cong viec!\n";

        return;
    }


    // Tạo biến công việc mới
    CongViec cv;


    // Cấp mã tự động
    //
    // Nếu idTiepTheo = 1:
    //
    // cv.ma = 1
    // idTiepTheo = 2
    cv.ma = idTiepTheo++;


    // Xóa ký tự Enter còn lại sau cin
    cin.ignore();


    // Nhập tên
    cout << "\nNhap ten cong viec: ";

    getline(cin, cv.ten);


    // Nhập môn
    cout << "Nhap mon hoc: ";

    getline(cin, cv.monHoc);


    // Nhập deadline có kiểm tra tính hợp lệ
    do {
        cout << "Nhap han chot (YYYY-MM-DD): ";
        getline(cin, cv.hanChot);

        if (!kiemTraNgayHopLe(cv.hanChot)) {
            cout << "-> Ngay khong hop le hoac sai dinh dang! Vui long nhap lai.\n";
        }
    } while (!kiemTraNgayHopLe(cv.hanChot));

    // Nhập ưu tiên
    cout << "Nhap do uu tien (1-3): ";

    cin >> cv.doUuTien;


    // Kiểm tra ưu tiên
    while(
        cv.doUuTien < 1
        ||
        cv.doUuTien > 3
    ){

        cout << "Nhap lai (1-3): ";

        cin >> cv.doUuTien;
    }


    // Công việc mới mặc định chưa hoàn thành
    cv.daHoanThanh = false;



    // --------------------------------------------------
    // LƯU VÀO MẢNG
    // --------------------------------------------------

    danhSachCongViec[
        soLuongCongViec
    ] = cv;


    // Tăng số lượng công việc
    soLuongCongViec++;



    // --------------------------------------------------
    // LƯU MÃ VÀO LINKED LIST
    // --------------------------------------------------

    danhSach.themCuoi(cv.ma);



    // --------------------------------------------------
    // LƯU LỊCH SỬ VÀO STACK
    // --------------------------------------------------

    LichSu ls;


    // Ghi hành động là THEM
    ls.hanhDong = "THEM";


    // Lưu bản sao công việc
    ls.congViec = cv;


    // Đưa lịch sử vào Stack
    lichSu.them(ls);



    // --------------------------------------------------
    // CẬP NHẬT QUEUE VÀ BST
    // --------------------------------------------------

    capNhatHangDoi();

    capNhatCay();


    cout << "\nThem thanh cong!";

    cout << "\nMa cong viec: "
         << cv.ma
         << "\n";
}



// ======================================================
// XÓA CÔNG VIỆC
// ======================================================

void QuanLyCongViec::xoaCongViec(){

    int ma;


    // Nhập mã cần xóa
    cout << "\nNhap ma can xoa: ";

    cin >> ma;


    // Tìm công việc
    int viTri =
    timViTriCongViec(ma);


    // Không tìm thấy
    if(viTri == -1){

        cout << "\nKhong tim thay!\n";

        return;
    }


    // Lưu bản sao công việc trước khi xóa
    //
    // Vì cần bản sao này để Undo.
    CongViec cv =
    danhSachCongViec[viTri];



    // --------------------------------------------------
    // LƯU LỊCH SỬ
    // --------------------------------------------------

    LichSu ls;

    ls.hanhDong = "XOA";

    ls.congViec = cv;

    lichSu.them(ls);



    // --------------------------------------------------
    // XÓA KHỎI LINKED LIST
    // --------------------------------------------------

    danhSach.xoaTheoMa(ma);



    // --------------------------------------------------
    // XÓA KHỎI MẢNG
    // --------------------------------------------------

    xoaCongViecTrongMang(ma);



    // --------------------------------------------------
    // CẬP NHẬT LẠI QUEUE VÀ BST
    // --------------------------------------------------

    capNhatHangDoi();

    capNhatCay();


    cout << "\nXoa thanh cong!\n";
}



// ======================================================
// ĐÁNH DẤU HOÀN THÀNH
// ======================================================

void QuanLyCongViec::hoanThanh(){

    int ma;


    // Nhập mã
    cout << "\nNhap ma cong viec: ";

    cin >> ma;


    // Tìm vị trí
    int viTri =
    timViTriCongViec(ma);


    // Không tìm thấy
    if(viTri == -1){

        cout << "\nKhong tim thay!\n";

        return;
    }


    // Nếu đã hoàn thành rồi
    if(
        danhSachCongViec[viTri]
        .daHoanThanh
    ){

        cout << "\nCong viec da hoan thanh!\n";

        return;
    }



    // --------------------------------------------------
    // LƯU LỊCH SỬ ĐỂ SAU NÀY UNDO
    // --------------------------------------------------

    LichSu ls;

    ls.hanhDong = "HOAN THANH";

    ls.congViec =
    danhSachCongViec[viTri];

    lichSu.them(ls);



    // --------------------------------------------------
    // THAY ĐỔI TRẠNG THÁI
    // --------------------------------------------------

    danhSachCongViec[viTri]
    .daHoanThanh = true;


    // --------------------------------------------------
    // CẬP NHẬT QUEUE
    // --------------------------------------------------

    // Vì công việc đã hoàn thành
    // nên nó phải được loại khỏi Queue.
    capNhatHangDoi();


    cout << "\nDa hoan thanh!\n";
}



// ======================================================
// TÌM KIẾM
// ======================================================

void QuanLyCongViec::timKiem(){

    int chon;


    cout << "\n========== TIM KIEM ==========\n";

    cout << "1. Tim theo ma\n";

    cout << "2. Tim theo ten\n";

    cout << "3. Tim theo mon hoc\n";

    cout << "Chon: ";

    cin >> chon;



    // --------------------------------------------------
    // TÌM THEO MÃ
    // --------------------------------------------------

    if(chon == 1){

        int ma;


        cout << "Nhap ma: ";

        cin >> ma;


        // Tìm trong mảng
        int viTri =
        timViTriCongViec(ma);


        if(viTri != -1){

            // In công việc
            inTask(
                danhSachCongViec[viTri]
            );
        }

        else{

            cout << "\nKhong tim thay!\n";
        }
    }



    // --------------------------------------------------
    // TÌM THEO TÊN
    // --------------------------------------------------

    else if(chon == 2){

        string ten;


        cin.ignore();


        cout << "Nhap ten: ";

        getline(cin, ten);


        timTheoTen(
            danhSach,
            ten
        );
    }



    // --------------------------------------------------
    // TÌM THEO MÔN
    // --------------------------------------------------

    else if(chon == 3){

        string mon;


        cin.ignore();


        cout << "Nhap mon: ";

        getline(cin, mon);


        timTheoMon(
            danhSach,
            mon
        );
    }


    else{

        cout << "\nLua chon sai!\n";
    }
}



// ======================================================
// LỌC
// ======================================================

void QuanLyCongViec::loc(){

    int chon;


    cout << "\n========== LOC ==========\n";

    cout << "1. Da hoan thanh\n";

    cout << "2. Chua hoan thanh\n";

    cout << "3. Theo do uu tien\n";

    cout << "Chon: ";

    cin >> chon;



    // --------------------------------------------------
    // LỌC ĐÃ HOÀN THÀNH
    // --------------------------------------------------

    if(chon == 1){

        locTheoTrangThai(
            danhSach,
            true
        );
    }



    // --------------------------------------------------
    // LỌC CHƯA HOÀN THÀNH
    // --------------------------------------------------

    else if(chon == 2){

        locTheoTrangThai(
            danhSach,
            false
        );
    }



    // --------------------------------------------------
    // LỌC THEO ƯU TIÊN
    // --------------------------------------------------

    else if(chon == 3){

        int muc;


        cout << "Nhap muc uu tien: ";

        cin >> muc;


        // Chỉ cho phép từ 1 đến 3
        if(muc >= 1 && muc <= 3){

            locTheoUuTien(
                danhSach,
                muc
            );
        }

        else{

            cout << "\nMuc uu tien tu 1 den 3!\n";
        }
    }


    else{

        cout << "\nLua chon sai!\n";
    }
}



// ======================================================
// QUEUE
// ======================================================


// Hiển thị Queue
void QuanLyCongViec::hienThiHangDoi(){

    // Xây dựng lại Queue
    capNhatHangDoi();


    // Hiển thị
    hangDoi.hienThi();
}



// ======================================================
// XỬ LÝ CÔNG VIỆC ĐẦU QUEUE
// ======================================================


// Ý tưởng:
//
// Cập nhật Queue
//     ↓
// Kiểm tra rỗng
//     ↓
// Lấy công việc đầu tiên
//     ↓
// Hiển thị công việc
void QuanLyCongViec::xuLyThongBao(){

    // Cập nhật Queue
    capNhatHangDoi();


    // Nếu không có công việc
    if(hangDoi.rong()){

        cout << "\nKhong co cong viec dang cho!\n";

        return;
    }


    // Lấy công việc đầu Queue
    CongViec cv =
    hangDoi.layRa();


    cout << "\nCong viec dau hang doi:\n";


    // In công việc
    inTask(cv);


    // Xây dựng lại Queue
    capNhatHangDoi();
}



// ======================================================
// BST
// ======================================================


// Hiển thị cây
void QuanLyCongViec::hienThiCay(){

    // Xây dựng lại BST
    capNhatCay();


    // Gọi hàm hiển thị BST
    cay.hienThi();
}



// ======================================================
// SẮP XẾP DEADLINE
// ======================================================

void QuanLyCongViec::sapXepDeadline(){

    // Cập nhật BST trước
    capNhatCay();


    int chon;


    cout << "\n========== DEADLINE ==========\n";

    cout << "1. Tang dan\n";

    cout << "2. Giam dan\n";

    cout << "Chon: ";

    cin >> chon;



    // Deadline tăng dần
    if(chon == 1){

        cay.tangDan();
    }


    // Deadline giảm dần
    else if(chon == 2){

        cay.giamDan();
    }


    else{

        cout << "\nLua chon sai!\n";
    }
}



// ======================================================
// STACK / UNDO
// ======================================================


// Hiển thị lịch sử
void QuanLyCongViec::hienThiLichSu(){

    lichSu.hienThi();
}



// ======================================================
// XÓA LỊCH SỬ
// ======================================================

void QuanLyCongViec::xoaLichSu(){

    // Xóa toàn bộ Stack
    lichSu.xoaHet();


    cout << "\nDa xoa lich su!\n";
}



// ======================================================
// UNDO
// ======================================================


// Đây là một trong những hàm quan trọng nhất.
//
// Ý tưởng:
//
// Stack:
//
// HOAN THANH 3  <- mới nhất
// XOA 2
// THEM 1
//
// Undo:
//
// lấy HOAN THANH 3 ra
// rồi khôi phục trạng thái trước đó.
void QuanLyCongViec::hoanTac(){

    // Nếu Stack rỗng
    if(lichSu.rong()){

        cout << "\nKhong co thao tac de Undo!\n";

        return;
    }


    // Lấy thao tác mới nhất
    LichSu ls =
    lichSu.layRa();



    // ==================================================
    // UNDO THÊM
    // ==================================================

    if(ls.hanhDong == "THEM"){

        // Lấy mã công việc
        int ma =
        ls.congViec.ma;


        // Vì trước đó đã thêm
        // nên Undo = xóa công việc
        danhSach.xoaTheoMa(ma);


        // Xóa khỏi mảng
        xoaCongViecTrongMang(ma);


        cout << "\nDa Undo thao tac THEM!\n";
    }



    // ==================================================
    // UNDO XÓA
    // ==================================================

    else if(ls.hanhDong == "XOA"){

        // Kiểm tra mảng còn chỗ không
        if(soLuongCongViec < MAX){

            // Đưa công việc trở lại mảng
            danhSachCongViec[
                soLuongCongViec
            ] = ls.congViec;


            // Tăng số lượng
            soLuongCongViec++;


            // Đưa mã trở lại Linked List
            danhSach.themCuoi(
                ls.congViec.ma
            );


            cout << "\nDa khoi phuc cong viec!\n";
        }
    }



    // ==================================================
    // UNDO HOÀN THÀNH
    // ==================================================

    else if(ls.hanhDong == "HOAN THANH"){

        // Tìm lại công việc
        int viTri =
        timViTriCongViec(
            ls.congViec.ma
        );


        if(viTri != -1){

            // Chuyển lại thành chưa hoàn thành
            danhSachCongViec[viTri]
            .daHoanThanh = false;
        }


        cout << "\nDa Undo trang thai hoan thanh!\n";
    }



    // ==================================================
    // CẬP NHẬT LẠI QUEUE VÀ BST
    // ==================================================

    capNhatHangDoi();

    capNhatCay();
}



// ======================================================
// THỐNG KÊ
// ======================================================

void QuanLyCongViec::thongKeCongViec(){

    // Gọi hàm thống kê
    thongKe(danhSach);
}



// ======================================================
// MENU
// ======================================================

void QuanLyCongViec::menu(){

    int chon;


    // Do-while:
    // Menu sẽ chạy ít nhất một lần
    // và lặp lại cho đến khi chọn 0.
    do{

        cout << "\n\n";

        cout << "=========================================\n";

        cout << "     SO TAY HOC TAP VA QUAN LY DEADLINE\n";

        cout << "=========================================\n";


        cout << "1. Them cong viec\n";

        cout << "2. Xoa cong viec\n";

        cout << "3. Danh dau hoan thanh\n";

        cout << "4. Hien thi danh sach\n";

        cout << "5. Tim kiem\n";

        cout << "6. Loc cong viec\n";

        cout << "7. Hien thi hang doi Deadline\n";

        cout << "8. Xu ly cong viec dau hang doi\n";

        cout << "9. Hien thi cay BST\n";

        cout << "10. Sap xep Deadline\n";

        cout << "11. Lich su thao tac\n";

        cout << "12. Undo\n";

        cout << "13. Xoa lich su\n";

        cout << "14. Thong ke\n";

        cout << "0. Thoat\n";


        cout << "=========================================\n";


        cout << "Nhap lua chon: ";

        cin >> chon;



        // ==================================================
        // SWITCH DÙNG ĐỂ XỬ LÝ LỰA CHỌN
        // ==================================================

        switch(chon){


            // ------------------------------------------------
            // 1. THÊM
            // ------------------------------------------------

            case 1:

                themCongViec();

                break;



            // ------------------------------------------------
            // 2. XÓA
            // ------------------------------------------------

            case 2:

                xoaCongViec();

                break;



            // ------------------------------------------------
            // 3. HOÀN THÀNH
            // ------------------------------------------------

            case 3:

                hoanThanh();

                break;



            // ------------------------------------------------
            // 4. HIỂN THỊ DANH SÁCH
            // ------------------------------------------------

            case 4:

                danhSach.hienthi();

                break;



            // ------------------------------------------------
            // 5. TÌM KIẾM
            // ------------------------------------------------

            case 5:

                timKiem();

                break;



            // ------------------------------------------------
            // 6. LỌC
            // ------------------------------------------------

            case 6:

                loc();

                break;



            // ------------------------------------------------
            // 7. HIỂN THỊ QUEUE
            // ------------------------------------------------

            case 7:

                hienThiHangDoi();

                break;



            // ------------------------------------------------
            // 8. XỬ LÝ QUEUE
            // ------------------------------------------------

            case 8:

                xuLyThongBao();

                break;



            // ------------------------------------------------
            // 9. HIỂN THỊ BST
            // ------------------------------------------------

            case 9:

                hienThiCay();

                break;



            // ------------------------------------------------
            // 10. SẮP XẾP DEADLINE
            // ------------------------------------------------

            case 10:

                sapXepDeadline();

                break;



            // ------------------------------------------------
            // 11. HIỂN THỊ LỊCH SỬ
            // ------------------------------------------------

            case 11:

                hienThiLichSu();

                break;



            // ------------------------------------------------
            // 12. UNDO
            // ------------------------------------------------

            case 12:

                hoanTac();

                break;



            // ------------------------------------------------
            // 13. XÓA LỊCH SỬ
            // ------------------------------------------------

            case 13:

                xoaLichSu();

                break;



            // ------------------------------------------------
            // 14. THỐNG KÊ
            // ------------------------------------------------

            case 14:

                thongKeCongViec();

                break;



            // ------------------------------------------------
            // 0. THOÁT
            // ------------------------------------------------

            case 0:

                cout << "\nCam on ban da su dung chuong trinh!\n";

                break;



            // ------------------------------------------------
            // NHẬP SAI
            // ------------------------------------------------

            default:

                cout << "\nLua chon khong hop le!\n";
        }


    // Nếu chưa chọn 0 thì tiếp tục hiện Menu
    }while(chon != 0);
}



// ======================================================
// MAIN
// ======================================================

int main(){

    QuanLyCongViec quanLy;

    quanLy.khoiTao();

    quanLy.menu();

    return 0;
}
