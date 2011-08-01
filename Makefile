ROOT = .
I = .
O = .

V = 1.15

MAKEDEF = ./MakeDef/*.* ./MakeDef/Makefile \
	./MakeDef/Library/*.* \
	./MakeDef/Virtual/*.* \
	./MakeDef/Generic/*.*

SOURCE = ./Source/*.*

INCLUDE = ./Include/*.*

STATIC = ./Static/*.* ./Static/Include/*.*

DYNAMIC = ./DLL/*.*

TOOLS = ./Bin/*.*

AW_CONSOLE = ./AppWizards/PCL_Console/*.* \
	./AppWizards/PCL_Console/hlp/*.* \
	./AppWizards/PCL_Console/res/*.* \
	./AppWizards/PCL_Console/Template/*.*

AW_INPROC = ./AppWizards/PCL_Inproc/*.* \
	./AppWizards/PCL_Inproc/hlp/*.* \
	./AppWizards/PCL_Inproc/res/*.* \
	./AppWizards/PCL_Inproc/Template/*.*

AW_SERVICE = ./AppWizards/PCL_Service/*.* \
	./AppWizards/PCL_Service/hlp/*.* \
	./AppWizards/PCL_Service/res/*.* \
	./AppWizards/PCL_Service/Template/*.*

APPWIZ = ./AppWizards/*.* $(AW_CONSOLE) $(AW_INPROC) $(AW_SERVICE)

LIST = $(MAKEDEF) $(SOURCE) $(INCLUDE) $(STATIC) $(DYNAMIC) $(TOOLS) $(APPWIZ)

PCL.V$(V).Win32.zip : $(LIST)
	zip -q $@ ./PCL.dsw ./Install.txt ./tuner.bat $(LIST)
	zip -d $@ *.plg 
	zip -d $@ *.aps 

