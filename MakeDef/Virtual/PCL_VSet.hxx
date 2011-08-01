///!
///! Public Methods
///!
public:
	// General Management
	virtual uint Length() const PCL_PURE; // 0 for empty set
	virtual void SetLength(uint NewLength) PCL_PURE; // 0 to make set empty
	virtual void SetAll(bool NewValue) PCL_PURE;
	virtual void Copy(const VSet &SourceSet) PCL_PURE;
	virtual void SetValue(uint Member, bool NewValue) PCL_PURE;
	virtual bool Value(uint Member) const PCL_PURE;
	// Set Logics
	virtual void Not(void) PCL_PURE;
	virtual void And(const VSet &Set) PCL_PURE;
	virtual void Or(const VSet &Set) PCL_PURE;
	virtual void Xor(const VSet &Set) PCL_PURE;
	virtual bool IsEqual(const VSet &Set) const PCL_PURE;
	virtual bool IsEmpty(void) const PCL_PURE;
///!
///! Public Operators
///!
public:
	virtual bool operator [](uint Member) const PCL_PURE; // .Value() {Same as Pascal's 'in'}
	// Assignments
	virtual const VSet& operator =(bool NewValue) PCL_PURE; // .SetAll(NewValue)
	virtual const VSet& operator &=(const VSet &Set) PCL_PURE; // .And(Set)
	virtual const VSet& operator |=(const VSet &Set) PCL_PURE; // .Or(Set)
	virtual const VSet& operator ^=(const VSet &Set) PCL_PURE; // .Xor(Set)
	virtual const VSet& operator +=(uint Member) PCL_PURE; // .SetValue(Member, true)
	virtual const VSet& operator -=(uint Member) PCL_PURE; // .SetValue(Member, false)
	// Comparisons
	virtual bool operator ==(const VSet &Set) const PCL_PURE; // .IsEqual(Set)
	virtual bool operator !=(const VSet &Set) const PCL_PURE; // !.IsEqual(Set)
///!
///! Protected Methods (Direct access to the set)
///!
	virtual uint _Size(void) const PCL_PURE;
	virtual puchar _Addr(void) const PCL_PURE;
