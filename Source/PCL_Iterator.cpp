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

///! Implementation of GIterator

GIterator::GIterator(VList * List) {
	m_list = List;
	m_index = ZUintInvalid;
	m_pFilter = NULL;
}

GIterator::~GIterator() {
}

void GIterator::Reset() {
	m_index = ZUintInvalid;
}

void GIterator::SetTo(ZPosition Pos) {
	LTerminate("GIterator::SetTo() called");
}

bool GIterator::SetToIndex(int Index) {
	uint count = m_list->Count();
	if (!count) return false;
	if ((Index < 0) || ((uint)Index >= count)) return false;
	m_index = Index;
	return true;
}

void GIterator::GetCurrent(pvoid *ppItem) const {
	LTerminate("GIterator::GetCurrent() called");
}

pvoid GIterator::operator ()() const {
	LTerminate("GIterator::operator ()() const called");
	return NULL;
}

void GIterator::Get(ZPosition Pos, pvoid *ppItem) const {
	*ppItem = (*m_list)[Pos];
}

pvoid GIterator::operator [](ZPosition Pos) const {
	pvoid pItem;
	Get(Pos, &pItem);
	return pItem;
}

void GIterator::GetByIndex(int Index, pvoid *ppItem) const {
	uint count = m_list->Count();
	if (!count) {
		*ppItem = NULL;
		return;
	}
	if ((Index < 0) || ((uint)Index >= count)) {
		*ppItem = NULL;
		return;
	}
	*ppItem = const_cast<GIterator*>(this)->_MoveToIndex((uint)Index);
	return;
}

pvoid GIterator::operator [](int Index) const {
	pvoid pItem;
	GetByIndex(Index, &pItem);
	return pItem;
}

bool GIterator::Move(ZDirection Dir) {
	bool plainMove = _Move(Dir);
	if (!m_pFilter) return plainMove;
	while (plainMove) {
		pvoid pItem;
		GetCurrent(&pItem);
		if ((*m_pFilter)(pItem)) return true;
		plainMove = _Move(Dir);
	}
	return false;
}

bool GIterator::_Move(ZDirection Dir) {
	if (IsValid()) {
		_MoveValid(Dir);
	}
	else {
		SetTo((ZNext == Dir) ? ZHead : ZLast);
	}
	return IsValid();
}

void GIterator::_MoveValid(ZDirection Dir) {
	if (ZNext == Dir) {
		m_index++;
		if (m_index == m_list->Count()) m_index = ZUintInvalid;
	}
	else {
		if (!m_index) {
			m_index = ZUintInvalid;
		}
		else m_index--;
	}
}

uint GIterator::ItemSize() const {
	return m_list->ItemSize();
}

uint GIterator::ItemSizeAt(ZPosition Pos) const {
	return m_list->ItemSizeAt(Pos);
}

uint GIterator::ItemSizeByIndex(int Index) const {
	return m_list->ItemSizeByIndex(Index);
}

uint GIterator::Count() const {
	return m_list->Count();
}

bool GIterator::IsValid() const {
	return (ZUintInvalid != m_index) ? true : false;
}

bool GIterator::IsAt(ZPosition Pos) const {
	if (ZUintInvalid == m_index) return false;
	if (ZHead == Pos) {
		return (!m_index) ? true : false;
	}
	else {
		return (m_index == m_list->Count() - 1) ? true : false;
	}
}

pvoid GIterator::_MoveToIndex(uint Index) {
	LTerminate("GIterator::_MoveToIndex() called");
	return NULL;
}

void GIterator::_IncIndex() {
	m_index++;
}

void GIterator::_DecIndex() {
	m_index--;
}

void GIterator::_SetFilter(ZFilter pFilter) {
	m_pFilter = pFilter;
}

///! Implementation of LListIterator

LListIterator::LListIterator(LList * List) : GIterator(List) {
	m_current = NULL;
}

void LListIterator::Reset() {
	GIterator::Reset();
	m_current = NULL;
}

void LListIterator::SetTo(ZPosition Pos) {
	m_list->Get(Pos, &m_current);
	if (m_current) {
		m_index = (ZHead == Pos) ? 0 : m_list->Count() - 1;
	}
	else {
		m_index = ZUintInvalid;
	}
}

bool LListIterator::SetToIndex(int Index) {
	bool res = GIterator::SetToIndex(Index);
	if (res) m_current = _MoveToIndex((uint)Index);
	return res;
}

void LListIterator::GetCurrent(pvoid *ppItem) const {
	*ppItem = (m_current) ? m_current : NULL;
}

pvoid LListIterator::operator ()() const {
	pvoid pItem;
	GetCurrent(&pItem);
	return pItem;
}

pvoid LListIterator::operator [](ZPosition Pos) const {
	pvoid pItem;
	Get(Pos, &pItem);
	return pItem;
}

pvoid LListIterator::operator [](int Index) const {
	pvoid pItem;
	GIterator::GetByIndex(Index, &pItem);
	return pItem;
}

void LListIterator::_MoveValid(ZDirection Dir) {
	GIterator::_MoveValid(Dir);
	pZListHeader pHdr = (pZListHeader)m_current - 1;
	pHdr = (ZNext == Dir) ? pHdr->pNext : pHdr->pPrev;
	m_current = (pHdr) ? pHdr + 1 : NULL;
}

static pvoid _MoveFromNearest(uint i, pvoid p1, uint i1, pvoid p2, uint i2
) {
	if (i == i1) return p1;
	if (i == i2) return p2;

	uint count;
	pZListHeader pHdr;
	if ((i - i1) <= (i2 - i)) {
		pHdr = (pZListHeader)p1 - 1;
		for (count = i - i1; count; count--) {
			pHdr = pHdr->pNext;
		}
	}
	else {
		pHdr = (pZListHeader)p2 - 1;
		for (count = i2 - i; count; count--) {
			pHdr = pHdr->pPrev;
		}
	}
	return pHdr + 1;
}

pvoid LListIterator::_MoveToIndex(uint Index) {
	uint count = m_list->Count();
	if (ZUintInvalid == m_index) return _MoveFromNearest(
		Index,
		(*m_list)[ZHead], 0,
		(*m_list)[ZLast], count - 1
	);
	if (Index > m_index) return _MoveFromNearest(
		Index,
		m_current, m_index,
		(*m_list)[ZLast], count - 1
	);
	return _MoveFromNearest(
		Index,
		(*m_list)[ZHead], 0,
		m_current, m_index
	);
}

///! Implementation of LVectorIterator

LVectorIterator::LVectorIterator(LVector *Vector) : GIterator(Vector) {
}

void LVectorIterator::SetTo(ZPosition Pos) {
	if (m_list->Count()) {
		m_index = (ZHead == Pos) ? 0 : m_list->Count() - 1;
	}
	else m_index = ZUintInvalid;
}

void LVectorIterator::GetCurrent(pvoid *ppItem) const {
	*ppItem = (ZUintInvalid != m_index)
		? (puchar)((*m_list)[ZHead]) + m_list->ItemSize() * m_index
		: NULL;
}

pvoid LVectorIterator::operator ()() const {
	pvoid pItem;
	GetCurrent(&pItem);
	return pItem;
}

pvoid LVectorIterator::_MoveToIndex(uint Index) {
	return (puchar)((*m_list)[ZHead]) + Index * m_list->ItemSize();
}

///! Implementation of LCollectionIterator

LCollectionIterator::LCollectionIterator(LCollection *Collection)
	: GIterator(Collection), Iter(Collection->NewIterator(NULL)) {
}

LCollectionIterator::~LCollectionIterator(void) {
	// TODO: Delete Iterator
}

void LCollectionIterator::Reset() {
	Iter.Reset();
}

void LCollectionIterator::SetTo(ZPosition Pos) {
	Iter.SetTo(Pos);
}

bool LCollectionIterator::SetToIndex(int Index) {
	return Iter.SetToIndex(Index);
}

void LCollectionIterator::GetCurrent(pvoid *ppItem) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter();
	*ppItem = pHdr ? pHdr->pMem->Addr() : NULL;
}

pvoid LCollectionIterator::operator ()() const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter();
	return pHdr ? pHdr->pMem->Addr() : NULL;
}

void LCollectionIterator::Get(ZPosition Pos, pvoid *ppItem) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter[Pos];
	*ppItem = pHdr ? pHdr->pMem->Addr() : NULL;
}

pvoid LCollectionIterator::operator [](ZPosition Pos) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter[Pos];
	return pHdr ? pHdr->pMem->Addr() : NULL;
}

void LCollectionIterator::GetByIndex(int Index, pvoid *ppItem) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter[Index];
	*ppItem = pHdr ? pHdr->pMem->Addr() : NULL;
}

pvoid LCollectionIterator::operator [](int Index) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter[Index];
	return pHdr ? pHdr->pMem->Addr() : NULL;
}

bool LCollectionIterator::Move(ZDirection Dir) {
	return Iter.Move(Dir);
}

uint LCollectionIterator::ItemSize() const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter();
	return pHdr ? pHdr->itemSize : ZUintInvalid;
}

uint LCollectionIterator::ItemSizeByIndex(int Index) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter[Index];
	return pHdr ? pHdr->itemSize : ZUintInvalid;
}

uint LCollectionIterator::ItemSizeAt(ZPosition Pos) const {
	pZCollectionHeader pHdr = (pZCollectionHeader)Iter[Pos];
	return pHdr ? pHdr->itemSize : ZUintInvalid;
}

uint LCollectionIterator::Count() const {
	return Iter.Count();
}

bool LCollectionIterator::IsValid() const {
	return Iter.IsValid();
}

bool LCollectionIterator::IsAt(ZPosition Pos) const {
	return Iter.IsAt(Pos);
}

