# Phần 1 - Tổng quan dự án

## 1.1 Giới thiệu đối tượng được kiểm thử
Đối tượng kiểm thử là một module C phục vụ học phần Software Testing, tập trung vào bài toán **buffer overflow trong hàm xử lý chuỗi**. Project gồm:
- hàm an toàn `safe_str_copy`, `safe_str_concat`
- hàm không an toàn `unsafe_str_copy`, `unsafe_str_concat`
- hàm lỗi biên `buggy_copy_off_by_one`
- hàm có khuyết điểm thiết kế `no_null_terminate_copy`

## 1.2 Mục tiêu
- Chứng minh hàm safe không đọc/ghi ngoài biên.
- Tái hiện đúng 3 bug điển hình bằng CBMC.
- Thiết kế testcase theo white-box coverage.
- Tự động hóa việc chạy suite và sinh báo cáo.

## 1.3 Công nghệ / nền tảng
- Ngôn ngữ: C11
- Công cụ kiểm chứng: CBMC
- Công cụ automation: Node.js CLI runner
- IDE khuyến nghị: Visual Studio Code

## 1.4 Thời gian thực hiện
- Phân tích yêu cầu và thiết kế: 1 tuần
- Viết harness và automation: 1 tuần
- Chạy kiểm chứng và hoàn thiện báo cáo: 1 tuần
