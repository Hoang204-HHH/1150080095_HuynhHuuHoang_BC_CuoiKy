/**
 * TC05 - Safe copy với dst_size = 1.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[1];
    const char *src = "AB";

    int rc = safe_str_copy(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 1, "dst_size=1 va src khong rong thi truncation");
    __CPROVER_assert(dst[0] == '\0', "dst[0] phai la null");
    return 0;
}
