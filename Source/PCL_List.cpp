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

///! Implementation of LList

VIterator * LList::_CreateIterator(ZFilter pFilter) {
	LListIterator *result = new LListIterator(this);
	result->_SetFilter(pFilter);
	return (VIterator *)result;
}

void LList::_RemoveIterator(VIterator * pIter) {
	delete (LListIterator*)pIter;
}

LList::LList(uint ItemSize) {
	if (!ItemSize) LTerminate("Zero ItemSize passed to LList Constructor");
	m_itemSize = ItemSize;
	m_pIter[0] = _CreateIterator(NULL);
	m_iterCount = 1;
}

LList::LList(const pcont pContainer) {
	m_itemSize = ZUintInvalid;
	m_pIter[0] = _CreateIterator(NULL);
	m_iterCount = 1;
	Import(pContainer);
};

LList::~LList() {
	for (uint i = 0; i < m_iterCount; i++) { // Remove all the iterators
		_RemoveIterator(m_pIter[i]);
	}
	m_iterCount = 0;
	RemoveAll();
};

const pcont LList::Export() {
	return GList::Export();
};

void LList::Import(const pcont pContainer, bool AutoRelease) {
	GList::Import(pContainer, AutoRelease);
};

void LList::Insert(ZPosition Pos, pvoid pItem, uint ItemSize) {
	if (ItemSize) {
		XErrorSetLast(E_INVALIDARG, "Non Zero Item Size Specified for Fixed-Item List");
		XErrorSignal("LList::Insert");
		return;
	}
	pZListHeader pHdr = (pZListHeader)LMem.Std->Alloc(sizeof(ZListHeader) + m_itemSize);
	memcpy(pHdr + 1, pItem, m_itemSize);
	AfterInsert(pHdr + 1, m_itemSize);

	pHdr->pNext = pHdr->pPrev = NULL;
	if (!m_count) { // Insert the first Item
		m_head = m_last = pHdr + 1;
	}
	else if (ZHead == Pos) { // Insert the Head Item
		pZListHeader pOldHead = (pZListHeader)m_head - 1;
		pHdr->pNext = pOldHead;
		pOldHead->pPrev = pHdr;
		m_head = pHdr + 1;
		// Correct the iterators:
		for (uint i = 0; i < m_iterCount; i++) {
			// Increase indexes of all the valid iterators:
			if (m_pIter[i]->IsValid()) {
				((GIterator*)m_pIter[i])->_IncIndex();
			}
		}
	}
	else { // Insert the Last Item
		pZListHeader pOldLast = (pZListHeader)m_last - 1;
		pHdr->pPrev = pOldLast;
		pOldLast->pNext = pHdr;
		m_last = pHdr + 1;
	}
	m_count++;
}

bool LList::Remove(ZPosition Pos) { // false if list is empty
	if (!m_count) {
		return false;
	}
	else if (!--m_count) { // Remove the only item: the same as Remove all
		RemoveAll();
		return true;
	}
	pZListHeader pHdr;
	if (ZHead == Pos) { // Remove the Head Item
		pHdr = (pZListHeader)m_head - 1;
		m_head = pHdr->pNext + 1;
		((pZListHeader)m_head - 1)->pPrev = NULL;
		// Correct the iterators:
		for (uint i = 0; i < m_iterCount; i++) {
			// Decrease indexes of all the valid iterators:
			if (m_pIter[i]->IsValid()) {
				((GIterator*)m_pIter[i])->_DecIndex();
			}
		}
	}
	else { // Remove the Last Item
		pHdr = (pZListHeader)m_last - 1;
		m_last = pHdr->pPrev + 1;
		((pZListHeader)m_last - 1)->pNext = NULL;
	}
	// Correct the iterators:
	for (uint i = 0; i < m_iterCount; i++) {
		// Reset all the iterators pointing to removed item
		if ((*m_pIter[i])() == pHdr) m_pIter[i]->Reset();
	}
	BeforeRemove(pHdr + 1, m_itemSize);
	LMem.Std->Dealloc(pHdr);
	return true;
}

void LList::RemoveAll() {
	if (!m_count) return;
	// Reset all the iterators
	for (uint i = 0; i < m_iterCount; i++) {
		m_pIter[i]->Reset();
	}
	// Remove all items
	pZListHeader pHdr = (pZListHeader)m_head - 1;
	while (pHdr) {
		pvoid pNextHdr = pHdr->pNext;
		BeforeRemove(pHdr + 1, m_itemSize);
		LMem.Std->Dealloc(pHdr);
		pHdr = (pZListHeader)pNextHdr;
	}
	// Set members clear
	m_head = m_last = NULL;
	m_count = 0;
}
