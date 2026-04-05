/**
 * TC15 - Safe concat với dst = NULL.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    int rc = safe_str_concat((char *)0, 8, "ABC");
    __CPROVER_assert(rc == -1, "dst NULL thi rc bang -1");
    return 0;
}
