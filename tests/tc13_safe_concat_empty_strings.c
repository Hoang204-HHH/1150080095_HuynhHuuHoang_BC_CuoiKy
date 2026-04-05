/**
 * TC13 - Safe concat với dst rỗng, src rỗng.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[8] = "";
    const char *src = "";

    int rc = safe_str_concat(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 0, "Hai chuoi rong thi rc bang 0");
    __CPROVER_assert(dst[0] == '\0', "dst van la chuoi rong");
    return 0;
}
