///!
//*!===========================================================================!
//*! PCL stands for Portable Class Library and is designed for development
//*! of applications portable between different environments,
//*! first of all between MS Windows and GNU Linux.
//*!
//*! CopyFree Pulse Computer Consulting, 2001, 2002
//*!
//*! CopyFree License Agreement:
//*!	1.You may do with this code whatever you like.
//*!	2.In no case Pulse Computer Consulting is responsible for your results.
//*!
//*! E-mail: pulse.cc@mail.ru
//*!===========================================================================!
///!
#define PCL_IMPLEMENTATION
#include "PCL.hxx"

///! Service Functions
static void _ShiftRight(pchar pStart, uint Count, uint Shift) {
	pchar pFrom = pStart + Count - 1; // The last char of shifted substring
	pchar pTo = pFrom + Shift; // Location of the last char of destination
	for (uint i = 0; i < Count; i++) {
		*pTo-- = *pFrom--;
	}
}
static void _ShiftLeft(pchar pStart, uint Count, uint Shift) {
	pchar pFrom = pStart; // The first char of shifted substring
	pchar pTo = pFrom - Shift; // Location of the first char of destination
	for (uint i = 0; i < Count; i++) {
		*pTo++ = *pFrom++;
	}
}

///! Implementation of GString
GString::GString() {
	m_last.Found = 0;
	m_last.Pos = ZNullPosition;
	m_last.Mode = 0;
	m_last.Len = 0;
};

GString::~GString() {
};

GString::GString(const pcont pContainer) {
	LTerminate("constructor GString(const pcont pContainer) called");
};

const pcont GString::Export(void) {
	uint strLen = m_data.Size();
	uint contSize = sizeof(ZContainer) + strLen;
	pZContainer pHdr = (pZContainer)LMem.Std->Alloc(contSize);
	pHdr->classCode = ClassCode();
	pHdr->dataSize = contSize;
	if (strLen) {
		memcpy(pHdr + 1, m_data.Addr(), strLen); // No trailing 0 stored !!!
	}
	return (pcont)pHdr;
};

void GString::Import(const pcont pContainer, bool AutoRelease) {
	if (m_data.Size()) m_data.SetSize(0);
	pZContainer pHdr = (pZContainer)pContainer;
	if (!pHdr) return; // Empty container provides empty string
	if (ClassCode() != pHdr->classCode) {
		XErrorSetLast(E_INVALIDARG, "Wrong Container: not a string");
		XErrorSignal("GString::Import");
		return;
	}
	m_data.SetSize(pHdr->dataSize - sizeof(ZContainer));
	uint strLen = m_data.Size();
	if (strLen) {
		puchar pData = (puchar)m_data.Addr();
		memcpy(pData, pHdr + 1, strLen); // No trailing 0 loaded !!!
		*(pData + strLen) = 0; // Add trailing 0
	}
	if (AutoRelease) {
		pHdr->classCode = 0; // Mark as released (to be on the safe side)
		LMem.Std->Dealloc(pContainer);
	}
};

uint GString::Length() const {
	return m_data.Size();
};

void GString::SetBody(cstr Body) {
	m_last.Found = 0;
	m_data.SetSize(Body ? strlen(Body) : 0);
	uint strLen = m_data.Size();
	if (strLen) {
		memcpy(m_data.Addr(), Body, strLen + 1); // Trailing 0 stored !!!
	}
};

typedef int (__stdcall * pStrCmp) (cstr, cstr);

int GString::Compare(cstr CmpStr, bool IgnoreCase) const {
	pStrCmp pCmp = IgnoreCase ? &lstrcmpi : &lstrcmp;
	return (*pCmp)(Body(), CmpStr);
}

// Comparisons
bool GString::operator ==(cstr Src) const {
	return 0 == Compare(Src);
}

bool GString::operator !=(cstr Src) const {
	return 0 != Compare(Src);
}

bool GString::operator >=(cstr Src) const {
	return 0 <= Compare(Src);
}

bool GString::operator >(cstr Src) const {
	return 0 < Compare(Src);
}

bool GString::operator <=(cstr Src) const {
	return 0 >= Compare(Src);
}

bool GString::operator <(cstr Src) const {
	return 0 > Compare(Src);
}

void GString::Append(cstr App) {
	if (NULL == App || 0 == App[0]) return;
	uint addLen = strlen(App);
	uint oldLen = m_data.Size();
	m_data.SetSize(oldLen + addLen);
	memcpy(
		(puchar)m_data.Addr() + oldLen,
		App,
		addLen + 1
	); // Trailing 0 stored !!!
};

void GString::Prefix(cstr Pref) {
	if (NULL == Pref || 0 == Pref[0]) return;
	uint addLen = strlen(Pref);
	uint oldLen = m_data.Size();
	m_data.SetSize(oldLen + addLen);
	if (m_last.Found) m_last.Found += addLen;
	// Shift existing string 
	_ShiftRight((pchar)m_data.Addr(), oldLen + 1, addLen);
	// Insert new prefix at the beginig
	memcpy(m_data.Addr(), Pref, addLen);
};

void GString::Cut(uint Count, ZPosition From) {
	uint strLen = m_data.Size();
	if (Count >= strLen) {
		m_data.SetSize(0);
		return;
	}
	uint newLen = strLen - Count;
	puchar pTo = (puchar)m_data.Addr(); // Location of the first char of new string
	if (ZHead == From) {
		// Shift existing string 
		puchar pFrom = pTo + Count; // The first char of the tail of the string
		for (uint i = 0; i < newLen + 1; i++) { // Copy null character also
			*pTo++ = *pFrom++;
		}
		if (m_last.Found > Count) {
			m_last.Found -= Count;
		}
		else {
			m_last.Found = 0;
		}
	}
	else { // ZTail is Position
		*(pTo + newLen) = 0;
		if (m_last.Found > newLen) m_last.Found = 0;
	}
	m_data.SetSize(newLen);
};

void GString::Convert(ZStrConversionCode Code) {
	pchar pStr = (pchar)m_data.Addr();
	m_last.Found = 0; // drop the selection (if any)
	if (IsEmpty(pStr)) return;
	switch (Code) {
		case ZUpperCase: {
			CharUpper(pStr);
		} break;
		case ZLowerCase: {
			CharLower(pStr);
		} break;
		case ZNameStyle: {
			CharLower(pStr);
			pStr[0] = (char)CharUpper((pchar)pStr[0]);
		} break;
		case ZOEM: {
			CharToOem(pStr, pStr);
		} break;
		case ZANSI: {
			OemToChar(pStr, pStr);
		} break;
	}
}

void GString::Revert(void) {
	pchar pStr = (pchar)m_data.Addr();
	m_last.Found = 0; // drop the selection (if any)
	uint strLen = m_data.Size();
	if (!strLen) return;
	for (uint i = 0; i < (strLen >> 1); i++) {
		char tmp = pStr[i];
		pStr[i] = pStr[strLen - i - 1];
		pStr[strLen - i - 1] = tmp;
	}
}

char GString::Chr(uint Start) const {
	uint strLen = m_data.Size();
	if (!strLen) return 0;
	if (!Start) {
		XErrorSetLast(E_INVALIDARG, "Start 0 adjusted to 1", PCL_ELEV_(NOTIFICATION));
		XErrorSignal("GString::Chr");
		Start = 1;
	}
	if (Start-- > strLen) return 0; // Adjust Start to [0..Size() - 1]
	pchar pChr = (pchar)m_data.Addr();
	return *(pChr + Start);
}

void GString::SetChr(uint Start, char NewChr) {
	uint strLen = m_data.Size();
	if (!strLen) return;
	if (!Start) {
		XErrorSetLast(E_INVALIDARG, "Start 0 adjusted to 1", PCL_ELEV_(NOTIFICATION));
		XErrorSignal("GString::SetChr");
		Start = 1;
	}
	if (Start-- > strLen) return; // Adjust Start to [0..Size() - 1]
	pchar pChr = (pchar)m_data.Addr();
	*(pChr + Start) = NewChr;
}

cstr GString::SubStr(uint Start, uint Count) {
	uint strLen = m_data.Size();
	if (!strLen) return NULL;
	if (!Start) {
		XErrorSetLast(E_INVALIDARG, "Start 0 adjusted to 1", PCL_ELEV_(NOTIFICATION));
		XErrorSignal("GString::SubStr");
		Start = 1;
	}
	if (Start-- > strLen) return NULL; // Adjust Start to [0..Size() - 1]
	if (Count > strLen) Count = strLen - Start; // Two steps for BIG (Near to MAXUINT) Count
	if (Start + Count > strLen) Count = strLen - Start;
	if (!Count) return NULL;
	m_clip.SetSize(Count);
	pchar pDst = (pchar)m_clip.Addr();
	pchar pSrc = (pchar)m_data.Addr();
	memcpy(pDst, pSrc + Start, Count);
	*(pDst + Count) = 0;
	return pDst;
}

void GString::Select(uint Start, uint Count) {
	uint strLen = m_data.Size();
	if (Start > strLen) Start = strLen + 1;
	if (Start) {
		m_last.Found = Start--; // Adjust Start to [0..Size() - 1]
	}
	else {
		m_last.Found = 1;
	}
	if (Count > strLen) Count = strLen - Start; // Two steps for BIG (Near to MAXUINT) Count
	if (Start + Count > strLen) Count = strLen - Start;
	m_clip.SetSize(0);
	m_last.Len = Count;
}

static const uint s_modeFind = 1;
static const uint s_modeAny = 2;
static const uint s_modeNot = 4;

uint GString::FindChr(char SearchChar, ZPosition From) {
	m_last.Mode = s_modeFind;
	m_last.Found = 0;
	m_last.Pos = From;
	if (!m_data.Size()) return 0;

	pchar pData = (pchar)m_data.Addr();
	pchar pRes;
	if (ZHead == From) {
		pRes = strchr(pData, SearchChar);
	} else {
		pRes = strrchr(pData, SearchChar);
	}
	if (!pRes) return 0;
	m_last.Found = (pRes - pData) + 1;
	m_clip.SetSize(1);
	pchar pClip = (pchar)m_clip.Addr();
	pClip[0] = SearchChar;
	pClip[1] = 0;
	m_last.Len = 1;
	return m_last.Found;
}

uint GString::FindStr(cstr SearchStr, ZPosition From) {
	uint strLen = m_data.Size();
	m_last.Mode = s_modeFind;
	m_last.Found = 0;
	m_last.Pos = From;
	if (NULL == SearchStr || 0 == SearchStr[0]) return 0;
	if (!strLen) return 0;

	m_last.Len = strlen(SearchStr);
	if (m_last.Len > strLen) return 0;
	m_clip.SetSize(m_last.Len);
	memcpy(m_clip.Addr(), SearchStr, m_last.Len + 1);
	m_last.Found = (ZHead == From) ? 1 : strLen;
	return _FindNext();
}

uint GString::FindAny(cstr SearchStr, ZPosition From) {
	uint strLen = m_data.Size();
	m_last.Mode = s_modeAny;
	m_last.Found = 0;
	m_last.Pos = From;
	if (NULL == SearchStr || 0 == SearchStr[0]) return 0;
	if (!strLen) return 0;
	m_last.Found = (ZHead == From) ? 1 : strLen;
	uint sStrLen = strlen(SearchStr);
	m_clip.SetSize(sStrLen);
	memcpy(m_clip.Addr(), SearchStr, sStrLen + 1);
	m_last.Len = 1;
	return _FindAny();
}

uint GString::FindNot(cstr SearchStr, ZPosition From) {
	uint strLen = m_data.Size();
	m_last.Mode = s_modeNot;
	m_last.Found = 0;
	m_last.Pos = From;
	if (!strLen) return 0;
	m_last.Found = (ZHead == From) ? 1 : strLen;
	if (NULL == SearchStr || 0 == SearchStr[0]) return m_last.Found;
	uint sStrLen = strlen(SearchStr);
	m_clip.SetSize(sStrLen);
	memcpy(m_clip.Addr(), SearchStr, sStrLen + 1);
	m_last.Len = 1;
	return _FindNot();
}

uint GString::FindNext(void) {
	if (!m_last.Found) return 0;
	if (ZHead == m_last.Pos) {
		m_last.Found += m_last.Len;
	}
	else {
		m_last.Found--;
	}
	switch (m_last.Mode) {
		case s_modeFind: return _FindNext();
		case s_modeAny: return _FindAny();
		case s_modeNot: return _FindNot();
		default: return 0;
	}
}

uint GString::_FindNext(void) {
	if (!m_last.Found) return 0;
	uint strLen = m_data.Size();
	if (m_last.Found > strLen || !m_last.Len) {
		m_last.Found = 0;
		return 0;
	}
	pchar pStream = (pchar)m_data.Addr();
	pStream += m_last.Found - 1;
	pchar pSearch = (pchar)m_clip.Addr();
	pchar pRes = NULL;
	bool found = false;
	uint chrCount;
	if (ZHead == m_last.Pos) { // Direct Find
		chrCount = strLen - m_last.Found + 1;
		m_last.Found = 0;
		while(!found) {
			pchar pPatt = pSearch;
			while (chrCount) {
				if (*pPatt == *pStream) break;
				pStream++;
				chrCount--;
			}
			if (!chrCount) break;
			uint matchCount = 1;
			pRes = pStream;
			do {
				if (matchCount++ == m_last.Len) {
					found = true;
					break;
				}
				if (*(++pPatt) != *(++pStream)) break;
				chrCount--;
			} while (chrCount);
			if (!chrCount) break;
		}
	}
	else { // Reverse Find
		pSearch += m_last.Len - 1;
		chrCount = m_last.Found;
		m_last.Found = 0;
		while(!found) {
			pchar pPatt = pSearch;
			while (chrCount) {
				if (*pPatt == *pStream) break;
				pStream--;
				chrCount--;
			}
			if (!chrCount) break;
			uint matchCount = 1;
			do {
				if (matchCount++ == m_last.Len) {
					found = true;
					break;
				}
				if (*(--pPatt) != *(--pStream)) break;
				chrCount--;
			} while (chrCount);
			if (!chrCount) break;
		}
		pRes = pStream;
	}
	if (found) m_last.Found = (pRes - (pchar)m_data.Addr()) + 1;
	return m_last.Found;
}

uint GString::_FindAny(void) {
	pchar pSet = (pchar)m_clip.Addr();
	uint chrCount;
	pchar pData;
	if (ZHead == m_last.Pos) { // Direct Find
		chrCount = m_data.Size() - m_last.Found + 1;
		pData = (pchar)m_data.Addr() + m_last.Found - 1;
		uint base = m_last.Found;
		m_last.Found = 0;
		for (uint i = 0; i < chrCount; i++) {
			if (NULL != strchr(pSet, pData[i])) {
				m_last.Found = base + i;
				break;
			}
		}
	}
	else { // Reverse Find
		chrCount = m_last.Found;
		pData = (pchar)m_data.Addr();
		m_last.Found = 0;
		for (uint i = chrCount; i > 0; i--) {
			if (NULL != strchr(pSet, pData[i - 1])) {
				m_last.Found = i;
				break;
			}
		}
	}
	return m_last.Found;
}

uint GString::_FindNot(void) {
	pchar pSet = (pchar)m_clip.Addr();
	uint chrCount;
	pchar pData;
	if (ZHead == m_last.Pos) { // Direct Find
		chrCount = m_data.Size() - m_last.Found + 1;
		pData = (pchar)m_data.Addr() + m_last.Found - 1;
		uint base = m_last.Found;
		m_last.Found = 0;
		for (uint i = 0; i < chrCount; i++) {
			if (NULL == strchr(pSet, pData[i])) {
				m_last.Found = base + i;
				break;
			}
		}
	}
	else { // Reverse Find
		chrCount = m_last.Found;
		pData = (pchar)m_data.Addr();
		m_last.Found = 0;
		for (uint i = chrCount; i > 0; i--) {
			if (NULL == strchr(pSet, pData[i - 1])) {
				m_last.Found = i;
				break;
			}
		}
	}
	return m_last.Found;
}

void GString::Replace(cstr ReplExp) {
	if (!m_last.Found) {
		XErrorSetLast(E_FAIL, "Nothing was found/selected");
		XErrorSignal("GString::Replace");
		return;
	}
	uint replen = ReplExp ? strlen(ReplExp) : 0;
	int shift = replen - m_last.Len;
	uint strLen = m_data.Size();
	m_data.SetSize(strLen + shift);
	pchar pStartRepl = (pchar)m_data.Addr() + m_last.Found - 1;
	pchar pStartTail = pStartRepl + m_last.Len;
	uint taillen = strlen(pStartTail) + 1;
	if (shift > 0) {
		_ShiftRight(pStartTail, taillen, shift);
	}
	else if (shift < 0) {
		uint ushift = 0 - shift;
		_ShiftLeft(pStartTail, taillen, ushift);
	}
	if (replen) memcpy(pStartRepl, ReplExp, replen);
}

cstr GString::Body() const {
	return (cstr)m_data.Addr();
};

GString::operator cstr() const {
	return Body();
};

char& GString::operator [](ZPosition Pos) {
	static char s_nil = 0;
	pchar pData = (pchar)m_data.Addr();
	if (!pData) return s_nil;
	if (ZTail == Pos) pData += m_data.Size() - 1;
	return pData[0];
}

cstr GString::operator ()(uint Start) {
	return SubStr(Start);
}

cstr GString::operator ()(uint Start, uint End) {
	if (Start <= End) return SubStr(Start, End + 1 - Start);
	return SubStr(End, Start + 1 - End);
};

void GString::ImportUnicode(
	ustr Src,
	bool AutoRelease,
	ZMemAdmType MemAdmCode
) {
	m_last.Found = 0; // drop the selection (if any)
	int srcLen;
	if (!Src || !(srcLen  = wcslen(Src))) {
		m_data.SetSize(0);
		return;
	}
	int nBytes = WideCharToMultiByte(CP_ACP, 0, Src, srcLen, NULL, 0,
		NULL, NULL
	);
	m_data.SetSize(srcLen);
	pchar pDst = (pchar)m_data.Addr();
	WideCharToMultiByte(CP_ACP, 0, Src, srcLen, pDst, nBytes,
		NULL, NULL
	);
	pDst[srcLen] = 0;
	if (AutoRelease) LGetMemAdm(MemAdmCode)->Dealloc(Src);
};

ustr GString::ExportUnicode(void) {
	uint strLen = m_data.Size();
	if (!strLen) return NULL;
	pchar pSrc = (pchar)m_data.Addr();
	int nLen = MultiByteToWideChar(CP_ACP, 0, pSrc, strLen,
		NULL, NULL
	);
	ustr Result = (ustr)LMem.Unicode->Alloc(nLen);
	MultiByteToWideChar(CP_ACP, 0, pSrc, strLen,
		Result, nLen
	);
	return Result;
};

void GString::ImportRes(uint ResID, pvoid Module) {
	char str[MAX_PATH];
	if (!Module) Module = LGetModuleHandle();
	uint len = (uint)LoadString((HINSTANCE)Module, ResID, str, MAX_PATH);
	m_data.SetSize(len);
	if (len) memcpy(m_data.Addr(), str, len + 1);
}

void GString::ImportEnv(cstr Name) {
	m_last.Found = 0; // drop the selection (if any)
	uint len = GetEnvironmentVariable(Name, NULL, 0);
	if (!len) {
		m_data.SetSize(0);
	}
	else {
		m_data.SetSize(len - 1);
		GetEnvironmentVariable(Name, (pchar)m_data.Addr(), len);
	}
}

void GString::ExportEnv(cstr Name) {
	if (!SetEnvironmentVariable(
			Name, 
			m_data.Size() 
				? (pchar)m_data.Addr() 
				: NULL
		)) {
		XErrorSetLast(GetLastError(), "Cannot set environment variable");
		XErrorSignal("GString::ExportEnv");
	}
}

static const uint s_maxExpLen = 20;
void GString::ImportInt(int Src, cstr Format) {
	if (!Format) {
		XErrorSetLast(E_FAIL, "Null Format pointer");
		XErrorSignal("GString::ImportInt");
	}
	pchar pbuf = (pchar)LMem.Std->Alloc(strlen(Format) + s_maxExpLen);
	sprintf(pbuf, Format, Src);
	SetBody(pbuf);
	LMem.Std->Dealloc(pbuf);
}

void GString::ImportHex(uint Src, cstr Format) {
	if (!Format) {
		XErrorSetLast(E_FAIL, "Null Format pointer");
		XErrorSignal("GString::ImportHex");
	}
	pchar pbuf = (pchar)LMem.Std->Alloc(strlen(Format) + s_maxExpLen);
	sprintf(pbuf, Format, Src);
	SetBody(pbuf);
	LMem.Std->Dealloc(pbuf);
}

void GString::ImportDbl(double Src, cstr Format) {
	if (!Format) {
		XErrorSetLast(E_FAIL, "Null Format pointer");
		XErrorSignal("GString::ImportDbl");
	}
	pchar pbuf = (pchar)LMem.Std->Alloc(strlen(Format) + s_maxExpLen);
	sprintf(pbuf, Format, Src);
	SetBody(pbuf);
	LMem.Std->Dealloc(pbuf);
}

///! Implementation of LString
LString::LString(cstr Body) {
	m_data.SetSize(InitialLen());
	m_clip.SetSize(0);
	SetBody(Body);
};

LString::LString(LString &Copy) {
	m_data.SetSize(InitialLen());
	m_clip.SetSize(0);
	SetBody(Copy);
}

LString::~LString() {
//	m_data.SetSize(0);
//	m_clip.SetSize(0);
};

LString::LString(const pcont pContainer) {
	m_data.SetSize(0);
	m_clip.SetSize(0);
	Import(pContainer);
};

const pcont LString::Export() {
	return GString::Export();
};

void LString::Import(const pcont pContainer, bool AutoRelease) {
	GString::Import(pContainer, AutoRelease);
};

// Asigments
const VString& LString::operator =(LString& Src) {
	SetBody((cstr)Src);
	return *this;
}

const VString& LString::operator =(cstr Src) {
	SetBody(Src);
	return *this;
}

const VString& LString::operator +=(cstr Src) {
	Append(Src);
	return *this;
}

const VString& LString::operator ^=(cstr Src) {
	Prefix(Src);
	return *this;
}

