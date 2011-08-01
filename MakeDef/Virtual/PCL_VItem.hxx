///!
///! Public Methods
///!
public:
	virtual uint ClassCode(void) const PCL_PURE;
	virtual void SetClassCode(uint NewClassCode) PCL_PURE;
	virtual uint Size(void) const PCL_PURE;
	virtual void SetSize(uint NewSize) PCL_PURE;
	virtual puchar Addr(void) const PCL_PURE;
	virtual void SetAddr(puchar NewAddr) PCL_PURE;
	virtual uint Info(void) const PCL_PURE;
	virtual void SetInfo(uint NewInfo) PCL_PURE;
///!
///! Public Operators
///!
public:
	virtual operator puchar() const PCL_PURE; // operator form of .Addr()
	virtual operator pvoid() const PCL_PURE; // operator form of .Addr()
