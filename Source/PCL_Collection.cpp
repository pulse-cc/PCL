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

///! Implementation of _WCollectionHeader

_WCollectionHeader::_WCollectionHeader() : LVector(sizeof(ZCollectionHeader)) {
	m_pItem = NULL;
	m_itemSize = 0;
	m_pDbg = new LException(ZIgnore);
}

_WCollectionHeader::~_WCollectionHeader() {
	delete m_pDbg;
}

void _WCollectionHeader::AfterInsert(pvoid _pHdr, uint HdrSize) {
	m_pDbg->Signal("_WCollectionHeader::AfterInsert");
	pZCollectionHeader pHdr = (pZCollectionHeader)_pHdr;
	if (!m_pItem) {
		m_pDbg->Signal("Empty Item Insert");
		pHdr->pMem = NULL;
		pHdr->itemSize = 0;
	}
	else {
		pHdr->pMem = new LMemory(m_itemSize);
		memcpy(pHdr->pMem->Addr(), m_pItem, m_itemSize);
		pHdr->itemSize = m_itemSize;
		m_pItem = pHdr->pMem->Addr();
	}
	return;
}

void _WCollectionHeader::BeforeRemove(pvoid _pHdr, uint HdrSize) {
	m_pDbg->Signal("_WCollectionHeader::BeforeRemove");
	pZCollectionHeader pHdr = (pZCollectionHeader)_pHdr;
	if (pHdr->pMem) {
		delete pHdr->pMem;
		pHdr->pMem = NULL;
		pHdr->itemSize = 0;
	}
	return;
}

///! Implementation of LCollection

VIterator& LCollection::NewIterator(ZFilter pFilter) {
	return *_CreateIterator(pFilter);
}

void LCollection::DeleteIterator(const VIterator& Iter) {
	_RemoveIterator(const_cast<VIterator*>(&Iter));
}

VIterator * LCollection::_CreateIterator(ZFilter pFilter) {
	VIterator *result = &m_cHdr.NewIterator(pFilter);
	return result;
}

void LCollection::_RemoveIterator(VIterator * pIter) {
	// delete pIter;
}

LCollection::LCollection(void) {
	m_head = m_last = NULL;
	m_itemSize = ZUintInvalid;
	m_pIter[0] = &NewIterator(NULL);
	m_iterCount = 1;
}

LCollection::LCollection(const pcont pContainer) {
	m_head = m_last = NULL;
	m_itemSize = ZUintInvalid;
	m_pIter[0] = &NewIterator(NULL);
	m_iterCount = 1;
	Import(pContainer);
}

LCollection::~LCollection() {
	for (uint i = 0; i < m_iterCount; i++) { // Remove all the iterators
		_RemoveIterator(m_pIter[i]);
	}
	m_iterCount = 0;
	RemoveAll();
}

const pcont LCollection::Export() {
	XErrorSetLast(E_NOTIMPL, "Export is not implemented yet");
	XErrorSignal("LCollection::Export");
	return NULL;
}

void LCollection::Import(const pcont pContainer, bool AutoRelease) {
	XErrorSetLast(E_NOTIMPL, "Import is not implemented yet");
	XErrorSignal("LCollection::Import");
}

void LCollection::Insert(ZPosition Pos, pvoid pItem, uint ItemSize) {
	if (!ItemSize && pItem) {
		XErrorSetLast(E_INVALIDARG, "Zero Item Size Specified for not-NULL Item");
		XErrorSignal("LCollection::Insert");
		return;
	}
	ZCollectionHeader newHdr;
	m_cHdr.m_pItem = pItem;
	m_cHdr.m_itemSize = ItemSize;
	m_cHdr.Insert(Pos, &newHdr);
	AfterInsert(m_cHdr.m_pItem, ItemSize);
	m_cHdr.m_pItem = NULL;
	m_count++;
}

bool LCollection::Remove(ZPosition Pos) { // false if list is empty
	if (!m_count) {
		return false;
	}
	else if (!--m_count) { // Remove the only item: the same as Remove all
		RemoveAll();
		return true;
	}
	pZCollectionHeader pHdr = (pZCollectionHeader)m_cHdr[Pos];
	BeforeRemove(pHdr->pMem->Addr(), pHdr->itemSize);
	m_cHdr.Remove(Pos);
	return true;
}

void LCollection::RemoveAll() {
	if (!m_count) return;
	// Reset all the iterators
	for (uint i = 0; i < m_iterCount; i++) {
		m_pIter[i]->Reset();
	}
	// Remove all items
	m_cHdr.RemoveAll();
	// Set members clear
	m_head = m_last = NULL;
	m_count = 0;
}

void LCollection::SwapWith(ZPosition Pos, const VIterator& Iter) {
	m_cHdr.SwapWith(Pos, Iter);
}

void LCollection::Swap(const VIterator& Iter1, const VIterator& Iter2) {
	m_cHdr.Swap(Iter1, Iter2);
}

void LCollection::SortAsc(ZSortOrder Greater) {
	uint cnt = Count();
	if (cnt < 2) return;
	LCollectionIterator i1(this);
	VIterator &_i1 = NewIterator(NULL);
	i1.SetTo(ZHead);
	_i1.SetTo(ZHead);
	if (cnt == 2) {
		if (Greater(i1(), (*this)[ZTail])) SwapWith(ZTail, _i1);
		return;
	}
	VIterator &_i2 = NewIterator(NULL);
	for (uint j = 0; j < cnt - 1; j++) {
		i1.SetToIndex(j);
		_i1.SetToIndex(j);
		for (uint k = j + 1; k < cnt; k++) {
			SetToIndex(k);
			_i2.SetToIndex(k);
			if (Greater(i1(), (*this)())) Swap(_i1, _i2);
		}
	}
}

void LCollection::GetCurrent(pvoid *ppItem) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])();
	*ppItem = pHdr ? pHdr->pMem->Addr() : NULL;
}

pvoid LCollection::operator ()() const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])();
	return pHdr ? pHdr->pMem->Addr() : NULL;
}

void LCollection::Get(ZPosition Pos, pvoid *ppItem) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])[Pos];
	*ppItem = pHdr ? pHdr->pMem->Addr() : NULL;
}

pvoid LCollection::operator [](ZPosition Pos) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])[Pos];
	return pHdr ? pHdr->pMem->Addr() : NULL;
}

void LCollection::GetByIndex(int Index, pvoid *ppItem) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])[Index];
	*ppItem = pHdr ? pHdr->pMem->Addr() : NULL;
}

pvoid LCollection::operator [](int Index) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])[Index];
	return pHdr ? pHdr->pMem->Addr() : NULL;
}

uint LCollection::ItemSize() const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])();
	return pHdr ? pHdr->itemSize : ZUintInvalid;
}

uint LCollection::Count() const {
	return m_pIter[0]->Count();
}

uint LCollection::ItemSizeByIndex(int Index) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])[Index];
	return pHdr ? pHdr->itemSize : ZUintInvalid;
}

uint LCollection::ItemSizeAt(ZPosition Pos) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)(*m_pIter[0])[Pos];
	return pHdr ? pHdr->itemSize : ZUintInvalid;
}

void LCollection::SetItemSize(uint NewSize, const VIterator& Iter) {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter();
	if (!pHdr) {
		XErrorSetLast(E_INVALIDARG, "Current Item Undefined");
		XErrorSignal("LCollection::SetItemSize");
		return;
	}
	pHdr->itemSize = NewSize;
	if (pHdr->pMem) {
		if (NewSize) {
			pHdr->pMem->SetSize(NewSize);
		}
		else {
			delete pHdr->pMem;
			pHdr->pMem = NULL;
		}
	}
	else {
		if (NewSize) {
			pHdr->pMem = new LMemory(NewSize);
		}
	}
	return;
}

