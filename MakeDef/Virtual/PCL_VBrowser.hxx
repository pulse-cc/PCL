///!
///! Public Methods
///!
public:
	// Generic Name Space info
	// Path returns the current path in human readable form
	virtual cstr Path(void) const PCL_PURE;
	virtual uint Level() const PCL_PURE; // 0 - the root
	// SubTree / Leaf Access (current level only)
	virtual uint FindFirst( // Returns 0 if nothing found
		ZTreeNodeKind NodeKind = ZAnyNode,
		cstr NameFilter = NULL // NULL or empty str - match any
	) PCL_PURE;
	virtual uint FindNext(void) PCL_PURE; // Returns 0 if nothing found
	// Node Information
	virtual bool IsLeaf(uint NodeKey) const PCL_PURE; // false if SubTree
	virtual cstr Name(uint NodeKey) const PCL_PURE;
	// These are abstract Info and Data related to the given node.
	// Use NodeKey == 0 to access root node data
	virtual VItem &Get(uint NodeKey) const PCL_PURE;
	// ForgetNode may (but not must) be called by clients for optimization aids
	virtual void ForgetNode(uint NodeKey) PCL_PURE;
	// Tree Navigation
	// MoveTo returns false if node is Leaf or NodeKey is invalid
	virtual bool MoveTo(uint NodeKey) PCL_PURE;
	virtual bool MoveUp(void) PCL_PURE; // false if at the root
