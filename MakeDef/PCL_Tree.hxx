#ifndef __PCL_TREE_H__ 
#define __PCL_TREE_H__ 
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
///!===========================================================================!
///!
///! Virtual Navigator (Helper Class for navigation into Virtual Trees)
///!
///! Global Scope Definitions:
///!
typedef enum PCL_TreeNodeKind { ZNullTreeNodeKind = 0,
	ZLeaf = 0x1,
	ZSubTree = ZLeaf << 1,
	ZBranch = ZSubTree,
	ZAnyNode = ZLeaf | ZSubTree,
} ZTreeNodeKind;
static const uint VNavigatorClassCode = VIRTUALCODE(false); class VNavigator { public:
///!
///! Public Methods
///!
public:
	// Generic Tree info
	// Path returns the current path in human readable form
	virtual cstr Path(void) const =0;
	virtual uint Level() const =0; // 0 - the root
	// SubTree / Leaf Access (current level only)
	virtual uint FindFirst( // Returns 0 if nothing found
		ZTreeNodeKind NodeKind = ZAnyNode,
		cstr NameFilter = NULL // NULL or empty str - match any
	) =0;
	virtual uint FindNext(void) =0; // Returns 0 if nothing found
	// Node Information
	virtual bool IsLeaf(uint NodeKey) const =0; // false if SubTree
	virtual cstr Name(uint NodeKey) const =0;
	// These are abstract Info and Data related to the given node.
	// Use NodeKey == 0 to access root node data
	virtual VItem &Get(uint NodeKey) const =0;
	// ForgetNode may (but not must) be called by clients for optimization aids
	virtual void ForgetNode(uint NodeKey) =0;
	// Tree Navigation
	// MoveTo returns false if node is Leaf or NodeKey is invalid
	virtual bool MoveTo(uint NodeKey) =0;
	virtual bool MoveUp(void) =0; // false if at the root
};
///!===========================================================================!
///!
///! Virtual Tree
///!
///! Global Scope Definitions:
///!
///!	Special reference value indicating default (built-in) navigator
static const VNavigator *ZDefaultNavigator = NULL;
static const uint VTreeClassCode = VIRTUALCODE(true); class VTree : public VContainer, public VNavigator { public:
///!
///! Methods to be Overrided in Descendant Classes (doing nothing by default)
///!
protected:
	virtual void AfterInsert(VItem &Item) =0;
	virtual void BeforeRemove(VItem &Item) =0;
///!
///! Public Methods
///!
public:
	// Navigator Management
	virtual VNavigator& NewNavigator(void) =0;
	virtual void DeleteNavigator(const VNavigator& Nav) =0;
	// Insert / Copy / Update / Remove
	// Insert returns new NodeKey, which never may be 0
	virtual uint Insert(
		ZTreeNodeKind NodeKind, // ZLeaf or ZSubTree
		cstr Name,
		VItem &Item
//		uint Info = 0, // Optional Info Flag associated with the Leaf / SubTree
//		pvoid pData = NULL, // Optional Data associated with the Leaf / SubTree
//		uint DataSize = 0
	) =0;
	// Copy, Update, Remove return false if Node Key is invalid
	virtual bool Copy(cstr NewName, uint NodeKey) =0;
	virtual bool Update(
		uint NodeKey, // use NodeKey == 0 to update root node data
		VItem &Item
//		uint Info = 0, // Optional Info Flag associated with the Leaf / SubTree
//		pvoid pData = NULL, // Optional Data associated with the Leaf / SubTree
//		uint DataSize = 0
	) =0;
	virtual bool Remove(uint NodeKey) =0;
	// RemoveAll makes tree empty
	virtual void RemoveAll(void) =0;
};
///!===========================================================================!
///!
///! Virtual Browser (Helper Class for browsing Virtual NameSpaces)
///!
static const uint VBrowserClassCode = VIRTUALCODE(false); class VBrowser { public:
///!
///! Public Methods
///!
public:
	// Generic Name Space info
	// Path returns the current path in human readable form
	virtual cstr Path(void) const =0;
	virtual uint Level() const =0; // 0 - the root
	// SubTree / Leaf Access (current level only)
	virtual uint FindFirst( // Returns 0 if nothing found
		ZTreeNodeKind NodeKind = ZAnyNode,
		cstr NameFilter = NULL // NULL or empty str - match any
	) =0;
	virtual uint FindNext(void) =0; // Returns 0 if nothing found
	// Node Information
	virtual bool IsLeaf(uint NodeKey) const =0; // false if SubTree
	virtual cstr Name(uint NodeKey) const =0;
	// These are abstract Info and Data related to the given node.
	// Use NodeKey == 0 to access root node data
	virtual VItem &Get(uint NodeKey) const =0;
	// ForgetNode may (but not must) be called by clients for optimization aids
	virtual void ForgetNode(uint NodeKey) =0;
	// Tree Navigation
	// MoveTo returns false if node is Leaf or NodeKey is invalid
	virtual bool MoveTo(uint NodeKey) =0;
	virtual bool MoveUp(void) =0; // false if at the root
};
///!===========================================================================!
///!
///! Virtual NameSpace (may be implemented as File System Tree, Registry or ...)
///!
///! Global Scope Definitions:
///!
///!	Special reference value indicating default (built-in) browser
static const VNavigator *ZDefaultBrowser = NULL;
static const uint VNameSpaceClassCode = VIRTUALCODE(true); class VNameSpace : public VContainer, public VBrowser { public:
///!
///! Methods to be Overrided in Descendant Classes (doing nothing by default)
///!
protected:
	virtual void AfterInsert(VItem &Item) =0;
	virtual void BeforeRemove(VItem &Item) =0;
///!
///! Public Methods
///!
public:
	// Browser Management
	virtual VBrowser& NewBrowser(void) =0;
	virtual void DeleteBrowser(const VBrowser& Browser) =0;
	// Insert / Copy / Update / Remove
	// Insert and Copy return new NodeKey, which never may be 0
	virtual uint Insert(
		ZTreeNodeKind NodeKind, // ZLeaf or ZSubTree
		cstr Name,
		VItem &Item
	) =0;
	virtual uint Copy(
		ZTreeNodeKind NodeKind, // ZLeaf - copy only node data; ZSubTree - all
		cstr DestinationName,
		uint SourceNodeKey // use NodeKey == 0 to copy root
	) =0;
	// Update, Remove return false if Node Key is invalid
	virtual bool Update(
		uint NodeKey, // use NodeKey == 0 to update root node data
		VItem &Item
	) =0;
	virtual bool Remove(uint NodeKey) =0;
	// RemoveAll makes tree empty
	virtual void RemoveAll(void) =0;
};
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
#endif // __PCL_TREE_H__ 
