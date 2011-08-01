#ifndef __PCL_VIRTUAL_H__
#define __PCL_VIRTUAL_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif
///!===========================================================================!
///!
///! Virtual Class Codes for fundamental types
///!
PCL_VIRTUAL_CLASSCODE(void, false)
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
///! Virtual Iterator (Helper Class for navigation into Virtual Lists)
///!
///! Global Scope Definitions:
///!
PCL_ENUMERATOR(Position)
	ZHead,
	ZFirst = ZHead,
	ZTop = ZHead,
///!
	ZTail,
	ZLast = ZTail,
	ZBottom = ZTail,
} ZPosition;
///!
PCL_ENUMERATOR(Direction)
	ZPrev,
	ZUp = ZPrev,
	ZBackward = ZPrev,
///!
	ZNext,
	ZDown = ZNext,
	ZForward = ZNext,
} ZDirection;
PCL_VIRTUAL_CLASS(Iterator):
#include "PCL_VIterator.hxx"
};
///!===========================================================================!
///!
///! Virtual List (may be implemented as dynamic array or linked list or ...)
///!
///! Global Scope Definitions:
///!
///!	Pointer to user-defined filter function
PCL_FPTR(bool,ZFilter)(pvoid pItem); // true if item match criterium
///!	Pointer to user-defined sort ordering function
PCL_FPTR(bool,ZSortOrder)(pvoid pItem1, pvoid pItem2); // true if Greater
///!	Special reference value indicating default (built-in) iterator
static const VIterator *ZDefaultIterator = NULL;
PCL_VIRTUAL_CONTAINER_OF(Iterator, List):
#include "PCL_VList.hxx"
};
///!===========================================================================!
///!
///! Virtual String
///!
///! Global Scope Definitions:
///!
PCL_ENUMERATOR(StrConversionCode)
	ZUpperCase,
	ZLowerCase,
	ZOEM,
	ZANSI,
///!
	ZOEM_String = ZOEM,
	ZANSI_String = ZANSI,
	ZString_OEM = ZOEM,
	ZString_ANSI = ZANSI,
} ZStrConversionCode;
PCL_VIRTUAL_CONTAINER(String):
#include "PCL_VString.hxx"
};
///!===========================================================================!
///!
///! Virtual Exception
///!
///! Global Scope Definitions:
///!
PCL_ENUMERATOR(ExceptionMode)
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
PCL_VIRTUAL_CLASS(Exception):
#include "PCL_VException.hxx"
};
///!===========================================================================!
///!
///! Virtual Navigator (Helper Class for navigation into Virtual Trees)
///!
///! Global Scope Definitions:
///!
PCL_ENUMERATOR(TreeNodeKind)
	ZLeaf = 0x1,
	ZSubTree = ZLeaf << 1,
	ZBranch = ZSubTree,
	ZAnyNode = ZLeaf | ZSubTree,
} ZTreeNodeKind;
PCL_VIRTUAL_CLASS(Navigator):
#include "PCL_VNavigator.hxx"
};
///!===========================================================================!
///!
///! Virtual Tree (may be implemented as File System Tree, Registry or ...)
///!
///! Global Scope Definitions:
///!
///!	Special reference value indicating default (built-in) navigator
static const VNavigator *ZDefaultNavigator = NULL;
PCL_VIRTUAL_CONTAINER_OF(Navigator, Tree):
#include "PCL_VTree.hxx"
};
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
	ZAuto = ZOn | ZOff, // for typical buttons
	ZPulse = ZAuto,
// Modifiers
	ZInvisible		= 0x40000000uL,
	ZDisabled		= ZInvisible >> 1,
} ZControlState;
///!===========================================================================!
#endif // __PCL_VIRTUAL_H__
