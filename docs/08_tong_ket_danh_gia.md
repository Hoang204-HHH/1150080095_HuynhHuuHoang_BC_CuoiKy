# Phần 8 - Tổng kết & Đánh giá

## 8.1 Tổng hợp
Bộ project cuối cùng đã được chuẩn hóa thành:
- 22 testcase
- 19 Pass
- 3 Fail có chủ đích

## 8.2 Đánh giá chất lượng
Nhóm hàm safe đạt mục tiêu minh họa an toàn bộ nhớ.
Nhóm hàm unsafe/buggy cho phép tái hiện rõ ràng lỗi overflow.

## 8.3 Đã làm được / chưa làm được
Đã làm được:
- Hoàn thiện project VS Code
- Chuẩn hóa harness
- Bổ sung doctor check
- Đồng bộ tài liệu QA/Automation/Word

Chưa làm được:
- Không chạy CBMC thật trong môi trường container bàn giao này; việc chạy thật phụ thuộc máy người dùng có cài CBMC.

## 8.4 Bài học
Hệ thống test cần tách bạch:
- defect của sản phẩm
- defect của harness / toolchain

## 8.5 Đề xuất
Sau khi chạy `npm run test:all` trên máy có CBMC, cập nhật trực tiếp CSV output vào báo cáo cuối nếu giảng viên yêu cầu ảnh chụp log thật.
