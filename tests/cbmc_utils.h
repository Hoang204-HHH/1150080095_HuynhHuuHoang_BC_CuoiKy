/**
 * @file cbmc_utils.h
 * @brief Tiện ích dùng riêng cho CBMC harness.
 *
 * Các helper trong file này được viết lại để tránh lỗi tương thích với
 * một số môi trường CBMC trên Windows:
 * - Không dùng __CPROVER_nondet_uchar trực tiếp.
 * - Không truyền biến con trỏ làm message cho __CPROVER_assert.
 *
 * Cách làm an toàn hơn:
 * - Khai báo các hàm nondet thông thường: nondet_uchar(), nondet_uint().
 * - Dùng message là string literal cố định trong từng helper.
 */

#ifndef CBMC_UTILS_H
#define CBMC_UTILS_H

#include <stddef.h>

/* Khai báo nondet function theo kiểu CBMC hỗ trợ tốt */
unsigned char nondet_uchar(void);
unsigned int nondet_uint(void);

void __CPROVER_assume(int);
void __CPROVER_assert(int, const char *);

/* Điền dữ liệu symbolic vào mảng byte */
static inline void make_nondet_bytes(char *s, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        s[i] = (char)nondet_uchar();
    }
}

/* Sinh chuỗi symbolic nhưng luôn buộc byte cuối là '\0' */
static inline void make_nondet_string(char *s, size_t max)
{
    if (max == 0)
    {
        return;
    }

    for (size_t i = 0; i + 1 < max; ++i)
    {
        s[i] = (char)nondet_uchar();
    }
    s[max - 1] = '\0';
}

/* Giả định n byte đầu đều khác '\0' */
static inline void assume_no_nul_prefix(const char *s, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        __CPROVER_assume(s[i] != '\0');
    }
}

/* Khẳng định buffer có ít nhất một '\0' trong phạm vi max */
static inline void assert_has_nul_within(const char *s, size_t max)
{
    int found = 0;
    for (size_t i = 0; i < max; ++i)
    {
        if (s[i] == '\0')
        {
            found = 1;
            break;
        }
    }

    __CPROVER_assert(found, "Buffer phai co ky tu null trong pham vi cho phep");
}

/* Khẳng định buffer KHÔNG có '\0' trong phạm vi max */
static inline void assert_no_nul_within(const char *s, size_t max)
{
    for (size_t i = 0; i < max; ++i)
    {
        __CPROVER_assert(s[i] != '\0', "Buffer khong duoc co ky tu null trong pham vi max");
    }
}

#endif  // CBMC_UTILS_H
