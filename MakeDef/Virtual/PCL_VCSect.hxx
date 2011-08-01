///!
///! Public Methods
///!
public:
	virtual void Lock(void) PCL_PURE;
	virtual void Unlock(void) PCL_PURE;
	virtual bool TryLock(void) PCL_PURE; // true if locked
