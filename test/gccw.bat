@echo off
set EXEFILE=a.exe

:find_file
if -%1 == - goto run
if exist "%1" (
    set EXEFILE=%~n1.exe
    goto run
) else (
    shift /1
    goto find_file
)

:run
if exist "%EXEFILE%" del "%EXEFILE%"
if -%~x1 == -cpp (
    g++ -static-libstdc++ -static-libgcc -O2 @%~dpn0-warnings -o "%EXEFILE%" %*
) else (
    gcc -static-libgcc -O2 @%~dpn0-warnings -o "%EXEFILE%" %*
)
if exist "%EXEFILE%" strip "%EXEFILE%"
