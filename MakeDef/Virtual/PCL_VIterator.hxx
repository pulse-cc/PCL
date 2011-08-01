///!
///! Public Methods
///!
public:
	// List Navigation
	virtual void Reset() PCL_PURE; // force to point to nothing
	virtual void SetTo(ZPosition Pos) PCL_PURE;
	virtual bool SetToIndex(int Index) PCL_PURE;
		// true if current position succesfully set
		// false if invalid index, current position remains unchanged
	virtual bool Move(ZDirection Dir) PCL_PURE;
		// false if no more items in direction
	// List Access
	virtual void GetCurrent(pvoid *ppItem) const PCL_PURE;
		// fills *ppItem with NULL if points to nothing
	virtual void Get(ZPosition Pos, pvoid *ppItem) const PCL_PURE;
		// fills *ppItem with NULL if the list is emplty
	virtual void GetByIndex(int Index, pvoid *ppItem) const PCL_PURE;
		// fills *ppItem with NULL if index is out of Count
	// List Information
	virtual uint Count() const PCL_PURE;
		// returns number of items (0 for empty list)
	virtual uint ItemSize() const PCL_PURE; // returns size of the current item
	virtual uint ItemSizeAt(ZPosition Pos) const PCL_PURE;
	virtual uint ItemSizeByIndex(int Index) const PCL_PURE;
	virtual bool IsValid() const PCL_PURE; // true if currently points to data
	virtual bool IsAt(ZPosition Pos) const PCL_PURE;
		// true if currently at specified position
///!
///! Public Operators
///!
public:
	virtual pvoid operator ()() const PCL_PURE;
		// operator form of GetCurrent
	virtual pvoid operator [](ZPosition Pos) const PCL_PURE;
		// operator form of Get
	virtual pvoid operator [](int Index) const PCL_PURE;
		// operator form of GetByIndex
