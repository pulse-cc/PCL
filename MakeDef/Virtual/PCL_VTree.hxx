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
	// Navigator Management
	virtual VNavigator& NewNavigator(void) PCL_PURE;
	virtual void DeleteNavigator(const VNavigator& Nav) PCL_PURE;
	// Insert / Copy / Update / Remove
	// Insert returns new NodeKey, which never may be 0
	virtual uint Insert(
		ZTreeNodeKind NodeKind, // ZLeaf or ZSubTree
		cstr Name,
		VItem &Item
//		uint Info = 0, // Optional Info Flag associated with the Leaf / SubTree
//		pvoid pData = NULL, // Optional Data associated with the Leaf / SubTree
//		uint DataSize = 0
	) PCL_PURE;
	// Copy, Update, Remove return false if Node Key is invalid
	virtual bool Copy(cstr NewName, uint NodeKey) PCL_PURE;
	virtual bool Update(
		uint NodeKey, // use NodeKey == 0 to update root node data
		VItem &Item
//		uint Info = 0, // Optional Info Flag associated with the Leaf / SubTree
//		pvoid pData = NULL, // Optional Data associated with the Leaf / SubTree
//		uint DataSize = 0
	) PCL_PURE;
	virtual bool Remove(uint NodeKey) PCL_PURE;
	// RemoveAll makes tree empty
	virtual void RemoveAll(void) PCL_PURE;

