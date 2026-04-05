/**
 * TC14 - Safe concat với dst không có '\0' trong phạm vi dst_size.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[4] = {'A', 'B', 'C', 'D'};
    const char *src = "Z";

    int rc = safe_str_concat(dst, sizeof(dst), src);

    __CPROVER_assert(rc == -1, "dst khong hop le thi rc bang -1");
    return 0;
}
