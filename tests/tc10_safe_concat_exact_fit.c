/**
 * TC10 - Safe concat biên trên vừa khít.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[16] = "Hello";
    const char *src = "1234567890";

    int rc = safe_str_concat(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 0, "Exact fit thi rc bang 0");
    __CPROVER_assert(dst[15] == '\0', "Byte cuoi phai la null");
    return 0;
}
