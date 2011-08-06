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

typedef struct PCL_TreeContainerHeader : PCL_Container {
	uint treeInfo;
	uint itemCount;
} ZTreeContainerHeader, *pZTreeContainerHeader;

typedef struct PCL_TreeItemHeader {
	uint itemSize;
	uint itemInfo;
} ZTreeItemHeader, *pZTreeItemHeader;

///! Overridables

void GTree::BeforeRemove(VItem &Item) {return;};
void GTree::AfterInsert(VItem &Item) {return;};

///! Implementation of GTree

VNavigator * GTree::_CreateNavigator(void) {
	LTerminate("GTree::_CreateNavigator() called");
	return NULL;
}

void GTree::_RemoveNavigator(VNavigator * pNav) {
	LTerminate("GTree::_RemoveNavigator() called");
}

GTree::GTree() {
	m_itemCount = 0;
	m_pNav = (VNavigator **)LMem.Std->Alloc(sizeof(pvoid));
	m_navCount = 0;
}

GTree::GTree(const pcont pContainer) {
	LTerminate("constructor GTree(const pcont pContainer) called");
};

GTree::~GTree() {
	LMem.Std->Dealloc(m_pNav);
};

const pcont GTree::Export() {
	uint contSize = sizeof(ZTreeContainerHeader);
	puchar pCont = (puchar)LMem.Std->Alloc(contSize);
	pZTreeContainerHeader pHdr = (pZTreeContainerHeader)pCont;
	pHdr->classCode = ClassCode();
	pHdr->itemCount = m_itemCount;
	pHdr->treeInfo = 0; // for future use and fuck XP!
	for (m_nodeList.Reset(); m_nodeList.Move(ZNext);) {
		uint dataSize = m_nodeList.ItemSize();
		uint itemSize = sizeof(ZTreeItemHeader) + dataSize;
		pCont = (puchar)LMem.Std->Realloc(pCont, contSize + itemSize);
		pZTreeItemHeader pContItem = (pZTreeItemHeader)(pCont + contSize);
		contSize += itemSize;
		pContItem->itemSize = itemSize;
		pContItem->itemInfo = 0; // for future use and fuck XP!
		memcpy(pContItem + 1, m_nodeList(), dataSize);
	}
	pHdr = (pZTreeContainerHeader)pCont;
	pHdr->dataSize = contSize;
	return (pcont)pHdr;
};

void GTree::Import(const pcont pContainer, bool AutoRelease) {
	if (m_itemCount) RemoveAll();
	pZTreeContainerHeader pHdr = (pZTreeContainerHeader)pContainer;
	if (!pHdr) return; // Empty container provides empty tree
	if (ClassCode() != pHdr->classCode) {
		XErrorSetLast(E_INVALIDARG, "Wrong Container: not a tree");
		XErrorSignal("GTree::Import");
		return;
	}
	puchar pCont = (puchar)(pHdr + 1);
	for (uint i = 0; i < pHdr->itemCount; i++) {
		pZTreeItemHeader pContItem = (pZTreeItemHeader)pCont;
		uint itemSize = pContItem->itemSize;
		uint dataSize = itemSize - sizeof(ZTreeItemHeader);
		m_nodeList.Insert(ZLast, pContItem + 1, dataSize);
		pCont += itemSize;
	}
	if (AutoRelease) {
		pHdr->classCode = 0; // Mark as released (to be on the safe side)
		LMem.Std->Dealloc(pContainer);
	}
}

VNavigator& GTree::NewNavigator(void) {
	VNavigator * result = NULL;
	m_navCount++;
	m_pNav = (VNavigator **)LMem.Std->Realloc(m_pNav, m_navCount * sizeof(pvoid));
	m_pNav[m_navCount - 1] = _CreateNavigator();
	result = m_pNav[m_navCount - 1];
	return *result;
}

uint GTree::_FindNavigator(const VNavigator& Nav) {
	for (uint i = 1; i < m_navCount; i++) { // Skip default navator from search
		if (m_pNav[i] == &Nav) return i;
	}
	return ZUintInvalid;
}

void GTree::DeleteNavigator(const VNavigator& Nav) {
	if (1 == m_navCount) {
		XErrorSetLast(E_INVALIDARG, "No navator(s) created");
		XErrorSignal("GTree::DeleteNavigator");
		return;
	}
	uint iIdx = _FindNavigator(Nav);
	if (ZUintInvalid == iIdx) {
		XErrorSetLast(E_INVALIDARG, "Unknown navigator");
		XErrorSignal("GTree::DeleteNavigator");
		return;
	}
	// Call destructor
	_RemoveNavigator(m_pNav[iIdx]);
	// Save the last navator in vector (if necessary)
	if (iIdx < m_navCount - 1) m_pNav[iIdx] = m_pNav[m_navCount - 1];
	// Realloc vector
	m_navCount--;
	m_pNav = (VNavigator **)LMem.Std->Realloc(m_pNav, m_navCount * sizeof(pvoid));
}

uint GTree::Insert(ZTreeNodeKind NodeKind, cstr Name, VItem &Item) {
	LTerminate("GTree::Insert() called");
	return ZUintInvalid;
}

bool GTree::Remove(uint NodeKey) {
	LTerminate("GTree::Remove() called");
	return false;
}

void GTree::RemoveAll() {
	LTerminate("GTree::RemoveAll() called");
}

VItem & GTree::Get(uint NodeKey) {
	*ppItem = (ZHead == Pos) ? m_head : m_last;
}

pvoid GTree::operator ()(ZPosition Pos) const {
	pvoid pItem;
	const_cast<GTree*>(this)->Get(Pos, &pItem);
	return pItem;
}

void GTree::GetCurrent(pvoid *ppItem) {
	m_pNav[0]->GetCurrent(ppItem);
}

pvoid GTree::operator ()() const {
	pvoid pItem;
	m_pNav[0]->GetCurrent(&pItem);
	return pItem;
}

void GTree::GetByIndex(pvoid *ppItem, int Index) {
	m_pNav[0]->GetByIndex(ppItem, Index);
}

pvoid GTree::operator [](int Index) const {
	pvoid pItem;
	m_pNav[0]->GetByIndex(&pItem, Index);
	return pItem;
}

bool GTree::Move(ZDirection Dir) {
	return m_pNav[0]->Move(Dir);
}

void GTree::Reset() {
	m_pNav[0]->Reset();
}

uint GTree::GetItemSize() {
	return m_itemSize;
}

uint GTree::GetCount() {
	return m_count;
}

bool GTree::IsValid() {
	return m_pNav[0]->IsValid();
}

bool GTree::IsAt(ZPosition Pos) {
	return m_pNav[0]->IsAt(Pos);
}

