/**
 * TC18 - Integration: safe_str_copy rồi safe_str_concat.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[16];

    int rc1 = safe_str_copy(dst, sizeof(dst), "Hi");
    int rc2 = safe_str_concat(dst, sizeof(dst), "!");

    __CPROVER_assert(rc1 == 0, "Copy hop le thi rc1 bang 0");
    __CPROVER_assert(rc2 == 0, "Concat hop le thi rc2 bang 0");
    __CPROVER_assert(dst[0] == 'H', "dst[0] phai la H");
    __CPROVER_assert(dst[1] == 'i', "dst[1] phai la i");
    __CPROVER_assert(dst[2] == '!', "dst[2] phai la !");
    __CPROVER_assert(dst[3] == '\0', "dst[3] phai la null");
    return 0;
}
