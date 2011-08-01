#define PCL_GENDEFRUN
#define __PCL_H__
#include "PCL_License.h"
#include "PCL_Internal.h"
#include "PCL_ClassCode.h"

#define PCL_PURE =0
///!===========================================================================!
///!
///! Virtual Container: serializable classes root
///!
PCL_VIRTUAL_CLASS(Container):
#include "PCL_VContainer.hxx"
};
///!===========================================================================!
///!
///! Virtual Class: Memory Manager
///!
PCL_VIRTUAL_CLASS(MemAdm):
#include "PCL_VMemAdm.hxx"
};
///!===========================================================================!
///!
///! Global Scope Definition
///!
PCL_ENUMERATOR(MemAdmType)
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
PCL_VIRTUAL_CLASS(Memory):
#include "PCL_VMemory.hxx"
};

///!===========================================================================!
///!
///! Virtual Item (Descriptor)
///!
PCL_VIRTUAL_CLASS(Item):
#include "PCL_VItem.hxx"
};
///!===========================================================================!
///!
///! Virtual Critical Section
///!
PCL_VIRTUAL_CLASS(CSect):
#include "PCL_VCSect.hxx"
};
///!===========================================================================!
///!
///! Virtual Root: assumed one object per application
///!
PCL_VIRTUAL_CLASS(Root):
#include "PCL_VRoot.hxx"
};
///!===========================================================================!
///!
///! Virtual Event
///!
PCL_VIRTUAL_CLASS(Event):
#include "PCL_VEvent.hxx"
};
///!===========================================================================!
///!
///! Virtual Mutex
///!
PCL_VIRTUAL_CLASS(Mutex):
#include "PCL_VMutex.hxx"
};
///!===========================================================================!
///!
///! Virtual Class Codes for fundamental types
///!
PCL_VIRTUAL_CLASSCODE(pvoid, false)
PCL_VIRTUAL_CLASSCODE(char, false)
PCL_VIRTUAL_CLASSCODE(uchar, false)
PCL_VIRTUAL_CLASSCODE(short, false)
PCL_VIRTUAL_CLASSCODE(ushort, false)
PCL_VIRTUAL_CLASSCODE(sshort, false)
PCL_VIRTUAL_CLASSCODE(int, false)
PCL_VIRTUAL_CLASSCODE(uint, false)
PCL_VIRTUAL_CLASSCODE(sint, false)
PCL_VIRTUAL_CLASSCODE(long, false)
PCL_VIRTUAL_CLASSCODE(ulong, false)
PCL_VIRTUAL_CLASSCODE(slong, false)
PCL_VIRTUAL_CLASSCODE(float, false)
PCL_VIRTUAL_CLASSCODE(double, false)
PCL_VIRTUAL_CLASSCODE(cstr, false)
PCL_VIRTUAL_CLASSCODE(ustr, false)
///!===========================================================================!
///!
///! Other Stuff
///!
PCL_ENUMERATOR(RegistrySection)
	ZClassInfo,
	ZSystemInfo,
	ZUserInfo,
} ZRegistrySection;
///!
PCL_ENUMERATOR(AccessMode)
	ZNoAccess	= 0,
	ZRead		= 0x1,
	ZWrite		= ZRead << 1,
	ZUpdate		= ZRead | ZWrite,
} ZAccessMode;
///!
PCL_ENUMERATOR(ControlState)
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
#undef PCL_PURE
#define PCL_PURE /**/
///!
///! Definition of Generic Memory Manager GMemAdm 
///!
#include "PCL_GMemAdm.hxx"
///!===========================================================================!
///!
///! Definition of Memory Manager LMemAdm 
///!	use stdlib calls 'malloc', 'realloc', 'free'
///!
PCL_CLASS_OF(GMemAdm, MemAdm):
protected:
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);
};
///!===========================================================================!
///!
///! Definition of Memory Manager LMemCOM use IMalloc
///!
PCL_CLASS_OF(GMemAdm, MemAdmCOM):
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
PCL_CLASS_OF(GMemAdm, MemAdmUnicode):
protected:
	virtual pvoid _Alloc(uint Size);
	virtual pvoid _Realloc(pvoid ptr, uint Size);
	virtual void _Dealloc(pvoid ptr);
};
///!===========================================================================!
///!
///! Definition of Memory Chunk
///!
PCL_CLASS(Memory):
	LMemory(uint IniLength = 0);
	virtual ~LMemory();

#include "PCL_VMemory.hxx"

private:
	uint m_len, m_allocLen;
	pvoid m_addr;
};
///!===========================================================================!
///!
///! Definition of Item Descriptor
///!
PCL_CLASSCODE(Descr, VItemClassCode)

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

#include "PCL_VItem.hxx"

private:
	ZItem m_item;
};
///!===========================================================================!
///!
///! Definition of Critical Section
///!
PCL_CLASS(CSect):
	LCSect();

#include "PCL_VCSect.hxx"

private:
	CRITICAL_SECTION m_cs;
};
///!===========================================================================!
///!
///! Definition of Root
///!
PCL_CLASS(Root):
	LRoot(uint Reserved);
	~LRoot();

#include "PCL_VRoot.hxx"

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
PCL_CLASS(Event):
	LEvent(ZEventReleaseMode Type = ZEventReleaseOne);

#include "PCL_VEvent.hxx"

private:
	ZEventReleaseMode m_type;
	HANDLE m_hEvent;
};
///!===========================================================================!
///!
///! Definition of Mutex (Binary Semaphore)
///!
PCL_CLASS(Mutex):
	LMutex(bool InitialyOwned = true);

#include "PCL_VMutex.hxx"

private:
	HANDLE m_hMutex;
};
