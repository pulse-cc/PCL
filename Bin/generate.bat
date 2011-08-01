@echo off
echo #ifndef __PCL_%3_H__>%2 
echo #define __PCL_%3_H__>> %2 
echo #ifndef __PCL_H__>> %2
echo #	error Do not include this file directly. Include "PCL.h" instead>> %2
echo #endif>> %2
cl /nologo /C /I..\Include /I.\Generic /I.\Library /I.\Virtual /EP /u /X %1 | findstr "." >>%2 
echo #endif // __PCL_%3_H__>> %2 
