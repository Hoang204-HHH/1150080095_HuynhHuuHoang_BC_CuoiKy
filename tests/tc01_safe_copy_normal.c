/**
 * TC01 - Safe copy thông thường, không truncation.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

#define DST_MAX 8
#define SRC_MAX 8

int main(void)
{
    char dst[DST_MAX];
    char src[SRC_MAX];

    make_nondet_string(src, SRC_MAX);

    int rc = safe_str_copy(dst, DST_MAX, src);

    __CPROVER_assert(rc == 0, "Du cho thi safe_str_copy phai return 0");
    assert_has_nul_within(dst, DST_MAX);

    return 0;
}
