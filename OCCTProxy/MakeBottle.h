

#include "OCCTProxy.h"



extern TopoDS_Shape MakeBottle(const Standard_Real myWidth, 
	const Standard_Real myHeight,const Standard_Real myThickness);

extern TopoDS_Shape MakeMaterialShell(TopoDS_Shape RectPrism,Standard_Real thickness);