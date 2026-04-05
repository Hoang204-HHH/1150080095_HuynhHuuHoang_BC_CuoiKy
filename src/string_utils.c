/**
 * @file string_utils.c
 * @brief Triển khai các hàm xử lý chuỗi phục vụ đề tài CBMC.
 *
 * Cấu trúc file:
 * 1) Nhóm safe_*:
 *    - Viết theo hướng phòng thủ.
 *    - Có kiểm tra kích thước vùng đệm.
 *    - Không đọc/ghi ngoài biên.
 *    - Luôn cố gắng null-terminate khi đầu vào hợp lệ.
 *
 * 2) Nhóm unsafe_* / buggy_*:
 *    - Cố tình để lại lỗi phổ biến trong C.
 *    - Dùng để minh họa CBMC phát hiện buffer overflow / out-of-bounds.
 */

#include "string_utils.h"

/* -------------------------------------------------------------------------- */
/*                               SAFE FUNCTIONS                               */
/* -------------------------------------------------------------------------- */

/**
 * Sao chép src sang dst.
 *
 * Ý tưởng:
 * - Nếu tham số không hợp lệ thì trả -1 ngay.
 * - Chỉ copy tối đa dst_size - 1 ký tự để chừa chỗ cho '\0'.
 * - Nếu src dài hơn dung lượng cho phép thì return 1 (truncation).
 * - Nếu copy trọn vẹn thì return 0.
 */
int safe_str_copy(char *dst, size_t dst_size, const char *src)
{
    if (dst == NULL || src == NULL || dst_size == 0)
    {
        return -1;
    }

    size_t i = 0;
    while (i + 1 < dst_size && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }

    /* Luôn đóng chuỗi trong phạm vi hợp lệ của dst */
    dst[i] = '\0';

    /* Nếu src chưa kết thúc thì nghĩa là đã bị cắt */
    if (src[i] != '\0')
    {
        return 1;
    }

    return 0;
}

/**
 * Nối src vào cuối dst.
 *
 * Ý tưởng an toàn:
 * - Chỉ tìm độ dài của dst trong phạm vi dst_size.
 * - Nếu dst không có '\0' trong phạm vi đó thì xem là input không hợp lệ.
 * - Chỉ nối khi còn chỗ; nếu hết chỗ thì return 1 (truncation).
 */
int safe_str_concat(char *dst, size_t dst_size, const char *src)
{
    if (dst == NULL || src == NULL || dst_size == 0)
    {
        return -1;
    }

    size_t dlen = 0;
    while (dlen < dst_size && dst[dlen] != '\0')
    {
        dlen++;
    }

    if (dlen == dst_size)
    {
        /* dst không có '\0' trong phạm vi buffer */
        return -1;
    }

    if (dlen + 1 == dst_size)
    {
        /* dst đã đầy, chỉ còn đúng byte '\0' */
        return (src[0] == '\0') ? 0 : 1;
    }

    size_t i = 0;
    while ((dlen + 1) < dst_size && src[i] != '\0')
    {
        dst[dlen] = src[i];
        dlen++;
        i++;
    }

    dst[dlen] = '\0';

    if (src[i] != '\0')
    {
        return 1;
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                         UNSAFE / BUG DEMONSTRATION                         */
/* -------------------------------------------------------------------------- */

/**
 * LỖI:
 * - Duyệt đến khi gặp '\0' nhưng không có giới hạn.
 * - Nếu chuỗi đầu vào không được null-terminate, hàm sẽ đọc tràn.
 */
size_t unsafe_strlen(const char *s)
{
    size_t i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}

/**
 * LỖI:
 * - Copy từng byte cho đến khi gặp '\0'.
 * - Không biết kích thước dst nên có thể ghi tràn buffer.
 */
void unsafe_str_copy(char *dst, const char *src)
{
    size_t i = 0;
    while (1)
    {
        dst[i] = src[i];
        if (src[i] == '\0')
        {
            break;
        }
        i++;
    }
}

/**
 * LỖI CỐ Ý:
 * - Dùng unsafe_strlen để tìm dlen.
 * - Sau đó nối mà không kiểm tra dung lượng thực tế của dst.
 */
void unsafe_str_concat(char *dst, const char *src)
{
    size_t dlen = unsafe_strlen(dst);
    size_t i = 0;

    while (1)
    {
        dst[dlen + i] = src[i];
        if (src[i] == '\0')
        {
            break;
        }
        i++;
    }
}

/**
 * LỖI CỐ Ý off-by-one:
 * - Đáng lẽ ghi '\0' vào dst[i].
 * - Nhưng lại ghi vào dst[dst_size], vượt đúng 1 byte.
 */
int buggy_copy_off_by_one(char *dst, size_t dst_size, const char *src)
{
    if (dst == NULL || src == NULL || dst_size == 0)
    {
        return -1;
    }

    size_t i = 0;
    while (i + 1 < dst_size && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }

    dst[dst_size] = '\0'; /* BUG: vượt biên 1 byte */

    return 0;
}

/**
 * HÀM CÓ KHUYẾT ĐIỂM THIẾT KẾ:
 * - Copy đủ dst_size byte nhưng không thêm '\0'.
 * - Hàm này tự nó không ghi vượt biên, nhưng tạo ra buffer dễ gây đọc tràn
 *   nếu bị truyền sang unsafe_strlen hoặc các API chuỗi kiểu C khác.
 */
int no_null_terminate_copy(char *dst, size_t dst_size, const char *src)
{
    if (dst == NULL || src == NULL || dst_size == 0)
    {
        return -1;
    }

    for (size_t i = 0; i < dst_size; i++)
    {
        dst[i] = src[i];
    }

    return 0;
}
