# CBMC QA Automation Project v3

Đề tài: **Dùng CBMC kiểm chứng buffer overflow cho hàm xử lý chuỗi trong C**

## Mục tiêu của bản v3
Bản v3 đã sửa các vấn đề của bản trước và chuẩn hóa suite theo mục tiêu báo cáo:

- **22 testcase**
- **19 testcase Pass**
- **3 testcase Fail có chủ đích**
- Không còn phụ thuộc vào message pointer trong `__CPROVER_assert`
- Không còn gọi trực tiếp `__CPROVER_nondet_uchar`
- Có thêm lệnh `npm run doctor` để kiểm tra cấu hình trước khi chạy

## Cấu trúc chính
- `src/`: mã nguồn C của module được kiểm thử
- `tests/`: CBMC harness cho từng testcase
- `automation/config/testcases.json`: khai báo toàn bộ suite
- `automation/config/bugs.json`: 3 bug demo
- `automation/scripts/run-cbmc.js`: runner chính
- `automation/scripts/doctor.js`: kiểm tra project trước khi chạy thật
- `docs/`: tài liệu CSV/MD phục vụ làm báo cáo
- `output/`: nơi sinh log và report sau khi chạy

## Cách chạy
### 1. Kiểm tra project trước
```bash
npm run doctor
```

### 2. Dry run
```bash
npm run test:dry
```

### 3. Chạy toàn bộ suite
```bash
npm run test:all
```

### 4. Chạy riêng một testcase
```bash
node automation/scripts/run-cbmc.js --id TC19
```

## Diễn giải kết quả
Bộ test cuối cùng được thiết kế để cho ra đúng tinh thần bài báo cáo:

- `TC01` đến `TC18` và `TC21`: **Pass**
- `TC19`, `TC20`, `TC22`: **Fail có chủ đích**

Lưu ý:
- 3 ca Fail này là **bug demo**, không phải lỗi của harness.
- Nếu CBMC báo đúng `VERIFICATION FAILED` cho 3 ca đó thì suite đang vận hành đúng.

## Kiểm tra nội bộ đã thực hiện trước khi bàn giao
Trong môi trường dựng project:
- Đã kiểm tra sự tồn tại đầy đủ của harness/source/config
- Đã kiểm tra đúng **22 testcase**
- Đã kiểm tra đúng **3 testcase Fail có chủ đích**
- Đã chạy `gcc -fsyntax-only` cho toàn bộ file C
- Đã chạy `npm run doctor`
- Đã chạy `npm run test:dry`

> Việc chạy CBMC thật vẫn phụ thuộc máy có cài `cbmc` trong PATH.
