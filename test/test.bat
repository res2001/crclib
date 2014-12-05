@echo off
for %%a in (test_cfg_*.h) do (
    echo === USING %%a ====
    copy %%a fast_crc_cfg.h > nul
    call gccw -I. -I.. fastcrc_test.c ../fast_crc.c -w ../crc.c
    fastcrc_test
    pause
)
