@echo off
if .%1 == . goto help
if .%2 == . goto help
if .%2 == .. goto help_err

if not exist %2 md %2
if not exist %2\Include md %2\Include
if not exist %2\Bin md %2\Bin
if not exist %2\Lib md %2\Lib

echo Populating Include ...
copy ..\Include\PCL_*.h %2\Include >nul
copy ..\Static\Include\PCL_*.h %2\Include >nul
copy ..\pclidl.idl %2\Include >nul
copy ..\TPCL.h %2\Include >nul
call writehdr %2\Include\PCL.h DLL
call writehdr %2\Include\PCL_Static.h Main _Static

rem copy ..\Include\PCL.idl %2\Include >nul

echo Populating Bin ...
copy ..\DLL\%1\PCL*.dll %2\Bin >nul
copy ..\DLL\%1\PCL*.pdb %2\Bin >nul

echo Populating Lib ...
copy ..\DLL\%1\PCL*.lib %2\Lib >nul
copy ..\Static\%1\PCL*.lib %2\Lib >nul

goto exit

:help_err
echo Current directory as target is invalid
:help
echo distribute {Config} {Directory}
echo Example: distribute Debug Distrib

:exit