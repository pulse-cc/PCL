#define PCL_GENDEFRUN
#define __PCL_H__
#include "PCL_License.h"
#include "PCL_Internal.h"

#define PCL_PURE =0
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
///! Virtual Tree
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
///! Virtual Browser (Helper Class for browsing Virtual NameSpaces)
///!
PCL_VIRTUAL_CLASS(Browser):
#include "PCL_VBrowser.hxx"
};
///!===========================================================================!
///!
///! Virtual NameSpace (may be implemented as File System Tree, Registry or ...)
///!
///! Global Scope Definitions:
///!
///!	Special reference value indicating default (built-in) browser
static const VNavigator *ZDefaultBrowser = NULL;
PCL_VIRTUAL_CONTAINER_OF(Browser, NameSpace):
#include "PCL_VNameSpace.hxx"
};
#undef PCL_PURE
#define PCL_PURE /**/
///!===========================================================================!
///!
///! Definition of Generic Navigator & NameTree
///!
//#include "PCL_GNavigator.hxx"
//#include "PCL_GTree.hxx"
///!===========================================================================!
///!
///! Definition of Navigators & NameTrees
///!
//#include "PCL_Navigator.hxx"
//#include "PCL_Registry.hxx"
