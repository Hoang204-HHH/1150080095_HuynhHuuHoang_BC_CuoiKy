# Phần 3 - Test Plan

## 3.1 Mục tiêu kiểm thử
- An toàn bộ nhớ
- Tính đúng đắn mã trả về
- Bao phủ nhánh valid / invalid / truncation
- Minh họa bug overflow bằng ca Fail có chủ đích

## 3.2 Chiến lược
- Functional / White-box: TC01-TC18
- Design observation: TC21
- Security-oriented defect demo: TC19, TC20, TC22

## 3.3 Môi trường
- Windows 10/11 hoặc Linux
- Node.js >= 18
- CBMC trong PATH
- VS Code

## 3.4 Entry criteria
- Project mở đúng thư mục
- `npm run doctor` không báo lỗi cấu hình
- Có sẵn lệnh `cbmc --version`

## 3.5 Exit criteria
- Chạy đủ 22 testcase
- Thu được CSV report
- 19 Pass, 3 Fail có chủ đích
- Có log riêng cho từng testcase

## 3.6 Rủi ro
- Sai PATH CBMC
- Sai version CBMC
- Người dùng chạy nhầm thư mục project

## 3.7 Lịch trình
- Setup
- Dry run
- Full run
- Tổng hợp report
