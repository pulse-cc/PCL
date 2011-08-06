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

typedef struct PCL_ListContainerHeader : PCL_Container {
	uint itemSize;
	uint itemCount;
} ZListContainerHeader, *pZListContainerHeader;

///! Overridables

void GList::BeforeRemove(pvoid, uint) {return;};
void GList::AfterInsert(pvoid, uint) {return;};

///! Implementation of GList

VIterator * GList::_CreateIterator(ZFilter pFilter) {
	LTerminate("GList::_CreateIterator() called");
	return NULL;
}

void GList::_RemoveIterator(VIterator * pIter) {
	LTerminate("GList::_RemoveIterator() called");
}

GList::GList() {
	m_count = 0;
	m_head = m_last = NULL;
	m_pIter = (VIterator **)LMem.Std->Alloc(sizeof(pvoid));
	m_iterCount = 0;
}

GList::GList(const pcont pContainer) {
	LTerminate("constructor GList(const pcont pContainer) called");
};

GList::~GList() {
	LMem.Std->Dealloc(m_pIter);
};

const pcont GList::Export() {
	uint contSize = sizeof(ZListContainerHeader) + m_itemSize * m_count;
	pZListContainerHeader pHdr = (pZListContainerHeader)LMem.Std->Alloc(contSize);
	pHdr->classCode = ClassCode();
	pHdr->dataSize = contSize;
	pHdr->itemCount = m_count;
	pHdr->itemSize = m_itemSize;
	puchar pContItem = (puchar)(pHdr + 1);
	for (Reset(); Move(ZNext); pContItem += m_itemSize) {
		memcpy(pContItem, (*this)(), m_itemSize);
	}
	return (pcont)pHdr;
};

void GList::Import(const pcont pContainer, bool AutoRelease) {
	if (m_count) RemoveAll();
	pZListContainerHeader pHdr = (pZListContainerHeader)pContainer;
	if (!pHdr) return; // Empty container provides empty list
	if (ClassCode() != pHdr->classCode) {
		XErrorSetLast(E_INVALIDARG, "Wrong Container: not a list");
		XErrorSignal("GList::Import");
		return;
	}
	m_itemSize = pHdr->itemSize;
	puchar pContItem = (puchar)(pHdr + 1);
	for (uint i = 0; i < pHdr->itemCount; i++) {
		Insert(ZLast, pContItem);
		pContItem += m_itemSize;
	}
	if (AutoRelease) {
		pHdr->classCode = 0; // Mark as released (to be on the safe side)
		LMem.Std->Dealloc(pContainer);
	}
}

VIterator& GList::NewIterator(ZFilter pFilter) {
	VIterator * result = NULL;
	m_iterCount++;
	m_pIter = (VIterator **)LMem.Std->Realloc(m_pIter, m_iterCount * sizeof(pvoid));
	m_pIter[m_iterCount - 1] = _CreateIterator(pFilter);
	result = m_pIter[m_iterCount - 1];
	return *result;
}

uint GList::_FindIterator(const VIterator& Iter) {
	for (uint i = 1; i < m_iterCount; i++) { // Skip default iterator from search
		if (m_pIter[i] == &Iter) return i;
	}
	return ZUintInvalid;
}

void GList::DeleteIterator(const VIterator& Iter) {
	if (1 == m_iterCount) {
		XErrorSetLast(E_INVALIDARG, "No iterator(s) created");
		XErrorSignal("GList::DeleteIterator");
		return;
	}
	uint iIdx = _FindIterator(Iter);
	if (ZUintInvalid == iIdx) {
		XErrorSetLast(E_INVALIDARG, "Unknown iterator");
		XErrorSignal("GList::DeleteIterator");
		return;
	}
	// Call destructor
	_RemoveIterator(m_pIter[iIdx]);
	// Save the last iterator in vector (if necessary)
	if (iIdx < m_iterCount - 1) m_pIter[iIdx] = m_pIter[m_iterCount - 1];
	// Realloc vector
	m_iterCount--;
	m_pIter = (VIterator **)LMem.Std->Realloc(m_pIter, m_iterCount * sizeof(pvoid));
}

void GList::Insert(ZPosition Pos, pvoid pItem, uint ItemSize) {
	LTerminate("GList::Insert() called");
}

bool GList::Remove(ZPosition Pos) {
	LTerminate("GList::Remove() called");
	return false;
}

void GList::RemoveAll() {
	LTerminate("GList::RemoveAll() called");
}

void GList::_InternalSwap(pvoid pItem1, pvoid pItem2) {
	pvoid pBuf = LMem.Std->Alloc(m_itemSize);
	memcpy(pBuf, pItem1, m_itemSize);
	memcpy(pItem1, pItem2, m_itemSize);
	memcpy(pItem2, pBuf, m_itemSize);
	LMem.Std->Dealloc(pBuf);
}

void GList::SwapWith(ZPosition Pos, const VIterator& Iter) {
	if (!m_count) {
		XErrorSetLast(E_FAIL, "Swap on empty list", PCL_ELEV_(RECOVER));
		XErrorSignal("GList::SwapWith");
		return;
	}
	pvoid pItem1 = (ZHead == Pos) ? m_head : m_last;
	pvoid pItem2;
	uint iIdx = (&Iter) ? _FindIterator(Iter) : 0;
	if (ZUintInvalid == iIdx) {
		XErrorSetLast(E_INVALIDARG, "Unknown iterator");
		XErrorSignal("GList::SwapWith");
		return;
	}
	else if (!(pItem2 = (*m_pIter[iIdx])())) {
		XErrorSetLast(E_FAIL, "Current undefined on the iterator");
		XErrorSignal("GList::SwapWith");
		return;
	}
	_InternalSwap(pItem1, pItem2);
}

void GList::Swap(const VIterator& Iter1, const VIterator& Iter2) {
	if (!m_count) {
		XErrorSetLast(E_FAIL, "Swap on empty list", PCL_ELEV_(RECOVER));
		XErrorSignal("GList::Swap");
		return;
	}

	uint iIdx1 = _FindIterator(Iter1);
	pvoid pItem1;
	if (ZUintInvalid == iIdx1) {
		XErrorSetLast(E_INVALIDARG, "Unknown iterator 1");
		XErrorSignal("GList::Swap");
		return;
	}
	else if (!(pItem1 = (*m_pIter[iIdx1])())) {
		XErrorSetLast(E_FAIL, "Current undefined on the iterator 1");
		XErrorSignal("GList::Swap");
		return;
	}

	uint iIdx2 = (&Iter2) ? _FindIterator(Iter2) : 0;
	pvoid pItem2;
	if (ZUintInvalid == iIdx2) {
		XErrorSetLast(E_INVALIDARG, "Unknown iterator 2");
		XErrorSignal("GList::Swap");
		return;
	}
	else if (!(pItem2 = (*m_pIter[iIdx2])())) {
		XErrorSetLast(E_FAIL, "Current undefined on the iterator 2");
		XErrorSignal("GList::Swap");
		return;
	}
	_InternalSwap(pItem1, pItem2);
}

void GList::SortAsc(ZSortOrder Greater) {
	uint cnt = Count();
	if (cnt < 2) return;
	VIterator &i1 = NewIterator();
	i1.SetTo(ZHead);
	if (cnt == 2) {
		if (Greater(i1(), (*this)[ZTail])) SwapWith(ZTail, i1);
		return;
	}
	VIterator &i2 = NewIterator();
	for (uint j = 0; j < cnt - 1; j++) {
		i1.SetToIndex(j);
		for (uint k = j + 1; k < cnt; k++) {
			i2.SetToIndex(k);
			if (Greater(i1(), i2())) Swap(i1, i2);
		}
	}
}

void GList::Reset() {
	m_pIter[0]->Reset();
}

void GList::SetTo(ZPosition Pos) {
	m_pIter[0]->SetTo(Pos);
}

bool GList::SetToIndex(int Index) {
	return m_pIter[0]->SetToIndex(Index);
}

void GList::Get(ZPosition Pos, pvoid *ppItem) const {
	*ppItem = (ZHead == Pos) ? m_head : m_last;
}

pvoid GList::operator [](ZPosition Pos) const {
	pvoid pItem;
	Get(Pos, &pItem);
	return pItem;
}

void GList::GetCurrent(pvoid *ppItem) const {
	m_pIter[0]->GetCurrent(ppItem);
}

pvoid GList::operator ()() const {
	pvoid pItem;
	m_pIter[0]->GetCurrent(&pItem);
	return pItem;
}

void GList::GetByIndex(int Index, pvoid *ppItem) const {
	m_pIter[0]->GetByIndex(Index, ppItem);
}

pvoid GList::operator [](int Index) const {
	pvoid pItem;
	m_pIter[0]->GetByIndex(Index, &pItem);
	return pItem;
}

bool GList::Move(ZDirection Dir) {
	return m_pIter[0]->Move(Dir);
}

uint GList::ItemSize() const {
	return m_itemSize;
}

uint GList::ItemSizeAt(ZPosition Pos) const {
	return m_itemSize;
}

uint GList::ItemSizeByIndex(int Index) const {
	return m_itemSize;
}

uint GList::Count() const {
	return m_count;
}

bool GList::IsValid() const {
	return m_pIter[0]->IsValid();
}

bool GList::IsAt(ZPosition Pos) const {
	return m_pIter[0]->IsAt(Pos);
}

