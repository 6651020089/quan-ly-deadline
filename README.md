/ Sổ tay Học tập & Quản lý Deadline

//Giới thiệu Đây là chương trình hỗ trợ quản lý công việc học tập, deadline và theo dõi tiến độ hoàn thành công việc.

//Cấu trúc dữ liệu chính Danh sách liên kết đơn (Singly Linked List), Hàng đợi liên kết (Queue), Ngăn xếp (Stack), Cây nhị phân tìm kiếm (BST).

//Thuật toán áp dụng Duyệt danh sách liên kết; tìm kiếm theo ID, tên, môn học; lọc theo trạng thái; duyệt BST LNR/RNL để sắp xếp Deadline tăng/giảm; FIFO cho Queue; LIFO cho Stack và Undo.

//Nghiệp vụ quản lý cơ bản Thêm, xóa và hoàn thành công việc; quản lý tên, môn học, Deadline, mức ưu tiên và trạng thái; tìm kiếm, lọc công việc; quản lý thông báo Deadline; xem Deadline tăng/giảm; quản lý lịch sử thao tác; Undo; thống kê tiến độ.

//Yêu cầu kỹ thuật C++ Struct/Class, con trỏ,cài đặt Linked List, Queue, Stack, BST; sử dụng hàm và đệ quy; thao tác với chuỗi; tổ chức các cấu trúc dữ liệu trong lớp StudentTaskManager.

//Thành viên nhóm

Nguyễn Anh Quân ,Lê Minh Quý, Phạm Quế Minh, Phạm Thị Hải Yến ,Hoàng Minh Quân

Chạy chương trình C++
1. Mở tệp main.cpp bằng Dev-C++ hoặc Code::Blocks, nhấn Build and Run.
2. Nhập số tương ứng với chức năng, nhấn Enter. Khi thêm công việc nhập lần lượt: tên,
môn học, hạn chót (YYYY-MM-DD), độ ưu tiên (1 đến 3).
3. Nhập 0 để thoát; chương trình tự ghi dữ liệu vào congviec.txt (cùng thư mục với tệp thực
thi) và nạp lại ở lần chạy sau. Xóa tệp này nếu muốn bắt đầu với danh sách rỗng.
4. Nên thoát bằng lựa chọn 0; nếu đóng cửa sổ đột ngột, thay đổi của phiên đó không được
lưu.

Sổ tay học tập & quản lý Deadline — GitHub + PythonAnywhere
Ứng dụng Flask + SQLite, truy cập bằng trình duyệt trên điện thoại và máy tính. Gồm thêm/sửa/xóa công việc, lọc, thống kê, lịch sử, hoàn tác, xuất JSON.

Đưa mã nguồn lên GitHub
Tạo repository Private.
Upload nội dung thư mục ZIP (không upload nguyên ZIP), giữ templates/index.html.
Không tải lên mật khẩu, file congviec.db, .env, hoặc WSGI thật có mật khẩu.
Cập nhật website PythonAnywhere đã chạy
Nếu ứng dụng của bạn đã hoạt động ở /home/phamthihaiyen/so_tay_web, không cần tạo website mới. Bạn có thể tải các file app.py, templates/index.html lên đúng thư mục cũ qua tab Files, thay file cũ rồi Web > Reload. Giữ nguyên file cơ sở dữ liệu congviec.db; không xóa thư mục cũ hoặc ghi đè dữ liệu. Sao lưu dữ liệu trước khi cập nhật.

Cài mới bằng GitHub trên PythonAnywhere
Mở Consoles > Bash. Chạy git clone https://github.com/USERNAME/REPOSITORY.git ~/so_tay_github (repo Private cần xác thực GitHub; có thể upload file bằng Files thay thế).
Chạy pip3 install --user -r ~/so_tay_github/requirements.txt.
Mở Web > WSGI configuration file. Sao chép nội dung pythonanywhere_wsgi.py vào file WSGI thật, thay YOUR_PYTHONANYWHERE_USERNAME và đặt ADMIN_PASSWORD riêng. Không commit file WSGI thật chứa mật khẩu lên GitHub.
Chọn Web > Reload rồi mở URL https://USERNAME.pythonanywhere.com. Đăng nhập với username admin và mật khẩu vừa đặt.
Nếu gặp HTTP 500, vào Web > Log files > Error log.
Lưu dữ liệu: SQLite đặt tại /home/USERNAME/congviec.db (bên ngoài thư mục code), giúp không bị ghi đè khi cập nhật code. Nếu website cũ đã có dữ liệu ở ~/so_tay_web/congviec.db, hãy sao lưu và trỏ DB_PATH tới file cũ, hoặc chuyển file sang vị trí mới trước khi chạy bản mới. Không tạo cơ sở dữ liệu rỗng rồi tưởng dữ liệu cũ đã mất.

Lưu ý: PythonAnywhere gói miễn phí có giới hạn và có thể cần gia hạn website định kỳ. File SQLite không phải sao lưu: hãy xuất JSON thường xuyên. Bản này chưa hỗ trợ nhập JSON để khôi phục. Dùng HTTPS, mật khẩu mạnh, không chia sẻ tài khoản. pythonanywhere_wsgi.py chỉ là mẫu, không dùng mật khẩu mẫu trong môi trường thật.

Kiểm tra cú pháp
python3 -m py_compile app.py

Giao diện nâng cấp (23/10/2026)
Đã bỏ phần hiển thị BST theo Deadline khỏi trang chính (không ảnh hưởng mã C++ trong dự án gốc).
Thêm nút Hoàn thành / Chưa xong cho từng công việc, đồng bộ ngay với API PATCH và SQLite.
Tối ưu bố cục responsive, danh sách dạng thẻ, bộ lọc, thanh tiến độ, hàng đợi và lịch sử.
Cập nhật PythonAnywhere không mất dữ liệu
Sao lưu congviec.db và file WSGI đang chạy.
Chỉ thay templates/index.html trong /home/<username>/so_tay_web/templates/ để nâng cấp giao diện.
Không xóa hoặc ghi đè congviec.db, không tải file WSGI có mật khẩu lên GitHub.
Trên tab Web chọn Reload, sau đó làm mới trang bằng Ctrl+Shift+R.
Nút Hoàn thành sử dụng PATCH /api/tasks/<id> và yêu cầu phiên bản app.py trong gói này hoặc phiên bản cũ có cùng API.
