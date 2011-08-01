@echo off
if not .%2 == . goto MainHeader
echo #ifndef __PCL_LIBRARY_H__>%1
echo #define __PCL_LIBRARY_H__>>%1
echo #ifndef __PCL_H__>>%1
echo #	error Do not include this file directly. Include "PCL.h" instead>>%1
echo #endif>>%1
copy /Y %1+..\Include\PCL_License.h+..\Include\PCL_Naming.h %1 /B >nul
echo #include "PCL_Root.h">>%1
echo #include "PCL_List.h">>%1
echo #include "PCL_Tree.h">>%1
echo #include "PCL_String.h">>%1
echo #include "PCL_Numeric.h">>%1
echo #include "PCL_Service.h">>%1
echo #endif //__PCL_LIBRARY_H__>>%1 
goto Exit
:MainHeader
echo #ifndef __PCL_H__>%1
echo #define __PCL_H__>>%1
copy /Y %1+..\Include\PCL_License.h+..\Include\PCL_Naming.h %1 /B >nul
echo #include "PCL_Define.h">>%1
echo #include "PCL_Config%3.h">>%1
echo #include "PCL_Environment.h">>%1
echo #include "PCL_Types.h">>%1
echo #include "PCL_Error.h">>%1
echo #include "PCL_Library.h">>%1
echo #endif //__PCL_H__>>%1 
:Exit
