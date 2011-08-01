#define PCL_GENDEFRUN
#define __PCL_H__
#include "PCL_License.h"
#include "PCL_Internal.h"

#define PCL_PURE =0
///!
///! Virtual String
///!
///! Global Scope Definitions:
///!
PCL_ENUMERATOR(StrConversionCode)
	ZUpperCase,
	ZLowerCase,
	ZNameStyle, // First Letter Uppercase, all the rest Lowercase
	ZOEM,
	ZANSI,
} ZStrConversionCode;
///!
inline bool IsEmpty(cstr Str) {
	return !Str || !Str[0];
};
///!
PCL_VIRTUAL_CONTAINER(String):
#include "PCL_VString.hxx"
};
#undef PCL_PURE
#define PCL_PURE /**/
///!===========================================================================!
///!
///! Definition of String
///!
#include "PCL_String.hxx"
