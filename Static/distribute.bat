@echo off
if .%1 == . goto help
if .%2 == . goto help
if .%2 == .. goto help_err

if not exist %2 md %2
if not exist %2\Include md %2\Include
if not exist %2\Lib md %2\Lib

echo Populating Include ...
copy .\Include\PCL_*.h %2\Include >nul
call ..\Bin\writehdr %2\Include\PCL%3.h Main %3

rem copy ..\Include\PCL.idl %2\Include >nul

echo Populating Lib ...
copy %1\PCL*.lib %2\Lib >nul

goto exit

:help_err
echo Current directory as target is invalid
:help
echo distribute {Config} {Directory}
echo Example: distribute Debug Distrib

:exit