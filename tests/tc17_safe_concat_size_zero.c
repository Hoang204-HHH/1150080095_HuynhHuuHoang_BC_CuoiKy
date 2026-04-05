/**
 * TC17 - Safe concat với dst_size = 0.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

int main(void)
{
    char dst[1];
    dst[0] = 'X';

    int rc = safe_str_concat(dst, 0, "A");

    __CPROVER_assert(rc == -1, "dst_size=0 thi rc bang -1");
    __CPROVER_assert(dst[0] == 'X', "Khong duoc ghi vao dst");
    return 0;
}
