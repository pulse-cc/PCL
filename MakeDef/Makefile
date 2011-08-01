VIRTUAL = .\Virtual
GENERIC = .\Generic
LIBRARY = .\Library
COMMON = ..\Include
TOOLS = ..\Bin

PCL_HDR = $(COMMON)\PCL_Library.h
PCL_ROOT = $(COMMON)\PCL_Root.h 
PCL_LIST = $(COMMON)\PCL_List.h 
PCL_TREE = $(COMMON)\PCL_Tree.h
PCL_STR = $(COMMON)\PCL_String.h
PCL_NUM = $(COMMON)\PCL_Numeric.h
PCL_SERV = $(COMMON)\PCL_Service.h

DEPENDS = \
	$(TOOLS)\generate.bat $(TOOLS)\translate.bat $(TOOLS)\writehdr.bat \
	PCL_ClassCode.h PCL_Internal.h \
	$(COMMON)\PCL_License.h $(COMMON)\PCL_Naming.h

TARGET_LIST = $(PCL_ROOT) $(PCL_LIST) $(PCL_TREE) $(PCL_STR) $(PCL_NUM) $(PCL_SERV)

all : $(TARGET_LIST)

ROOT_DEFS = \
	$(VIRTUAL)\PCL_VMemAdm.hxx \
	$(VIRTUAL)\PCL_VContainer.hxx \
	$(VIRTUAL)\PCL_VCSect.hxx \
	$(VIRTUAL)\PCL_VEvent.hxx \
	$(VIRTUAL)\PCL_VMemory.hxx \
	$(GENERIC)\PCL_GMemAdm.hxx
$(PCL_ROOT) : $(ROOT_DEFS) $(DEPENDS) PCL_DRoot.cpp 
	$(TOOLS)\generate PCL_DRoot.cpp PCL_Root.hxx ROOT
	$(TOOLS)\translate $(TOOLS)\fsub PCL_Root.hxx $@
	$(TOOLS)\writehdr $(PCL_HDR)

LIST_DEFS = \
	$(VIRTUAL)\PCL_VIterator.hxx \
	$(VIRTUAL)\PCL_VList.hxx \
	$(GENERIC)\PCL_GIterator.hxx \
	$(GENERIC)\PCL_GList.hxx \
	$(LIBRARY)\PCL_Iterator.hxx \
	$(LIBRARY)\PCL_List.hxx \
	$(LIBRARY)\PCL_Vector.hxx \
	$(LIBRARY)\PCL_Collection.hxx
$(PCL_LIST) : $(LIST_DEFS) $(DEPENDS) PCL_DList.cpp
	$(TOOLS)\generate PCL_DList.cpp PCL_List.hxx LIST
	$(TOOLS)\translate $(TOOLS)\fsub PCL_List.hxx $@
	$(TOOLS)\writehdr $(PCL_HDR)

TREE_DEFS = \
	$(VIRTUAL)\PCL_VNavigator.hxx \
	$(VIRTUAL)\PCL_VTree.hxx \
	$(GENERIC)\PCL_GNavigator.hxx \
	$(GENERIC)\PCL_GTree.hxx \
	$(LIBRARY)\PCL_Navigator.hxx 
#	$(LIBRARY)\PCL_Registry.hxx 
#	$(LIBRARY)\PCL_FileTree.hxx
$(PCL_TREE) : $(TREE_DEFS) $(DEPENDS) PCL_DTree.cpp 
	$(TOOLS)\generate PCL_DTree.cpp PCL_Tree.hxx TREE
	$(TOOLS)\translate $(TOOLS)\fsub PCL_Tree.hxx $@
	$(TOOLS)\writehdr $(PCL_HDR)

STR_DEFS = \
	$(VIRTUAL)\PCL_VString.hxx \
	$(LIBRARY)\PCL_String.hxx
$(PCL_STR) : $(STR_DEFS) $(DEPENDS) PCL_DString.cpp
	$(TOOLS)\generate PCL_DString.cpp PCL_Str.hxx STRING
	$(TOOLS)\translate $(TOOLS)\fsub PCL_Str.hxx $@
	$(TOOLS)\writehdr $(PCL_HDR)

NUM_DEFS = \
	$(VIRTUAL)\PCL_VSet.hxx \
	$(LIBRARY)\PCL_Set.hxx
$(PCL_NUM) : $(NUM_DEFS) $(DEPENDS) PCL_DSet.cpp
	$(TOOLS)\generate PCL_DSet.cpp PCL_Set.hxx SET
	$(TOOLS)\translate $(TOOLS)\fsub PCL_Set.hxx $@
	$(TOOLS)\writehdr $(PCL_HDR)

SERV_DEFS = \
	$(VIRTUAL)\PCL_VException.hxx \
	$(LIBRARY)\PCL_Exception.hxx \
	$(LIBRARY)\PCL_Service.hxx
$(PCL_SERV) : $(SERV_DEFS) $(DEPENDS) PCL_DServ.cpp
	$(TOOLS)\generate PCL_DServ.cpp PCL_Serv.hxx SERVICE
	$(TOOLS)\translate $(TOOLS)\fsub PCL_Serv.hxx $@
	$(TOOLS)\writehdr $(PCL_HDR)

