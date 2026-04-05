/**
 * TC22 - Unsafe concat gây buffer overflow khi dst gần đầy.
 * Kỳ vọng CBMC: VERIFICATION FAILED.
 * Kết luận QA: Fail (defect có chủ đích).
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[8] = "AAAAAAA";
    const char *src = "BBBB";

    unsafe_str_concat(dst, src);

    return 0;
}
