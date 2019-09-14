
#include "MaterialModel.h"


clsMaterialModel::clsMaterialModel(void)
{

}

clsMaterialModel::clsMaterialModel(TopoDS_Face section,TopoDS_Edge outside,TopoDS_Edge indside,
	string colorname, long color, string num)
{
	MaterialFace = section;
	FrameOutside = outside;
	FrameInside  = indside;
	MaterialColorName = colorname;
	MaterialColor= color ;
	MaterialNum = num;
}

clsMaterialModel::clsMaterialModel(TopoDS_Face section,TopoDS_Edge outside,TopoDS_Edge indside)
{
	MaterialFace = section;
	FrameOutside = outside;
	FrameInside  = indside;

}