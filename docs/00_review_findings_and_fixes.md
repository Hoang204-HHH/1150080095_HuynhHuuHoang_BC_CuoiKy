# Review Findings and Fixes - v3

## Những vấn đề của bản trước
1. `assert_has_nul_within` truyền biến con trỏ `msg` vào `__CPROVER_assert`, dễ gây lỗi tương thích trên một số môi trường CBMC Windows.
2. Một số testcase gọi trực tiếp `__CPROVER_nondet_uchar`, dẫn đến rủi ro `no body for callee`.
3. Bộ báo cáo trước đó còn lẫn giữa:
   - lỗi của module cần kiểm thử,
   - lỗi của harness/toolchain.

## Cách sửa trong bản v3
- Đổi helper nondet sang `nondet_uchar()` và `nondet_uint()`.
- Đổi helper assert sang message literal cố định.
- Chuẩn hóa suite còn đúng 3 ca Fail có chủ đích:
  - TC19: unsafe_str_copy overflow
  - TC20: buggy_copy_off_by_one
  - TC22: unsafe_str_concat overflow
- Chuyển TC21 thành ca quan sát thiết kế (`no_null_terminate_copy`) để không vượt quá 3 Fail.
- Cập nhật runner để phân biệt:
  - `Kỳ vọng CBMC`
  - `Trạng thái TC` ở góc nhìn QA
  - `Khớp kỳ vọng kỹ thuật`

## Kết quả mong muốn của bản v3
- Tổng testcase: 22
- Pass: 19
- Fail: 3
- Execution coverage: 100%
- Pass rate: 86.36%
