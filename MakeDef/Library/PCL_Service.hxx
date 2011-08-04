#ifndef __PCL_SERVICE_H__
#define __PCL_SERVICE_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif
///!
///! Common (external) variables
///!

extern PCL_API VMemAdm &LMemStd;
extern PCL_API VMemAdm &LMemCOM;
extern PCL_API VMemAdm &LMemUnicode;

typedef struct {
	VMemAdm *Std;
	VMemAdm *COM;
	VMemAdm *Unicode;
} ZMemAdmRefs;

extern PCL_API ZMemAdmRefs LMem;

extern PCL_API LString &LVersionString;

///!
///! Library Service Functions
///!
PCL_API void LInitialize(void);
PCL_API void LFinalize(void);
PCL_API void LSynchronize(void);
PCL_API VMemAdm *LGetMemAdm(ZMemAdmType Type = ZMemDefault);
PCL_API void LSetDefaultMemAdm(ZMemAdmType Type = ZMemStd);
PCL_API void LSetCustomMemAdm(VMemAdm * pMemAdm);
PCL_API pvoid LGetModuleHandle(void);
PCL_API pvoid LGetPCLHandle(void);
PCL_API void LSleep(uint MSecs);
PCL_API double LRandomFromTo(double From, double To);
PCL_API pvoid LGetPCLHandle(void);

PCL_API sint LParseInt(cstr Str, bool NegAllowed = true);
PCL_API double LParseDbl(cstr Str);
PCL_API uint LParseHex(cstr Str);

PCL_API void LTrim(VString &Str);
PCL_API void LSplit(
	cstr Source,
	cstr Split,
	VString &Head,
	VString &Tail,
	ZPosition Pos = ZHead
);
PCL_API void LFormat(VString &Str, cstr Format, ...);
PCL_API VString &LFormat(cstr Format, ...);

PCL_API VString &LCurrentDir(void);
//
//PCL_API bool LSetInputFile(cstr Name, cstr Mode = NULL);
//PCL_API void LSetInputMode(ZStrConversionCode InputConvCode);
//PCL_API void LInputStr(VString &Str);
//
PCL_API bool LSetOutputFile(cstr Name, cstr Mode = NULL);
PCL_API void LSetOutputMode(ZStrConversionCode OutConvCode);
PCL_API void LOutStr(VString &Str, ZOutputFile OutFile = ZStdOut);
PCL_API void LOutItem(VItem &Item, ZOutputFile OutFile = ZStdOut);
PCL_API void LOut(cstr Format, ...);

PCL_API VItem &LItem(
	puchar Addr = NULL,
	uint Size = 0,
	uint ClassCode = ZUintInvalid,
	uint Info = 0
);
PCL_API VItem &LItem(const LDescr &Copy);
PCL_API VItem &LItem(const pZItem pItem);
PCL_API VItem &LItem(const uint &Item, uint Info = 0);
PCL_API VItem &LItem(const sint &Item, uint Info = 0);
PCL_API VItem &LItem(const float &Item, uint Info = 0);
PCL_API VItem &LItem(const double &Item, uint Info = 0);
PCL_API VItem &LItem(cstr Item, uint Info = 0);
PCL_API VItem &LItem(ustr Item, uint Info = 0);

PCL_API void XErrorSetLast(
	HRESULT Error,
	cstr Message = NULL,
	XErrorLevel ErrLevel = PCL_ELEV_(SEVERE)
);
PCL_API void XErrorSignal(cstr Message = NULL);

inline void LTerminate(cstr Message) {
	XErrorSetLast(E_FAIL, "Process Termination", PCL_ELEV_(FATAL));
	XErrorSignal(Message);
};

PCL_API void XErrorSetAction(
	XErrorLevel ErrLevel,
	XErrorAction ErrAction
);

PCL_API XErrorAction XErrorGetAction(XErrorLevel ErrLevel);

#endif // __PCL_SERVICE_H__