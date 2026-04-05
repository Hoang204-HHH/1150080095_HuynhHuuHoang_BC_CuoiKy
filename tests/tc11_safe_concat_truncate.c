/**
 * TC11 - Safe concat truncation.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[8] = "ABCD";
    const char *src = "WXYZ";

    int rc = safe_str_concat(dst, sizeof(dst), src);

    __CPROVER_assert(rc == 1, "Khong du cho thi rc bang 1");
    __CPROVER_assert(dst[7] == '\0', "dst van phai duoc null terminate");
    return 0;
}
