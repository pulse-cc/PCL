#ifndef __PCL_ROOT_H__ 
#define __PCL_ROOT_H__ 
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
///! PCL Class Code Generation
///!
static const uint VIRTUALCODE(bool IsContainer) {
	static uint Number = 0;
	if (!Number++) return PCL_PREFIX | PCL_CONTAINER_MASK; // Special case for VContainer
	return PCL_PREFIX | (IsContainer ? PCL_CONTAINER_MASK : 0) | (Number++ << 7);
}
static const uint CLASSCODE(uint BaseCode) {
	static uint Number = 0;
	if (++Number == 256) Number = 1;
	return (BaseCode & 0xFFFFFF00uL) | Number;
}
///!===========================================================================!
///!
///! Virtual Container: serializable classes root
///!
static const uint VContainerClassCode = VIRTUALCODE(false); class VContainer { public:
///!
///! Public Methods
///!
public:
	virtual const pcont Export(void) =0;
	virtual void Import(const pcont pContainer, bool AutoRelease = true) =0;
};
///!===========================================================================!
///!
///! Virtual Class: Memory Manager
///!
static const uint VMemAdmClassCode = VIRTUALCODE(false); class VMemAdm { public:
///!
///! Public Methods
///!
public:
	virtual pvoid Alloc(uint Size) =0;
	virtual pvoid Realloc(pvoid ptr, uint Size) =0;
	virtual void Dealloc(pvoid ptr) =0;
};
///!===========================================================================!
///!
///! Global Scope Definition
///!
typedef enum PCL_MemAdmType { ZNullMemAdmType = 0,
	ZMemDefault	= 0, // placeholder for any of the following:
///!
	ZMemStd		= 1,
	ZMemCOM		= 2,
	ZMemCustom	= 3,
	ZMemUnicode	= 4,
///!
	ZMemAdmCount
} ZMemAdmType;
///!===========================================================================!
///!
///! Virtual Memory Chunk
///!
static const uint VMemoryClassCode = VIRTUALCODE(false); class VMemory { public:
///!
///! Public Methods
///!
public:
	virtual uint Size(void) const =0;
	virtual void SetSize(uint NewSize) =0;
	virtual puchar Addr(void) const =0;
};
///!===========================================================================!
///!
///! Virtual Item (Descriptor)
///!
static const uint VItemClassCode = VIRTUALCODE(false); class VItem { public:
///!
///! Public Methods
///!
public:
	virtual uint ClassCode(void) const =0;
	virtual void SetClassCode(uint NewClassCode) =0;
	virtual uint Size(void) const =0;
	virtual void SetSize(uint NewSize) =0;
	virtual puchar Addr(void) const =0;
	virtual void SetAddr(puchar NewAddr) =0;
	virtual uint Info(void) const =0;
	virtual void SetInfo(uint NewInfo) =0;
///!
///! Public Operators
///!
public:
	virtual operator puchar() const =0; // operator form of .Addr()
	virtual operator pvoid() const =0; // operator form of .Addr()
};
///!===========================================================================!
///!
///! Virtual Critical Section
///!
static const uint VCSectClassCode = VIRTUALCODE(false); class VCSect { public:
///!
///! Public Methods
///!
public:
	virtual void Lock(void) =0;
	virtual void Unlock(void) =0;
	virtual bool TryLock(void) =0; // true if locked
};
///!===========================================================================!
///!
///! Virtual Root: assumed one object per application
///!
static const uint VRootClassCode = VIRTUALCODE(false); class VRoot { public:
	virtual uint Check(void) =0;
};
///!===========================================================================!
///!
///! Virtual Event
///!
static const uint VEventClassCode = VIRTUALCODE(false); class VEvent { public:
///!
///! Public Methods
///!
public:
	virtual void Signal(void) =0;
	virtual void Clear(void) =0;
	virtual void Pulse(void) =0;
	virtual bool Wait(sint Timeout = INFINITE) =0; // false if timed-out
};
///!===========================================================================!
///!
///! Virtual Mutex
///!
static const uint VMutexClassCode = VIRTUALCODE(false); class VMutex { public:
///!
///! Public Methods
///!
public:
	virtual void Release(void) =0;
	virtual bool Wait(sint Timeout = INFINITE) =0; // false if timed-out
};
///!===========================================================================!
///!
///! Virtual Class Codes for fundamental types
///!
static const uint VpvoidClassCode = VIRTUALCODE(false);
static const uint VcharClassCode = VIRTUALCODE(false);
static const uint VucharClassCode = VIRTUALCODE(false);
static const uint VshortClassCode = VIRTUALCODE(false);
static const uint VushortClassCode = VIRTUALCODE(false);
static const uint VsshortClassCode = VIRTUALCODE(false);
static const uint VintClassCode = VIRTUALCODE(false);
static const uint VuintClassCode = VIRTUALCODE(false);
static const uint VsintClassCode = VIRTUALCODE(false);
static const uint VlongClassCode = VIRTUALCODE(false);
static const uint VulongClassCode = VIRTUALCODE(false);
static const uint VslongClassCode = VIRTUALCODE(false);
static const uint VfloatClassCode = VIRTUALCODE(false);
static const uint VdoubleClassCode = VIRTUALCODE(false);
static const uint VcstrClassCode = VIRTUALCODE(false);
static const uint VustrClassCode = VIRTUALCODE(false);
///!===========================================================================!
///!
///! Other Stuff
///!
typedef enum PCL_RegistrySection { ZNullRegistrySection = 0,
	ZClassInfo,
	ZSystemInfo,
	ZUserInfo,
} ZRegistrySection;
///!
typedef enum PCL_AccessMode { ZNullAccessMode = 0,
	ZNoAccess	= 0,
	ZRead		= 0x1,
	ZWrite		= ZRead << 1,
	ZUpdate		= ZRead | ZWrite,
} ZAccessMode;
///!
typedef enum PCL_ControlState { ZNullControlState = 0,
	ZOn = 0x1,
	ZOff = ZOn << 1,
	ZAuto = ZOn | ZOff, // For typical buttons
	ZPulse = ZAuto,
// Modifiers
	ZInvisible		= 0x40000000uL,
	ZDisabled		= ZInvisible >> 1,
} ZControlState;
///!
class LException; // Forward declaration (for implementation debug aids)
///!
///!===========================================================================!
///!
///! Definition of Generic Memory Manager GMemAdm 
///!
static const uint GMemAdmClassCode = CLASSCODE(VMemAdmClassCode); class PCL_API GMemAdm : public VMemAdm { public: static const uint ClassCode() {return GMemAdmClassCode;}; protected: GMemAdm(); virtual ~GMemAdm(); protected:
	// Inheritable variables and methods
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);
///!
///! Public Methods
///!
public:
	virtual pvoid Alloc(uint Size) ;
	virtual pvoid Realloc(pvoid ptr, uint Size) ;
	virtual void Dealloc(pvoid ptr) ;
};
///!===========================================================================!
///!
///! Definition of Memory Manager LMemAdm 
///!	use stdlib calls 'malloc', 'realloc', 'free'
///!
static const uint LMemAdmClassCode = CLASSCODE(GMemAdmClassCode); class PCL_API LMemAdm : public GMemAdm { public: static const uint ClassCode() {return LMemAdmClassCode;}; public:
protected:
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);
};
///!===========================================================================!
///!
///! Definition of Memory Manager LMemCOM use IMalloc
///!
static const uint LMemAdmCOMClassCode = CLASSCODE(GMemAdmClassCode); class PCL_API LMemAdmCOM : public GMemAdm { public: static const uint ClassCode() {return LMemAdmCOMClassCode;}; public:
protected:
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);
};
///!===========================================================================!
///!
///! Definition of Memory Manager LMemAdmUnicode 
///!	use SysAllocString...SysFreeString
///!
static const uint LMemAdmUnicodeClassCode = CLASSCODE(GMemAdmClassCode); class PCL_API LMemAdmUnicode : public GMemAdm { public: static const uint ClassCode() {return LMemAdmUnicodeClassCode;}; public:
protected:
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);
};
///!===========================================================================!
///!
///! Definition of Memory Chunk
///!
static const uint LMemoryClassCode = CLASSCODE(VMemoryClassCode); class PCL_API LMemory : public VMemory { public: static const uint ClassCode() {return LMemoryClassCode;}; public:
	LMemory(uint IniLength = 0);
	virtual ~LMemory();
///!
///! Public Methods
///!
public:
	virtual uint Size(void) const ;
	virtual void SetSize(uint NewSize) ;
	virtual puchar Addr(void) const ;
private:
	uint m_len, m_allocLen;
	pvoid m_addr;
};
///!===========================================================================!
///!
///! Definition of Item Descriptor
///!
static const uint LDescrClassCode = CLASSCODE(VItemClassCode);
class PCL_API LDescr : public VItem { // Doesn't have static .ClassCode method
public:
	LDescr(	// Generic constructor
		puchar Addr = NULL,
		uint Size = 0,
		uint ClassCode = ZUintInvalid,
		uint Info = 0
	);
	LDescr(const LDescr &Copy);
	LDescr(const pZItem pItem);
	LDescr(const uint &Item, uint Info = 0);
	LDescr(const sint &Item, uint Info = 0);
	LDescr(const float &Item, uint Info = 0);
	LDescr(const double &Item, uint Info = 0);
	LDescr(cstr Item, uint Info = 0);
	LDescr(ustr Item, uint Info = 0);
///!
///! Public Methods
///!
public:
	virtual uint ClassCode(void) const ;
	virtual void SetClassCode(uint NewClassCode) ;
	virtual uint Size(void) const ;
	virtual void SetSize(uint NewSize) ;
	virtual puchar Addr(void) const ;
	virtual void SetAddr(puchar NewAddr) ;
	virtual uint Info(void) const ;
	virtual void SetInfo(uint NewInfo) ;
///!
///! Public Operators
///!
public:
	virtual operator puchar() const ; // operator form of .Addr()
	virtual operator pvoid() const ; // operator form of .Addr()
private:
	ZItem m_item;
};
///!===========================================================================!
///!
///! Definition of Critical Section
///!
static const uint LCSectClassCode = CLASSCODE(VCSectClassCode); class PCL_API LCSect : public VCSect { public: static const uint ClassCode() {return LCSectClassCode;}; public:
	LCSect();
///!
///! Public Methods
///!
public:
	virtual void Lock(void) ;
	virtual void Unlock(void) ;
	virtual bool TryLock(void) ; // true if locked
private:
	CRITICAL_SECTION m_cs;
};
///!===========================================================================!
///!
///! Definition of Root
///!
static const uint LRootClassCode = CLASSCODE(VRootClassCode); class PCL_API LRoot : public VRoot { public: static const uint ClassCode() {return LRootClassCode;}; public:
	LRoot(uint Reserved);
	~LRoot();
	virtual uint Check(void) ;
	static const uint VMajor(void) {return PCL_VERMAJOR;};
	static const uint VMinor(void) {return PCL_VERMINOR;};
	static const bool IsDebug(void) {return PCL_ISDEBUG;};
private:
	uint m_initCode;
};
///!===========================================================================!
///!
///! Definition of Event
///!
///! Event type: been signaled, the event releases
///! either one of or all the waiting threads
///!
typedef enum PCL_EventReleaseMode {
	ZEventReleaseOne,
	ZEventReleaseAll
} ZEventReleaseMode;
///!
static const uint LEventClassCode = CLASSCODE(VEventClassCode); class PCL_API LEvent : public VEvent { public: static const uint ClassCode() {return LEventClassCode;}; public:
	LEvent(ZEventReleaseMode Type = ZEventReleaseOne);
///!
///! Public Methods
///!
public:
	virtual void Signal(void) ;
	virtual void Clear(void) ;
	virtual void Pulse(void) ;
	virtual bool Wait(sint Timeout = INFINITE) ; // false if timed-out
private:
	ZEventReleaseMode m_type;
	HANDLE m_hEvent;
};
///!===========================================================================!
///!
///! Definition of Mutex (Binary Semaphore)
///!
static const uint LMutexClassCode = CLASSCODE(VMutexClassCode); class PCL_API LMutex : public VMutex { public: static const uint ClassCode() {return LMutexClassCode;}; public:
	LMutex(bool InitialyOwned = true);
///!
///! Public Methods
///!
public:
	virtual void Release(void) ;
	virtual bool Wait(sint Timeout = INFINITE) ; // false if timed-out
private:
	HANDLE m_hMutex;
};
#endif // __PCL_ROOT_H__ 
