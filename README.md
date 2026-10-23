# Sổ tay học tập — bản cloud

## Triển khai Render
1. Tạo GitHub repository riêng tư và tải các file trong thư mục `so_tay_web` lên thư mục gốc repository, bao gồm `templates/index.html` và `render.yaml`.
2. Vào Render > New > Blueprint, kết nối repository. Render sẽ đọc `render.yaml`.
3. Thiết lập `ADMIN_PASSWORD` là mật khẩu dài, khó đoán (không lưu trong GitHub). Tên đăng nhập mặc định `admin`.
4. Render cấp đường dẫn HTTPS. Dùng cùng đường dẫn trên điện thoại và máy tính. Trình duyệt sẽ yêu cầu tên đăng nhập và mật khẩu.
5. Dữ liệu SQLite lưu tại `/var/data/congviec.db` trên ổ đĩa persistent disk.

**Chi phí:** Persistent disk yêu cầu gói Render trả phí; kiểm tra giá mới nhất trước khi triển khai. Disk không thay thế sao lưu. Định kỳ tải JSON qua nút Xuất JSON, cất trên máy hoặc Drive. Xóa disk/dịch vụ có thể làm mất dữ liệu.

## Chạy trên Windows
1. Cài Python. Mở CMD trong thư mục ứng dụng.
2. `py -m pip install -r requirements.txt`
3. `set ADMIN_PASSWORD=MatKhauRiengCuaBan`
4. `py app.py` và mở `http://127.0.0.1:5000`.

## Lưu ý
Đây là ứng dụng một tài khoản chung, không có tài khoản riêng từng thành viên. Không sử dụng HTTP Basic qua Internet không có HTTPS. Không chạy nhiều instance ghi vào SQLite. Chưa có tính năng nhập JSON để phục hồi. Các thao tác Linked List/Queue/BST/Stack được chuyển đổi theo hành vi chứ không dịch nguyên từng dòng C++.
