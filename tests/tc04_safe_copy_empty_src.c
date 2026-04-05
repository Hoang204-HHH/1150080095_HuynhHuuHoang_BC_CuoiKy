/**
 * TC04 - Safe copy với src rỗng.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[8];
    const char *src = "";

    int rc = safe_str_copy(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 0, "src rong thi rc bang 0");
    __CPROVER_assert(dst[0] == '\0', "dst phai la chuoi rong");
    return 0;
}
