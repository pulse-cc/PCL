#ifndef __PCL_GENERIC_NAVIGATOR_H__
#define __PCL_GENERIC_NAVIGATOR_H__

#ifndef __PCL_H__
#	error Do not include this file directly. Include "PCL.h" instead
#endif

PCL_GENERIC_CLASS(Navigator):
	// Inheritable variables and methods
	VTree *m_tree;
	GNavigator(VTree *Tree);

#include "PCL_VNavigator.hxx"

};

#endif // __PCL_GENERIC_NAVIGATOR_H__