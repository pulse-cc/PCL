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

///! Base Memory Manager
GMemAdm::GMemAdm() {
}
GMemAdm::~GMemAdm() {
}
pvoid GMemAdm::Alloc(uint Size) {
	pvoid res = _Alloc(Size);
	if (!Size) {
		XErrorSetLast(
			E_INVALIDARG,
			"Zero Size Memory Request",
			PCL_ELEV_(RECOVERABLE)
		);
	}
	else if (!res) {
		XErrorSetLast(E_OUTOFMEMORY, "Not enough memory");
	}
	XErrorSignal("GMemAdm::Alloc");
	return res;
}
pvoid GMemAdm::Realloc(pvoid Ptr, uint Size) {
	pvoid res = _Realloc(Ptr, Size);
	if (!Size) {
		XErrorSetLast(
			E_INVALIDARG,
			"Zero Size Memory Request",
			PCL_ELEV_(RECOVERABLE)
		);
	}
	else if (!res) {
		XErrorSetLast(E_OUTOFMEMORY, "Not enough memory");
	}
	XErrorSignal("GMemAdm::Realloc");
	return res;
}
void GMemAdm::Dealloc(pvoid Ptr) {
	if (Ptr) _Dealloc(Ptr);
	return;
}
pvoid GMemAdm::_Alloc(uint Size) {
	LTerminate("GMemAdm::_Alloc() called");
	return NULL;
}
pvoid GMemAdm::_Realloc(pvoid Ptr, uint Size) {
	LTerminate("GMemAdm::_Realloc() called");
	return NULL;
}
void GMemAdm::_Dealloc(pvoid Ptr) {
	LTerminate("GMemAdm::_Dealloc() called");
}

// Standard Memory Manager
pvoid LMemAdm::_Alloc(uint Size) {
	return malloc(Size);
}
pvoid LMemAdm::_Realloc(pvoid Ptr, uint Size) {
	return realloc(Ptr, Size);
}
void LMemAdm::_Dealloc(pvoid Ptr) {
	free(Ptr);
}

///! Memory Manager for COM applications
pvoid LMemAdmCOM::_Alloc(uint Size) {
	return CoTaskMemAlloc(Size);
}
pvoid LMemAdmCOM::_Realloc(pvoid ptr, uint Size) {
	return CoTaskMemRealloc(ptr, Size);
}
void LMemAdmCOM::_Dealloc(pvoid ptr) {
	CoTaskMemFree(ptr);
}

///! Memory Manager for Unicode Strings
pvoid LMemAdmUnicode::_Alloc(uint Size) {
	return (pvoid)SysAllocStringLen(NULL, Size);
}
pvoid LMemAdmUnicode::_Realloc(pvoid ptr, uint Size) {
	ustr pnew = NULL;
	SysReAllocStringLen(&pnew, (ustr)ptr, Size);
	_Dealloc(ptr);
	return pnew;
}
void LMemAdmUnicode::_Dealloc(pvoid ptr) {
	SysFreeString((ustr)ptr);
}

///! Memory Chunk
static const uint s_blockShift = 4;
LMemory::LMemory(uint IniSize) {
	m_len = 0;
	m_allocLen = 0;
	m_addr = NULL;
	if (IniSize) {
		SetSize(IniSize);
		memset(m_addr, 0, IniSize);
	}
}
LMemory::~LMemory(void) {
	if (m_addr) LMem.Std->Dealloc(m_addr);
}
uint LMemory::Size(void) const {
	return m_len;
}
void LMemory::SetSize(uint NewSize) {
	m_len = NewSize;
	if (!NewSize) return;
	if (m_allocLen <= NewSize) {
		uint delta = NewSize - m_allocLen;
		uint blockDelta = ((delta >> s_blockShift) + 1) << s_blockShift;
		m_allocLen += blockDelta;
		m_addr = LMem.Std->Realloc(m_addr, m_allocLen);
	}
}
puchar LMemory::Addr(void) const {
	return m_len ? (puchar)m_addr : NULL;
}

///! Descriptor
#define PCL_VCLASSCODE(ClassName) V##ClassName##ClassCode

template <class T> inline pZItem pItemOf(const T &Item, uint ClassCode, uint Info) {
	static ZItem s_item;
	s_item.Addr = (puchar)&Item;
	s_item.Size = sizeof(T);
	s_item.ClassCode = ClassCode;
	s_item.Info = Info;
	return &s_item;
}

LDescr::LDescr(puchar Addr, uint Size, uint ClassCode, uint Info) {
	m_item.Addr = Addr;
	m_item.Size = Size;
	m_item.ClassCode = ClassCode;
	m_item.Info = Info;
}
LDescr::LDescr(const LDescr &Copy) {
	memcpy(&m_item, &Copy.m_item, sizeof(ZItem));
}
LDescr::LDescr(const pZItem pItem) {
	memcpy(&m_item, pItem, sizeof(ZItem));
}
LDescr::LDescr(const uint &Item, uint Info) {
	memcpy(&m_item, pItemOf(Item, PCL_VCLASSCODE(uint), Info), sizeof(ZItem));
}
LDescr::LDescr(const sint &Item, uint Info) {
	memcpy(&m_item, pItemOf(Item, PCL_VCLASSCODE(sint), Info), sizeof(ZItem));
}
LDescr::LDescr(const float &Item, uint Info) {
	memcpy(&m_item, pItemOf(Item, PCL_VCLASSCODE(float), Info), sizeof(ZItem));
}
LDescr::LDescr(const double &Item, uint Info) {
	memcpy(&m_item, pItemOf(Item, PCL_VCLASSCODE(uint), Info), sizeof(ZItem));
}
LDescr::LDescr(cstr Item, uint Info) {
	memcpy(&m_item, pItemOf(Item, PCL_VCLASSCODE(cstr), Info), sizeof(ZItem));
	m_item.Size = strlen(Item);
}
LDescr::LDescr(ustr Item, uint Info) {
	memcpy(&m_item, pItemOf(Item, PCL_VCLASSCODE(ustr), Info), sizeof(ZItem));
	m_item.Size = wcslen(Item) << 1;
}
uint LDescr::ClassCode(void) const {
	return m_item.ClassCode;
}
void LDescr::SetClassCode(uint NewClassCode) {
	m_item.ClassCode = NewClassCode;
}
uint LDescr::Size(void) const {
	return m_item.Size;
}
void LDescr::SetSize(uint NewSize) {
	m_item.Size = NewSize;
}
puchar LDescr::Addr(void) const {
	return m_item.Addr;
}
void LDescr::SetAddr(puchar NewAddr) {
	m_item.Addr = NewAddr;
}
uint LDescr::Info(void) const {
	return m_item.Info;
}
void LDescr::SetInfo(uint NewInfo) {
	m_item.Info = NewInfo;
}
LDescr::operator puchar() const {
	return (puchar)m_item.Addr;
}
LDescr::operator pvoid() const {
	return (pvoid)m_item.Addr;
}

///! Critical Section
LCSect::LCSect() {
	::InitializeCriticalSection(&m_cs);
}
void LCSect::Lock(void) {
	::EnterCriticalSection(&m_cs);
}
void LCSect::Unlock(void) {
	::LeaveCriticalSection(&m_cs);
}
bool LCSect::TryLock(void) {
	return ::TryEnterCriticalSection(&m_cs) ? true : false;
}

///! Root
static bool s_rootCreated = false;
LRoot::LRoot(uint Reserved) {
	if (s_rootCreated) {
		XErrorSetLast(E_FAIL, "Another LRoot Forbidden", PCL_ELEV_(FATAL));
		XErrorSignal("LRoot::LRoot");
	}
	m_initCode = Reserved;
	Check();
	s_rootCreated = true;
}
LRoot::~LRoot() {
	LFinalize();
}
uint LRoot::Check(void) {
	static bool firstCall = true;
	if (firstCall) {
		LInitialize();
		OutputDebugString("PCL initialized\n");
		firstCall = false;
	}
	return m_initCode;
}

///! Event
LEvent::LEvent(ZEventReleaseMode Type) {
	m_type = Type;
	m_hEvent = ::CreateEvent(NULL, (Type == ZEventReleaseAll), FALSE, NULL);
	if (!m_hEvent) {
		XErrorSetLast(E_UNEXPECTED, "CreateEvent Fail");
		XErrorSignal("LEvent::LEvent");
	}
}
void LEvent::Signal(void) {
	if (!::SetEvent(m_hEvent)) {
		XErrorSetLast(E_UNEXPECTED, "SetEvent Fail");
		XErrorSignal("LEvent::Signal");
	}
	return;
}
void LEvent::Clear(void) {
	if (!::ResetEvent(m_hEvent)) {
		XErrorSetLast(E_UNEXPECTED, "ResetEvent Fail");
		XErrorSignal("LEvent::Clear");
	}
	return;
}
void LEvent::Pulse(void) {
	if (!::PulseEvent(m_hEvent)) {
		XErrorSetLast(E_UNEXPECTED, "PulseEvent Fail");
		XErrorSignal("LEvent::Pulse");
	}
	return;
}
bool LEvent::Wait(sint Timeout) {
	MSG winMsg;
	while (1) {
		switch (::MsgWaitForMultipleObjects(1L, &m_hEvent, FALSE, Timeout, 0)) {
			case WAIT_OBJECT_0: {
				return true;
			} break;
			case WAIT_TIMEOUT: {
				return false;
			} break;
			case WAIT_OBJECT_0 + 1: {
				::GetMessage(&winMsg, NULL, 0, 0);
				::TranslateMessage(&winMsg);
				::DispatchMessage(&winMsg);
			} break;
			default : {
				XErrorSetLast(
					E_UNEXPECTED,
					"Unknown return code from MsgWaitForMultipleObjects"
				);
				XErrorSignal("LEvent::Wait");
				return false;
			}
		}
	}
}

///! Mutex
LMutex::LMutex(bool InitialyOwned) {
	m_hMutex = ::CreateMutex(NULL, InitialyOwned, NULL);
}
void LMutex::Release(void) {
	if (!::ReleaseMutex(m_hMutex)) {
		XErrorSetLast(E_UNEXPECTED, "ReleaseMutex Fail");
		XErrorSignal("LMutex::Release");
	}
	return;
}
bool LMutex::Wait(sint Timeout) {
	MSG winMsg;
	while (1) {
		switch (::MsgWaitForMultipleObjects(1L, &m_hMutex, FALSE, Timeout, 0)) {
			case WAIT_OBJECT_0: {
				return true;
			} break;
			case WAIT_TIMEOUT: {
				return false;
			} break;
			case WAIT_OBJECT_0 + 1: {
				::GetMessage(&winMsg, NULL, 0, 0);
				::TranslateMessage(&winMsg);
				::DispatchMessage(&winMsg);
			} break;
			default : {
				XErrorSetLast(
					E_UNEXPECTED,
					"Unknown return code from MsgWaitForMultipleObjects"
				);
				XErrorSignal("LMutex::Wait");
				return false;
			}
		}
	}
}
