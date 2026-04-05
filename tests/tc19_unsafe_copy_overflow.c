/**
 * TC19 - Unsafe copy gây buffer overflow.
 * Kỳ vọng CBMC: VERIFICATION FAILED.
 * Kết luận QA: Fail (defect có chủ đích).
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

#define DST_MAX 8
#define SRC_MAX 9

int main(void)
{
    char dst[DST_MAX];
    char src[SRC_MAX];

    make_nondet_bytes(src, SRC_MAX);
    assume_no_nul_prefix(src, DST_MAX);
    src[DST_MAX] = '\0';

    unsafe_str_copy(dst, src);

    return 0;
}
