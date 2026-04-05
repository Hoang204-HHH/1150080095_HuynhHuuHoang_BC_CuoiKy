/**
 * TC09 - Safe concat cơ bản, đủ chỗ.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

#define DST_MAX 16
#define SRC_MAX 14

int main(void)
{
    char dst[DST_MAX] = "Hi";
    char src[SRC_MAX];

    make_nondet_string(src, SRC_MAX);

    int rc = safe_str_concat(dst, DST_MAX, src);

    __CPROVER_assert(rc == 0, "Du cho thi rc bang 0");
    assert_has_nul_within(dst, DST_MAX);

    return 0;
}
