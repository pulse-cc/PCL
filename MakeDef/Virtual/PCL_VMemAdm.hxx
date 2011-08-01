///!
///! Public Methods
///!
public:
	virtual pvoid Alloc(uint Size) PCL_PURE;
	virtual pvoid Realloc(pvoid ptr, uint Size) PCL_PURE;
	virtual void Dealloc(pvoid ptr) PCL_PURE;
