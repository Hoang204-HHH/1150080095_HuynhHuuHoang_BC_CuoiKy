# Internal validation before delivery

The following checks were run in the delivery environment before packaging:

1. `npm run doctor`  
   - verified 22 testcases exist
   - verified exactly 3 testcases have QA status = Fail
   - verified all referenced harness/source files exist
   - verified `bugs.json` contains exactly 3 bug demo records
   - ran `gcc -fsyntax-only` successfully for all C files

2. `npm run test:dry`  
   - generated dry-run commands successfully
   - confirmed output path and logging pipeline work

3. Runtime smoke check with gcc + AddressSanitizer  
   - compiled `src/string_utils.c`
   - exercised basic safe_str_copy / safe_str_concat scenarios successfully

Note: full CBMC execution was not performed in the delivery container because `cbmc`
is not installed in this environment. The project is prepared to be executed on the
user's machine after CBMC is installed and added to PATH.
