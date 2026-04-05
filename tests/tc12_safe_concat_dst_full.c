/**
 * TC12 - Safe concat khi dst đã đầy.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[5] = "ABCD";
    const char *src = "Z";

    int rc = safe_str_concat(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 1, "dst day va src khong rong thi rc bang 1");
    __CPROVER_assert(dst[4] == '\0', "Byte cuoi phai van la null");
    return 0;
}
