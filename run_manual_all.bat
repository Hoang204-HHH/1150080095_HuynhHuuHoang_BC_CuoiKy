@echo off
setlocal enabledelayedexpansion
chcp 65001 >nul

echo ============================================
echo  CBMC Manual Runner - 22 Testcases
echo ============================================
echo.

where cbmc >nul 2>nul
if errorlevel 1 (
  echo [ERROR] Khong tim thay lenh CBMC trong PATH.
  echo Hay cai dat CBMC va mo terminal moi roi chay lai.
  pause
  exit /b 1
)

if not exist tests (
  echo [ERROR] Khong tim thay thu muc tests.
  echo Hay dat file nay trong thu muc goc cua project.
  pause
  exit /b 1
)

if not exist src (
  echo [ERROR] Khong tim thay thu muc src.
  echo Hay dat file nay trong thu muc goc cua project.
  pause
  exit /b 1
)

if not exist manual_logs mkdir manual_logs

set COMMON=src\string_utils.c --bounds-check --pointer-check --unwind 64

echo [INFO] Bat dau chay test...
echo.

call :run_pass tc01_safe_copy_normal.c
call :run_pass tc02_safe_copy_exact_fit.c
call :run_pass tc03_safe_copy_truncate.c
call :run_pass tc04_safe_copy_empty_src.c
call :run_pass tc05_safe_copy_dst_size_1.c
call :run_pass tc06_safe_copy_null_dst.c
call :run_pass tc07_safe_copy_null_src.c
call :run_pass tc08_safe_copy_size_zero.c
call :run_pass tc09_safe_concat_basic.c
call :run_pass tc10_safe_concat_exact_fit.c
call :run_pass tc11_safe_concat_truncate.c
call :run_pass tc12_safe_concat_dst_full.c
call :run_pass tc13_safe_concat_empty_strings.c
call :run_pass tc14_safe_concat_unterminated_dst.c
call :run_pass tc15_safe_concat_null_dst.c
call :run_pass tc16_safe_concat_null_src.c
call :run_pass tc17_safe_concat_size_zero.c
call :run_pass tc18_integration_safe_copy_then_concat.c
call :run_fail tc19_unsafe_copy_overflow.c
call :run_fail tc20_buggy_off_by_one.c
call :run_pass tc21_no_null_copy_observation.c
call :run_fail tc22_unsafe_concat_overflow.c

echo.
echo ============================================
echo  Da chay xong toan bo 22 testcase
echo  Xem log trong thu muc manual_logs
echo ============================================
pause
exit /b 0

:run_pass
set FILE=%~1
echo --------------------------------------------
echo [RUN][EXPECT PASS] %FILE%
cbmc tests\%FILE% %COMMON% > manual_logs\%~n1.log 2>&1
findstr /C:"VERIFICATION SUCCESSFUL" manual_logs\%~n1.log >nul
if errorlevel 1 (
  echo [CHECK] %FILE% khong ra SUCCESSFUL. Xem log: manual_logs\%~n1.log
) else (
  echo [OK] %FILE% -> VERIFICATION SUCCESSFUL
)
exit /b 0

:run_fail
set FILE=%~1
echo --------------------------------------------
echo [RUN][EXPECT FAIL] %FILE%
cbmc tests\%FILE% %COMMON% --trace > manual_logs\%~n1.log 2>&1
findstr /C:"VERIFICATION FAILED" manual_logs\%~n1.log >nul
if errorlevel 1 (
  echo [CHECK] %FILE% khong ra FAILED nhu ky vong. Xem log: manual_logs\%~n1.log
) else (
  echo [OK] %FILE% -> VERIFICATION FAILED (dung chu dich)
)
exit /b 0
