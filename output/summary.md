# Test Execution Summary

- Thời gian tạo báo cáo: 2026-04-05T04:49:09.507Z
- Node.js: v22.14.0
- CBMC: 6.8.0 (cbmc-6.8.0)
- Dry run: Không
- Tổng số testcase: 1
- Pass (QA): 0
- Fail (QA): 1
- Not Run: 0
- Khớp kỳ vọng kỹ thuật: 1/1

## Diễn giải

- `Trạng thái TC = Pass` nghĩa là hàm/hành vi được kiểm chứng là đạt.
- `Trạng thái TC = Fail` trong 3 ca TC19, TC20, TC22 là **có chủ đích**, dùng để minh họa bug buffer overflow / off-by-one.
- Nếu chạy `--dry-run`, script chỉ kiểm tra cấu hình và sinh command, không có verdict thực tế.
