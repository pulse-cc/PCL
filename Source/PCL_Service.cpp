///!
//*!===========================================================================!
//*! PCL stands for Portable Class Library and is designed for development
//*! of applications portable between different environments,
//*! first of all between MS Windows and GNU Linux.
//*!
//*! CopyFree Pulse Computer Consulting, 2001 - 2011
//*!
//*! CopyFree License Agreement:
//*!	1.You may do with this code WHATEVER YOU LIKE.
//*!	2.In NO CASE Pulse Computer Consulting is responsible for your results.
//*!
//*! E-mail: pulse.cc@mail.ru, pulse.cc@gmail.com
//*!===========================================================================!
///!
#define PCL_IMPLEMENTATION
#include "PCL.hxx"

HANDLE s_hDLL = NULL;
HANDLE s_hModule = NULL;
VMemAdm *s_pMemAdm[ZMemAdmCount];

PCL_API VMemAdm &LMemStd = *LGetMemAdm();
PCL_API VMemAdm &LMemCOM = *LGetMemAdm(ZMemCOM);
PCL_API VMemAdm &LMemUnicode = *LGetMemAdm(ZMemUnicode);

PCL_API ZMemAdmRefs LMem = {
	LGetMemAdm(),
	LGetMemAdm(ZMemCOM),
	LGetMemAdm(ZMemUnicode)
};

#define PCL_STAMP PCL_DESCRIPTION " " __DATE__ " " __TIME__

static LString *s_pVersionString = NULL;
static LString *_LGetVersionString() {
	if (!s_hModule) LInitialize();
	if (!s_pVersionString) {
		char buf[MAX_PATH];
		sprintf(buf, "Portable Class Library %c%d.%d ",
			LRoot::IsDebug() ? 'D' : 'R',
			LRoot::VMajor(),
			LRoot::VMinor()
		);
		s_pVersionString = new LString(buf);
		*s_pVersionString += PCL_STAMP;
	}
	return s_pVersionString;
}

#pragma message("PCL_Stamp: " PCL_STAMP)

PCL_API LString &LVersionString = *_LGetVersionString();

static LDescr *s_pItem = NULL;

PCL_API void LInitialize(void) {
	srand(::GetTickCount());
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
//	::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (!s_hModule) {
		s_hModule = GetModuleHandle(NULL);
		s_pMemAdm[ZMemStd]		= new LMemAdm();
		s_pMemAdm[ZMemCOM]		= new LMemAdmCOM();
		s_pMemAdm[ZMemUnicode]	= new LMemAdmUnicode();
		s_pMemAdm[ZMemCustom]	= NULL;
		LSetDefaultMemAdm();
		s_pItem = new LDescr();
	}
}

PCL_API void LSynchronize(void) {
	MSG message;
	::GetMessage(&message, NULL, 0, 0);
	::TranslateMessage(&message);
	::DispatchMessage(&message);
}

PCL_API void LFinalize(void) {
	if (s_pVersionString) {
		delete s_pVersionString;
		s_pVersionString = NULL;
	}
	if (s_pItem) {
		delete s_pItem;
		s_pItem = NULL;
	}
	for (uint i = 1; i < ZMemAdmCount; i++) {
		if (s_pMemAdm[i]) {
			delete s_pMemAdm[i];
			s_pMemAdm[i] = NULL;
		}
	}
	::CoUninitialize();
}

///! Library Service Implementation
PCL_API VMemAdm *LGetMemAdm(ZMemAdmType Type) {
	if (Type >= ZMemAdmCount) {
		LTerminate("Invalid Type Code passed to LGetMemAdm()");
	}
	if (!s_hModule) LInitialize();
	return s_pMemAdm[Type];
}

PCL_API void LSetDefaultMemAdm(ZMemAdmType Type) {
	if (Type >= ZMemAdmCount) {
		LTerminate("Invalid Type Code passed to LSetDefaultMemAdm()");
	}
	s_pMemAdm[ZMemDefault] = s_pMemAdm[Type];
	LMem.Std = s_pMemAdm[Type];
}

PCL_API void LSetCustomMemAdm(VMemAdm * pMemAdm) {
	s_pMemAdm[ZMemCustom] = pMemAdm;
}

PCL_API pvoid LGetPCLHandle(void) {
	if (!s_hModule) LInitialize();
	return (pvoid)s_hDLL;
}

PCL_API pvoid LGetModuleHandle(void) {
	if (!s_hModule) LInitialize();
	return (pvoid)s_hModule;
}

PCL_API void LSleep(uint MSecs) {
	::MsgWaitForMultipleObjectsEx(
		0, 0, MSecs, QS_ALLEVENTS,
		MWMO_ALERTABLE | MWMO_INPUTAVAILABLE
	);
}

PCL_API double LRandomFromTo(double From, double To) {
	const double ONENTH = 1./256.; 
	uint rNum = (rand() & 0xFF0) >> 4;
	double step = (To - From) * ONENTH;
	return From + rNum * step;
}

static cstr s_decimal = "0123456789";

PCL_API sint LParseInt(cstr Str, bool NegAllowed) {
	if (IsEmpty(Str)) return ZSintInvalid;
	sint res = 0;
	bool neg = false;
	uint ix = 0;
	if (Str[0] == '-') {
		if (!NegAllowed) return ZSintInvalid;
		neg = true;
		ix = 1;
	}
	uint i;
	uint len = strlen(Str);
	for (i = ix; i < len && Str[i] >= '0' && Str[i] <= '9'; i++) {
		res *= 10;
		res += (Str[i] - '0');
	}
	if (i < len) return ZSintInvalid;
	return neg ? -res : res;
}

PCL_API double LParseDbl(cstr Str) {
	return atof(Str);
}

PCL_API uint LParseHex(cstr Str) {
	return ZUintInvalid;
}

///! VString Processing
cstr s_blankChars = " \t\v\n\x0D\x0A";

PCL_API void LTrim(VString &Str) {
	uint ix = Str.FindNot(s_blankChars);
	Str.Cut(ix - 1, ZHead);
	ix = Str.FindNot(s_blankChars, ZTail);
	Str.Cut(Str.Length() - ix, ZTail);
}

PCL_API void LSplit(
	cstr Source,
	cstr Split,
	VString &Head,
	VString &Tail,
	ZPosition Pos
) {
	LString str(Source);
	uint ix = str.FindAny(Split, Pos);
	if (!ix) { // None of the split characters found
		if (ZHead == Pos) {
			Head.SetBody(NULL);
			Tail.SetBody(Source);
		}
		else {
			Head.SetBody(Source);
			Tail.SetBody(NULL);
		}
	}
	else {
		Head.SetBody(str.SubStr(1, ix - 1));
		Tail.SetBody(str.SubStr(ix + 1));
	}
	LTrim(Head);
	LTrim(Tail);
}

static const uint s_maxPrintSize = 40960;

static void _LFormatV(VString &Str, cstr Format, va_list ArgList) {
	char buf[s_maxPrintSize];
//	FILE *tmp = tmpfile();
	if (!Format || !Format[0]) {
		buf[0] = '\n';
		buf[1] = 0;
	}
	else {
		vsprintf(buf, Format, ArgList);
	}
	Str.SetBody(buf);
}

PCL_API void LFormat(VString &Str, cstr Format, ...) {
	va_list argList;
	va_start(argList, Format);
	_LFormatV(Str, Format, argList);
	va_end(argList);
}

PCL_API VString &LFormat(cstr Format, ...) {
	static LString s_str;
	va_list argList;
	va_start(argList, Format);
	_LFormatV(s_str, Format, argList);
	va_end(argList);
	return s_str;
}

PCL_API VString &LCurrentDir(void) {
	static LString s_str;
	uint rc = ::GetCurrentDirectory(0, NULL);
	if (!rc) {
		XErrorSetLast(E_FAIL, "GetCurrentDirectory fail");
		XErrorSignal("LCurrentDir");
	}
	LMemory buf(rc);
	rc = ::GetCurrentDirectory(rc, (pchar)buf.Addr());
	if (!rc) {
		XErrorSetLast(E_FAIL, "GetCurrentDirectory fail");
		XErrorSignal("LCurrentDir");
	}
	s_str.SetBody((cstr)buf.Addr());
	return s_str;
}

///! Library File Output
static FILE* s_outFile = NULL;
static ZStrConversionCode s_outConvCode = ZNullStrConversionCode;

PCL_API bool LSetOutputFile(cstr Name, cstr Mode) {
	if (s_outFile) {
		fclose(s_outFile);
		s_outFile = NULL;
	}
	if (!Name || !Name[0]) return false;
	if (!Mode || !Mode[0]) Mode = "wt";
	s_outFile = fopen(Name, Mode);
	if (!s_outFile) return false;
	return true;
}

PCL_API void LSetOutputMode(ZStrConversionCode OutConvCode) {
	s_outConvCode = OutConvCode;
}

PCL_API void LOutStr(VString &Str, ZOutputFile OutFile) {
	if (!Str.Length()) return;
	FILE *fl;
	switch (OutFile) {
		case ZStdOut: {
			fl = stdout;
		} break;
		case ZStdErr: {
			fl = stderr;
		} break;
		case ZCustomOut: {
			fl = s_outFile ? s_outFile : stdout;
		} break;
	}
	Str.Convert(s_outConvCode);
	fputs((cstr)Str, fl);
	fflush(fl);
}

PCL_API void LOutItem(VItem &Item, ZOutputFile OutFile) {
	if (!Item.Size()) return;
	FILE *fl;
	switch (OutFile) {
		case ZStdOut: {
			fl = stdout;
		} break;
		case ZStdErr: {
			fl = stderr;
		} break;
		case ZCustomOut: {
			fl = s_outFile ? s_outFile : stdout;
		} break;
	}
	fwrite(Item.Addr(), Item.Size(), 1, fl);
	fflush(fl);
}

PCL_API void LOut(cstr Format, ...) {
	LString str;
	char buf[s_maxPrintSize];
	if (!Format || !Format[0]) {
		buf[0] = '\n';
		buf[1] = 0;
	}
	else {
		va_list argList;
		va_start(argList, Format);
		vsprintf(buf, Format, argList);
		va_end(argList);
	}
	str.SetBody(buf);
	LOutStr(str);
}

///! Library Item Implementation
PCL_API VItem &LItem(puchar Addr, uint Size, uint ClassCode, uint Info) {
	s_pItem->SetAddr(Addr);
	s_pItem->SetSize(Size);
	s_pItem->SetClassCode(ClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

PCL_API VItem &LItem(const LDescr &Copy) {
	s_pItem->SetAddr(Copy.Addr());
	s_pItem->SetSize(Copy.Size());
	s_pItem->SetClassCode(Copy.ClassCode());
	s_pItem->SetInfo(Copy.Info());
	return *s_pItem;
}

PCL_API VItem &LItem(const pZItem pItem) {
	s_pItem->SetAddr(pItem->Addr);
	s_pItem->SetSize(pItem->Size);
	s_pItem->SetClassCode(pItem->ClassCode);
	s_pItem->SetInfo(pItem->Info);
	return *s_pItem;
}

PCL_API VItem &LItem(const uint &Item, uint Info) {
	s_pItem->SetAddr((puchar)&Item);
	s_pItem->SetSize(sizeof(uint));
	s_pItem->SetClassCode(VuintClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

PCL_API VItem &LItem(const sint &Item, uint Info) {
	s_pItem->SetAddr((puchar)&Item);
	s_pItem->SetSize(sizeof(sint));
	s_pItem->SetClassCode(VsintClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

PCL_API VItem &LItem(const float &Item, uint Info) {
	s_pItem->SetAddr((puchar)&Item);
	s_pItem->SetSize(sizeof(float));
	s_pItem->SetClassCode(VfloatClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

PCL_API VItem &LItem(const double &Item, uint Info) {
	s_pItem->SetAddr((puchar)&Item);
	s_pItem->SetSize(sizeof(double));
	s_pItem->SetClassCode(VdoubleClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

PCL_API VItem &LItem(cstr Item, uint Info) {
	if (NULL == Item) {
		s_pItem->SetAddr(NULL);
		s_pItem->SetSize(0);
	}
	else {
		s_pItem->SetAddr((puchar)&Item[0]);
		s_pItem->SetSize(strlen(Item));
	}
	s_pItem->SetClassCode(VcstrClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

PCL_API VItem &LItem(ustr Item, uint Info) {
	if (NULL == Item) {
		s_pItem->SetAddr(NULL);
		s_pItem->SetSize(0);
	}
	else {
		s_pItem->SetAddr((puchar)&Item[0]);
		s_pItem->SetSize(wcslen(Item)<<1);
	}
	s_pItem->SetClassCode(VcstrClassCode);
	s_pItem->SetInfo(Info);
	return *s_pItem;
}

#if PCL_OS_TYPE == PCL_OS_MICROSOFT && PCL_LIBRARY_TYPE == PCL_LIBRARY_DYNAMIC
BOOL WINAPI DllMain(HANDLE hModule, sint callReason, pvoid /* Reserved */) {
	if (callReason == DLL_PROCESS_ATTACH) {
		s_hDLL = hModule;
		LInitialize();
	}
	else if (callReason == DLL_THREAD_ATTACH) {
		::CoInitializeEx(NULL, COINIT_MULTITHREADED);
//		::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	}
	else if (callReason == DLL_THREAD_DETACH) {
		::CoUninitialize();
	}
	else if (callReason == DLL_PROCESS_DETACH) {
		LFinalize();
		s_hDLL = NULL;
	}
	return TRUE;
}
#endif

///! Library Error Handling Implementation
static const uint s_MaxErr = 10;
XErrorInfo s_Err[s_MaxErr];
uint s_NewErr = 0;

static const uint s_ErrStrSize = 128;
char s_ErrStr[s_ErrStrSize];
static const uint s_BufSize = (s_ErrStrSize + 2) * s_MaxErr + 128;
char s_LogBuf[s_BufSize];
char s_MsgBuf[s_BufSize];

static FILE *s_LogFile = NULL;
static cstr s_LogFileMode = "a+t";
static cstr s_LogFileName = "pcl.log";

static const uint s_MBType = MB_OK | MB_ICONSTOP;

static struct {
	pchar name;
	XErrorAction action;
} s_Level[] = {
	{"Internal Error",	PCL_EACT_(TERMINATE)	},
	{"Notification",	PCL_EACT_(IGNORE)		},
	{"Recoverable",		PCL_EACT_(DISPLAY)		},
	{"Severe Error",	PCL_EACT_(LOGUP)		},
	{"Fatal Error",		PCL_EACT_(TERMINATE)	}
};

PCL_API void XErrorSetLast(HRESULT Error, cstr Message, XErrorLevel ErrLevel) {
	if (s_NewErr == s_MaxErr) XErrorSignal("PCL Error Buffer Overflow");
	s_Err[s_NewErr].code = Error;
	s_Err[s_NewErr].level = ErrLevel;
	s_Err[s_NewErr].message = const_cast<pchar>(Message);
	s_NewErr++;
	return;
}

static uint _LevIdx(XErrorLevel Level) {
	switch (Level) {
		case PCL_ELEV_(NOTIFICATION): return 1;
		case PCL_ELEV_(RECOVERABLE): return 2;
		case PCL_ELEV_(SEVERE): return 3;
		case PCL_ELEV_(FATAL): return 4;
		default: return 0;
	}
}

static void _XErrStrFill(pXErrorInfo pErr) {
	uint offset;
	uint msgLen = strlen(pErr->message);
	pchar pbuf = &s_ErrStr[0];
	offset = sprintf(pbuf, "%s(%08lx) - ", s_Level[_LevIdx(pErr->level)].name, pErr->code);
	if (msgLen + 1 > s_ErrStrSize - offset) {
		strncat(pbuf, pErr->message, s_ErrStrSize - offset - 4);
		strcat(pbuf, "...");
	}
	else {
		strcat(pbuf, pErr->message);
	}
	return;
};

PCL_API void XErrorSignal(cstr Message) {
	if (!s_NewErr) return;
	bool needLog = false;
	bool needMsg = false;
	bool needAbort = false;
	s_LogBuf[0] = 0;
	s_MsgBuf[0] = 0;
	for (int i = s_NewErr - 1; i >= 0; i--) {
		XErrorAction mask = s_Level[_LevIdx(s_Err[i].level)].action;
		_XErrStrFill(&s_Err[i]);
		if (mask & PCL_EACT_(KEEPTRACE)) {
			strcat(s_LogBuf, "\t");
			strcat(s_LogBuf, s_ErrStr);
			strcat(s_LogBuf, "\n");
			needLog = true;
		}
		if (mask & PCL_EACT_(DISPLAY)) {
			strcat(s_MsgBuf, s_ErrStr);
			strcat(s_MsgBuf, "\x0a");
			needMsg = true;
		}
		if (mask & PCL_EACT_(ABORT)) {
			needAbort = true;
		}
	}
	if (needLog) {
		FILE *s_LogFile = fopen(s_LogFileName, s_LogFileMode);
		if (!s_LogFile) {
			strcat(s_MsgBuf, "\x0a!!! PCL LOG FILE OPEN FAILED !!!\x0a");
			needMsg = true;
		}
		else {
			fprintf(s_LogFile, "*** %s:\n%s", Message, s_LogBuf);
			fclose(s_LogFile);
		}
	}
	if (needMsg) {
		::MessageBox(NULL, s_MsgBuf, Message, MB_OK);
	}
	if (needAbort) {
		::ExitProcess(0x0DEADL);
	}
	s_NewErr = 0;
}

PCL_API void XErrorSetAction(
	XErrorLevel ErrLevel,
	XErrorAction ErrAction
) {
	if (ErrLevel & PCL_ELEV_(NOTIFICATION)) {
		XErrorAction noAbort = (XErrorAction)(ErrAction & (~PCL_EACT_(ABORT)));
		s_Level[_LevIdx(PCL_ELEV_(NOTIFICATION))].action = noAbort;
	}
	if (ErrLevel & PCL_ELEV_(RECOVERABLE)) {
		s_Level[_LevIdx(PCL_ELEV_(RECOVERABLE))].action = ErrAction;
	}
	if (ErrLevel & PCL_ELEV_(SEVERE)) {
		s_Level[_LevIdx(PCL_ELEV_(SEVERE))].action = ErrAction;
	}
	if (ErrLevel & PCL_ELEV_(FATAL)) {
		XErrorAction forcedAbort = (XErrorAction)(ErrAction | PCL_EACT_(ABORT));
		s_Level[_LevIdx(PCL_ELEV_(FATAL))].action = forcedAbort;
	}
}
