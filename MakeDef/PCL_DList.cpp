#define PCL_GENDEFRUN
#define __PCL_H__
#include "PCL_License.h"
#include "PCL_Internal.h"

#define PCL_PURE =0
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
#undef PCL_PURE
#define PCL_PURE /**/
///!===========================================================================!
///!
///! Definition of Generic Iterator & List
///!
#include "PCL_GIterator.hxx"
#include "PCL_GList.hxx"
///!===========================================================================!
///!
///! Definition of Iterators & Lists
///!
#include "PCL_Iterator.hxx"
#include "PCL_List.hxx"
#include "PCL_Vector.hxx"
#include "PCL_Collection.hxx"
