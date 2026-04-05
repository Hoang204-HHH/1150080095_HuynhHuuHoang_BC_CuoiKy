/**
 * TC02 - Safe copy biên trên vừa khít.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[8];
    const char *src = "ABCDEFG";

    int rc = safe_str_copy(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 0, "Exact fit phai return 0");
    __CPROVER_assert(dst[7] == '\0', "Byte cuoi phai la null");
    return 0;
}
