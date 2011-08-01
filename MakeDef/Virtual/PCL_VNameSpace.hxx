///!
///! Methods to be Overrided in Descendant Classes (doing nothing by default)
///!
protected:
	virtual void AfterInsert(VItem &Item) PCL_PURE;
	virtual void BeforeRemove(VItem &Item) PCL_PURE;
///!
///! Public Methods
///!
public:
	// Browser Management
	virtual VBrowser& NewBrowser(void) PCL_PURE;
	virtual void DeleteBrowser(const VBrowser& Browser) PCL_PURE;
	// Insert / Copy / Update / Remove
	// Insert and Copy return new NodeKey, which never may be 0
	virtual uint Insert(
		ZTreeNodeKind NodeKind, // ZLeaf or ZSubTree
		cstr Name,
		VItem &Item
	) PCL_PURE;
	virtual uint Copy(
		ZTreeNodeKind NodeKind, // ZLeaf - copy only node data; ZSubTree - all
		cstr DestinationName,
		uint SourceNodeKey // use NodeKey == 0 to copy root
	) PCL_PURE;
	// Update, Remove return false if Node Key is invalid
	virtual bool Update(
		uint NodeKey, // use NodeKey == 0 to update root node data
		VItem &Item
	) PCL_PURE;
	virtual bool Remove(uint NodeKey) PCL_PURE;
	// RemoveAll makes tree empty
	virtual void RemoveAll(void) PCL_PURE;
