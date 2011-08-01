#ifndef __PCL_LIBRARY_H__
#define __PCL_LIBRARY_H__
#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif
///!
//*!===========================================================================!
//*! PCL stands for Portable Class Library and is designed for development
//*! of applications portable between different environments,
//*! first of all between MS Windows and GNU Linux.
//*!
//*! CopyFree Pulse Computer Consulting, 2001 - 2004
//*!
//*! CopyFree License Agreement:
//*!	1.You may do with this code whatever you like.
//*!	2.In no case Pulse Computer Consulting is responsible for your results.
//*!
//*! E-mail: pulse.cc@mail.ru
//*!===========================================================================!
///!
///!
///! PCL naming conventions:
///!	1. Virtual class names: VName
///!	2. Generic implementations of virtual classes: GName
///!	3. Library implementations of virtual or generic classes:
///!		LName or LModifiedName or LNameModified or LAlias
///!	4. Library functions: LActionDescription
///!	5. Library types: ZTypeDescription (tag PCL_TypeDescription)
///!	6. Library constants: ZConstDescription
///!	7. Any and all library names concerning error handling: XErrSomething
///!	8. Preprocessor guardians: __PCL_HEADERNAME_H__
///!	9. Preprocessor definitions: PCL_UPPERCASE_DESCRIPTION
///!
///!===========================================================================!
///!
#include "PCL_Root.h"
#include "PCL_List.h"
#include "PCL_Tree.h"
#include "PCL_String.h"
#include "PCL_Numeric.h"
#include "PCL_Service.h"
#endif //__PCL_LIBRARY_H__ 
