


#include "MakeCrossSection.h"

// 做空心矩形的拉伸
TopoDS_Shape MakeRectPrism(Standard_Real length, Standard_Real width,  Standard_Real height, Standard_Real thickness, Standard_Real FilletRadius) 
{
	gp_Pnt FirstPoint(0,0,0);
	gp_Pnt SecondPoint(length, width,0);
	gp_Pnt FirstPointY(FirstPoint.X(), SecondPoint.Y(), 0);
	gp_Pnt SecondPointX(SecondPoint.X(),FirstPoint.Y(),0);
	gp_Pnt ForthPoint(SecondPoint.X()+30, FirstPoint.Y(),0);

	gp_Pnt sFirstPoint(thickness,thickness,0);
	gp_Pnt sSecondPoint(length-thickness, width-thickness,0);
	gp_Pnt sFirstPointY(thickness, width-thickness, 0);
	gp_Pnt sSecondPointX(length-thickness, thickness,0);

	TopoDS_Edge Edge1 = BRepBuilderAPI_MakeEdge(FirstPoint, FirstPointY);
	TopoDS_Edge Edge2 = BRepBuilderAPI_MakeEdge(FirstPointY, SecondPoint);
	TopoDS_Edge Edge3 = BRepBuilderAPI_MakeEdge(SecondPoint,SecondPointX);
	TopoDS_Edge Edge4 = BRepBuilderAPI_MakeEdge(SecondPointX,FirstPoint);
	//TopoDS_Edge Edge5 = BRepBuilderAPI_MakeEdge(ForthPoint, FirstPoint);

	TopoDS_Edge sEdge1 = BRepBuilderAPI_MakeEdge(sFirstPoint, sFirstPointY);
	TopoDS_Edge sEdge2 = BRepBuilderAPI_MakeEdge(sFirstPointY, sSecondPoint);
	TopoDS_Edge sEdge3 = BRepBuilderAPI_MakeEdge(sSecondPoint,sSecondPointX);
	TopoDS_Edge sEdge4 = BRepBuilderAPI_MakeEdge(sSecondPointX,sFirstPoint);

	TopoDS_Wire RectWire = BRepBuilderAPI_MakeWire(Edge1,Edge2, Edge3, Edge4);
	TopoDS_Wire sRectWire = BRepBuilderAPI_MakeWire(sEdge1,sEdge2,sEdge3,sEdge4);

	TopoDS_Face RectFace = BRepBuilderAPI_MakeFace(RectWire);
	TopoDS_Face sRectFace = BRepBuilderAPI_MakeFace(sRectWire);



	gp_Vec vecZ(0,0,height);
	TopoDS_Shape RectPrism = BRepPrimAPI_MakePrism(RectFace, vecZ);

	//0605 make hollow

	//RectPrism = MakeMaterialShell(RectPrism,thickness);

	TopoDS_Shape sRectPrism = BRepPrimAPI_MakePrism(sRectFace,vecZ);

	RectPrism = BRepAlgoAPI_Cut(RectPrism,sRectPrism);

	TopExp_Explorer aFaceExplorer(RectPrism, TopAbs_FACE);

	Standard_Real zMax = 0;
	TopoDS_Face CrossSection;
	while(aFaceExplorer.More()) {
		TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
		// Check if <aFace> is the top face of the bottle抯 neck 
		Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
		if(aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)){
			Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
			gp_Pnt aPnt = aPlane->Location();
			Standard_Real aZ   = aPnt.Z();
			if(aZ > zMax){
				zMax = aZ;
				CrossSection = aFace;
			}
		}

		aFaceExplorer.Next();
	}

	TopoDS_Shape CrossSectionPrism = BRepPrimAPI_MakePrism(CrossSection, vecZ);

	return TopoDS_Shape(CrossSection);
}