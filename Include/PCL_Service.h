#ifndef __PCL_SERVICE_H__ 
#define __PCL_SERVICE_H__ 
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
///! Virtual Exception
///!
///! Global Scope Definitions:
///!
typedef enum PCL_ExceptionMode { ZNullExceptionMode = 0,
	ZIgnore = 0,
///!
	ZLog	= 0x1,			// Write to LOG File
	ZOutput	= ZLog << 1,	// Write to Console
	ZDebug	= ZOutput << 1,	// Use OutputDebugString in Win32 and ??? in Linux
	ZShow	= ZDebug << 1,	// Display MessageBox
	ZQuery	= ZShow << 1,	// Display dialog allowing end user mode change
	ZThrow	= ZQuery << 1,	// Throw C++ exception
///!
	ZAbort = 0x80000000uL
} ZExceptionMode;
static const uint VExceptionClassCode = VIRTUALCODE(false);

class VException {
public:
///!
///! Public Methods
///!
public:
	virtual void Signal(cstr Message, uint Code = 0) =0;
	virtual cstr LastMessage(void) const =0;
	virtual uint LastCode(void) const =0;
	virtual void SetMode(ZExceptionMode NewMode) =0;
	virtual ZExceptionMode Mode(void) const =0;
	virtual void SetTitle(cstr NewTitle) =0;
	virtual cstr Title(void) const =0;
};
///!===========================================================================!
///!
///! Definition of Exception
///!
// Exception Class
static const uint LExceptionClassCode = CLASSCODE(VExceptionClassCode);

class PCL_API LException : public VException {
public: static const uint ClassCode() {return LExceptionClassCode;};
public:
	LException(ZExceptionMode Mode = ZIgnore);
///!
///! Public Methods
///!
public:
	virtual void Signal(cstr Message, uint Code = 0) ;
	virtual cstr LastMessage(void) const ;
	virtual uint LastCode(void) const ;
	virtual void SetMode(ZExceptionMode NewMode) ;
	virtual ZExceptionMode Mode(void) const ;
	virtual void SetTitle(cstr NewTitle) ;
	virtual cstr Title(void) const ;
private:
	LString m_title;
	ZExceptionMode m_mode;
	LString m_lastMsg;
	uint m_lastCode;
};
/*
// Error Handling Class
PCL_CLASS_OF(LException, Error):
	LError();
	virtual void Report(ZErrorLevel Level, cstr Text, uint Code);
	virtual void SetAction(ZErrorLevel Level, ZExceptionMode Mode);
};
*/
///!===========================================================================!
///!
///! Definition of common library functions
///!
typedef enum PCL_OutputFile { ZNullOutputFile = 0,
	ZStdOut,
	ZStdErr,
	ZCustomOut
} ZOutputFile;
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
