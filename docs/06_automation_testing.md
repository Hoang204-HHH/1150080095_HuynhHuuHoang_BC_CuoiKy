# Phần 6 - Automation Testing

## 6.1 Công cụ sử dụng
- CBMC
- Node.js CLI runner
- VS Code tasks

## 6.2 Script đã viết
- `automation/scripts/run-cbmc.js`
- `automation/scripts/doctor.js`

## 6.3 Hướng dẫn chạy
```bash
npm run doctor
npm run test:dry
npm run test:all
```

## 6.4 Kết quả đầu ra
- `output/test-execution-results.csv`
- `output/test-execution-results.json`
- `output/bug-report-results.csv`
- `output/summary.md`
- `output/logs/*.log`

## 6.5 Nhận xét
Automation của đề tài này phù hợp ở mức CLI runner, không dùng Selenium/Cypress vì bài toán không có giao diện web.
