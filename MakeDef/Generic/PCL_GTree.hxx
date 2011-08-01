#ifndef __PCL_GENERIC_TREE_H__
#define __PCL_GENERIC_TREE_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

typedef struct PCL_TreeNode {
	LString *pName;
	LVector *pBranch;
	LVector *pLeaf;
	uint NodeKey;
} ZTreeNode, *pZTreeNode;

PCL_GENERIC_CONTAINER(Tree):
	// Inheritable variables and methods
	VNavigator **m_pNav; // Navigator Vector, m_pNav[0] points to default
	uint m_itemCount, m_navCount;
	LCollection m_nodeList;
	pZTreeNode m_pRoot, m_pCurr;

	virtual VNavigator * _CreateNavigator(void);
	virtual void _RemoveNavigator(VNavigator * pNav);
	virtual uint _FindNavigator(const VNavigator& Nav);
#include "PCL_VTree.hxx"
#include "PCL_VNavigator.hxx"
};

#endif // __PCL_GENERIC_TREE_H__