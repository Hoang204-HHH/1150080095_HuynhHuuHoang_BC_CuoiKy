/**
 * TC21 - Quan sát khi copy mà không null-terminate.
 * Mục tiêu: Chứng minh hàm no_null_terminate_copy không ghi vượt biên,
 * nhưng có thể tạo ra buffer không có '\0'.
 *
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass (đây là testcase quan sát đặc tính, không gọi unsafe_strlen).
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

#define BUF 8

int main(void)
{
    char dst[BUF];
    char src[BUF];

    make_nondet_bytes(src, BUF);
    assume_no_nul_prefix(src, BUF);

    int rc = no_null_terminate_copy(dst, BUF, src);

    __CPROVER_assert(rc == 0, "Ham copy du lieu hop le thi rc bang 0");
    assert_no_nul_within(dst, BUF);

    return 0;
}
