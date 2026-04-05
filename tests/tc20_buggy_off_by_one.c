/**
 * TC20 - Buggy off-by-one.
 * Kỳ vọng CBMC: VERIFICATION FAILED.
 * Kết luận QA: Fail (defect có chủ đích).
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

#define DST_MAX 8

int main(void)
{
    char dst[DST_MAX];
    char src[DST_MAX];

    make_nondet_bytes(src, DST_MAX);
    assume_no_nul_prefix(src, DST_MAX - 1);
    src[DST_MAX - 1] = '\0';

    buggy_copy_off_by_one(dst, DST_MAX, src);

    return 0;
}
