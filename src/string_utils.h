/**
 * @file string_utils.h
 * @brief Thư viện hàm xử lý chuỗi dùng cho đề tài:
 *        "Dùng CBMC kiểm chứng buffer overflow cho hàm xử lý chuỗi trong C"
 *
 * Ghi chú cho giảng viên / người chấm:
 * - File này được tổ chức theo chủ đích học thuật.
 * - Nhóm safe_* dùng để chứng minh hàm an toàn bằng CBMC.
 * - Nhóm unsafe_* / buggy_* dùng để cố ý tái hiện lỗi để báo cáo vẫn có ca Fail.
 * - Vì vậy trong full suite cuối cùng sẽ có 19 testcase Pass và 3 testcase Fail có chủ đích.
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Quy ước mã trả về:
 *  0  : Thành công, không bị cắt (không truncation)
 *  1  : Thành công nhưng bị cắt do thiếu dung lượng (truncation)
 * -1  : Tham số không hợp lệ
 *
 * Ý nghĩa:
 * - Các hàm safe_* phải luôn tránh đọc/ghi ngoài biên.
 * - Nếu không đủ chỗ thì được phép cắt chuỗi, nhưng vẫn phải null-terminate.
 */
int safe_str_copy(char *dst, size_t dst_size, const char *src);
int safe_str_concat(char *dst, size_t dst_size, const char *src);

/**
 * Các hàm dưới đây cố tình không an toàn để CBMC phát hiện lỗi.
 * Đây là "đối tượng demo bug", không phải mã sản xuất an toàn.
 */
size_t unsafe_strlen(const char *s);
void unsafe_str_copy(char *dst, const char *src);
void unsafe_str_concat(char *dst, const char *src);

/* Hàm cố tình có lỗi off-by-one. */
int buggy_copy_off_by_one(char *dst, size_t dst_size, const char *src);

/* Hàm cố tình không thêm ký tự '\0' ở cuối buffer. */
int no_null_terminate_copy(char *dst, size_t dst_size, const char *src);

#ifdef __cplusplus
}
#endif

#endif  // STRING_UTILS_H
