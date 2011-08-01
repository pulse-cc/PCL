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

///! Implementation of LVector

VIterator * LVector::_CreateIterator(ZFilter pFilter) {
	LVectorIterator *result = new LVectorIterator(this);
	result->_SetFilter(pFilter);
	return (VIterator *)result;
}

void LVector::_RemoveIterator(VIterator * pIter) {
	delete (LVectorIterator*)pIter;
}

LVector::LVector(uint ItemSize) {
	if (!ItemSize) LTerminate("Zero ItemSize passed to LVector Constructor");
	m_itemSize = ItemSize;
	m_pIter[0] = _CreateIterator(NULL);
	m_iterCount = 1;
	m_allocCount = 0;
}

LVector::LVector(const pcont pContainer) {
	m_itemSize = ZUintInvalid;
	m_pIter[0] = _CreateIterator(NULL);
	m_iterCount = 1;
	m_allocCount = 0;
	Import(pContainer);
};

LVector::~LVector() {
	for (uint i = 0; i < m_iterCount; i++) { // Remove all the iterators
		_RemoveIterator(m_pIter[i]);
	}
	m_iterCount = 0;
	RemoveAll();
};

const pcont LVector::Export() {
	return GList::Export();
};

void LVector::Import(const pcont pContainer, bool AutoRelease) {
	GList::Import(pContainer, AutoRelease);
};

void LVector::Insert(ZPosition Pos, pvoid pItem, uint ItemSize) {
	if (ItemSize) {
		XErrorSetLast(E_INVALIDARG, "Non Zero Item Size Specified for Vector");
		XErrorSignal("LVector::Insert");
		return;
	}
	uint oldCount = m_count++;
	if (m_count > m_allocCount) {
		m_allocCount += BlockCount();
		m_head = LMem.Std->Realloc(m_head, m_allocCount * m_itemSize);
	}
	m_last = (puchar)m_head + oldCount * m_itemSize;
	pvoid pNewItem;
	if (ZHead == Pos) { // Insert the Head Item
		pNewItem = m_head;
		// Copy the tail
		puchar pTmp = (puchar)m_last;
		for (uint i = 0; i < oldCount; i++) {
			memcpy(pTmp, pTmp - m_itemSize, m_itemSize);
			pTmp -= m_itemSize;
		}
		// Correct the iterators:
		uint i;
		for (i = 0; i < m_iterCount; i++) {
			// Increase indexes of all the valid iterators:
			if (m_pIter[i]->IsValid()) {
				((GIterator*)m_pIter[i])->_IncIndex();
			}
		}
	}
	else { // Insert the Last Item
		pNewItem = m_last;
	}
	memcpy(pNewItem, pItem, m_itemSize);
	AfterInsert(pNewItem, m_itemSize);
	return;
}

bool LVector::Remove(ZPosition Pos) { // false if list is empty
	if (!m_count) {
		return false;
	}
	else if (!--m_count) { // Remove the only item: the same as Remove all
		RemoveAll();
		return true;
	}
	pvoid pRemItem = (*this)[Pos];
	BeforeRemove(pRemItem, m_itemSize);
	if (ZHead == Pos) { // Remove the Head Item
		// Copy the tail
		puchar pTmp = (puchar)m_head;
		for (uint i = 0; i < m_count; i++) {
			memcpy(pTmp, pTmp + m_itemSize, m_itemSize);
			pTmp += m_itemSize;
		}
		// Correct the iterators:
		uint i;
		for (i = 0; i < m_iterCount; i++) {
			// Decrease indexes of all the valid iterators:
			if (m_pIter[i]->IsValid()) {
				((GIterator*)m_pIter[i])->_DecIndex();
			}
		}
	}
	else { // Remove the Last Item
		// No action required
	}
	// Correct the iterators:
	for (uint i = 0; i < m_iterCount; i++) {
		// Reset all the iterators pointing to removed item
		if ((*m_pIter[i])() == pRemItem) m_pIter[i]->Reset();
	}
	// Correct the last pointer
	m_last = (puchar)m_last - m_itemSize;
	// Doesn't Realloc memory until explicit .CollectGarbage() call
	return true;
}

void LVector::RemoveAll() {
	if (!m_count) return;
	// Reset all the iterators
	for (uint i = 0; i < m_iterCount; i++) {
		m_pIter[i]->Reset();
	}
	// Remove all items
	puchar pRemItem = (puchar)m_head;
	uint i;
	for (i = 0; i < m_count; i++) {
		BeforeRemove(pRemItem, m_itemSize);
		pRemItem += m_itemSize;
	}
	// Set members clear
	m_count = m_allocCount = 0;
	LMem.Std->Dealloc(m_head);
	m_head = m_last = 0;
}

void LVector::CollectGarbage() {
	XErrorSetLast(E_NOTIMPL, "Garbage Collection is not implemented yet");
	XErrorSignal("LVector::CollectGarbage");
}





