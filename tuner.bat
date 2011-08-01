@echo off
if .%1 == . goto help
if not exist %1 mkdir %1
mkdir %1\Include
mkdir %1\Bin
mkdir %1\Lib
for /R %%d in (*.vcproj) do (Bin\fsub -l+Z:\Projects+%1+ %%d tmp && del %%d && move tmp %%d)
goto exit
:help
echo Usage: tuner $PCL_Target_Path
:exit
