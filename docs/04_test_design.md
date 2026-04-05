# Phần 4 - Test Design

## 4.1 Black-box
- Phân vùng tương đương: normal / truncation / invalid
- Giá trị biên: dst_size = 0, 1, vừa khít, gần đầy

## 4.2 White-box
- Statement coverage
- Branch / Decision coverage
- Control Flow Graph cho `safe_str_copy`, `safe_str_concat`

## 4.3 Bộ testcase
Xem `testcases_master.csv`.

### Điểm nhấn của suite cuối
- 19 ca Pass để chứng minh hàm safe xử lý đúng
- 3 ca Fail để minh họa defect thật sự của các hàm unsafe/buggy
