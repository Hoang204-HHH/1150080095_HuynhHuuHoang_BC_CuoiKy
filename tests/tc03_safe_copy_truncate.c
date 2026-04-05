/**
 * TC03 - Safe copy truncation an toàn.
 * Kỳ vọng CBMC: VERIFICATION SUCCESSFUL.
 * Kết luận QA: Pass.
 */
#include "../src/string_utils.h"
#include "cbmc_utils.h"

#define DST_MAX 8
#define SRC_MAX 16

int main(void)
{
    char dst[DST_MAX];
    char src[SRC_MAX];

    make_nondet_bytes(src, SRC_MAX);
    assume_no_nul_prefix(src, DST_MAX);
    src[DST_MAX] = '\0';

    int rc = safe_str_copy(dst, DST_MAX, src);

    __CPROVER_assert(rc == 1, "Bi cat chuoi thi rc phai bang 1");
    __CPROVER_assert(dst[DST_MAX - 1] == '\0', "dst van phai duoc null terminate");

    return 0;
}
