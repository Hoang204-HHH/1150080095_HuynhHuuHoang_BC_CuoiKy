/**
 * TC16 - Safe concat với src = NULL.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[8] = "A";
    int rc = safe_str_concat(dst, sizeof(dst), (const char *)0);
    __CPROVER_assert(rc == -1, "src NULL thi rc bang -1");
    return 0;
}
