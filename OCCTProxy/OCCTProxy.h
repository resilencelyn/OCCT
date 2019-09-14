
#ifndef OCCTPROXY_H
#define OCCTPROXY_H



// include required OCCT headers
#include <Standard_Version.hxx>
#include <Message_ProgressIndicator.hxx>
//for OCC graphic
#include <Aspect_DisplayConnection.hxx>
#include <WNT_Window.hxx>
#include <OpenGl_GraphicDriver.hxx>
//for object display
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
//topology
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
//brep tools
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
// iges I/E
#include <IGESControl_Reader.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <Interface_Static.hxx>
//step I/E
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
//for stl export
#include <StlAPI_Writer.hxx>
//for vrml export
#include <VrmlAPI_Writer.hxx>
//wrapper of pure C++ classes to ref classes
#include <NCollection_Haft.h>


#include "Standard_ShortReal.hxx"


#include <Standard.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <AIS_Point.hxx>
#include <AIS_TextLabel.hxx>
#include <AIS_Dimension.hxx>
#include <AIS_DiameterDimension.hxx>
#include <AIS_LengthDimension.hxx>
#include <Aspect_Grid.hxx>
#include <Aspect_Window.hxx>
#include <Aspect_Background.hxx>


#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepAlgo.hxx>
#include <BRepAlgoAPI_Cut.hxx>
//#include <brepalgoapi>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepLib.hxx>
#include <BRepLib_Command.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepOffset.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepTools.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <BndLib_AddSurface.hxx>   
#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>

#include <BRepAlgoAPI_BuilderAlgo.hxx>

#include <Standard_NotImplemented.hxx>


#include <DsgPrs_LengthPresentation.hxx>
#include <FairCurve_Batten.hxx>
#include <FairCurve_MinimalVariation.hxx>

#include <GC_MakeCircle.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeTranslation.hxx>
#include <GC_MakeSegment.hxx>
#include <GC_MakeConicalSurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <GC_MakePlane.hxx>
#include <GC_MakeEllipse.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <GccAna_Circ2d2TanRad.hxx>
#include <GccAna_Lin2d2Tan.hxx>
#include <GccAna_Pnt2dBisec.hxx>
#include <GccEnt.hxx>
#include <GccEnt_QualifiedCirc.hxx>
#include <GccEnt_QualifiedLin.hxx>
#include <gce_MakeCirc2d.hxx>
#include <gce_MakeLin2d.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GCE2d_MakeParabola.hxx>
#include <GCE2d_MakeEllipse.hxx>
#include <GCE2d_MakeArcOfCircle.hxx>
#include <GCE2d_MakeArcOfEllipse.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <GCPnts_QuasiUniformDeflection.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GCPnts_UniformAbscissa.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_Transformation.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_OffsetSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom2dAPI_ExtremaCurveCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <Geom2dAPI_PointsToBSpline.hxx>
#include <Geom2d_OffsetCurve.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Parabola.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Geom2dConvert.hxx>
#include <Geom2dLProp_Curve2dTool.hxx>
#include <Geom2dLProp_CLProps2d.hxx>
#include <GeomAbs_CurveType.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <GeomAPI.hxx>
#include <GeomAPI_ExtremaSurfaceSurface.hxx>
#include <GeomAPI_IntCS.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <GeomConvert.hxx>
#include <GeomConvert_CompBezierSurfacesToBSplineSurface.hxx>
#include <GeomFill_ConstrainedFilling.hxx>
#include <GeomFill_SimpleBound.hxx>
#include <GeomFill_FillingStyle.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <GeomFill_Pipe.hxx>
#include <GeomLib.hxx>
#include <GeomPlate_BuildPlateSurface.hxx>
#include <GeomPlate_PointConstraint.hxx>
#include <GeomPlate_MakeApprox.hxx>
#include <GeomTools.hxx>
#include <GeomTools_Curve2dSet.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <GProp_PEquation.hxx>
#include <gp.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <gp_Lin.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Mat.hxx>
#include <gp_Parab2d.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec2d.hxx>

#include <IntAna_IntConicQuad.hxx>

#include <OSD_Environment.hxx>
#include <OpenGl_GraphicDriver.hxx>

#include <Poly_Triangulation.hxx>
#include <Precision.hxx>
#include <Prs3d_Arrow.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_Root.hxx>
#include <Prs3d_Text.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_IsoAspect.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <Prs3d_IsoAspect.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_PointAspect.hxx>

#include <SelectMgr_EntityOwner.hxx>
#include <SelectMgr_SelectableObject.hxx>
#include <SelectMgr_Selection.hxx>
#include <SelectMgr_SelectionManager.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <ShapeFix_Shape.hxx>
#include <StdSelect_ViewerSelector3d.hxx>
#include <StdPrs_ShadedSurface.hxx>
#include <StdPrs_Point.hxx>
#include <StdPrs_WFSurface.hxx>
#include <StdPrs_WFPoleSurface.hxx>
#include <StdPrs_Curve.hxx>
#include <StdPrs_PoleCurve.hxx>
#include <Standard_ErrorHandler.hxx>

#include <TColStd_MapIteratorOfMapOfTransient.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColgp_Array2OfPnt2d.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <TColgp_SequenceOfPnt2d.hxx>
#include <TColGeom_Array2OfBezierSurface.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS.hxx>
#include <TopoDS_ListIteratorOfListOfShape.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Builder.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>


#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <WNT_Window.hxx>


// list of required OCCT libraries
#pragma comment(lib, "TKernel.lib")
#pragma comment(lib, "TKMath.lib")
#pragma comment(lib, "TKBRep.lib")
#pragma comment(lib, "TKXSBase.lib")
#pragma comment(lib, "TKService.lib")
#pragma comment(lib, "TKV3d.lib")
#pragma comment(lib, "TKOpenGl.lib")
#pragma comment(lib, "TKIGES.lib")
#pragma comment(lib, "TKSTEP.lib")
#pragma comment(lib, "TKStl.lib")
#pragma comment(lib, "TKVrml.lib")


//自己手动添加 20190528
#pragma comment(lib, "TKBin.lib")
#pragma comment(lib, "TKBinL.lib")
#pragma comment(lib, "TKBinTObj.lib")
#pragma comment(lib, "TKBinXCAF.lib")
#pragma comment(lib, "TKBO.lib")
#pragma comment(lib, "TKBool.lib")
#pragma comment(lib, "TKBrep.lib")
#pragma comment(lib, "TKCAF.lib")
#pragma comment(lib, "TKCDF.lib")
#pragma comment(lib, "TKD3DHost.lib")
#pragma comment(lib, "TKDCAF.lib")
#pragma comment(lib, "TKDraw.lib")
#pragma comment(lib, "TKernel.lib")
#pragma comment(lib, "TKFeat.lib")
#pragma comment(lib, "TKFillet.lib")
#pragma comment(lib, "TKG2d.lib")
#pragma comment(lib, "TKG3d.lib")
#pragma comment(lib, "TKGeomAlgo.lib")
#pragma comment(lib, "TKGeomBase.lib")
#pragma comment(lib, "TKHLR.lib")
#pragma comment(lib, "TKIGES.lib")
#pragma comment(lib, "TKIVtk.lib")
#pragma comment(lib, "TKIVtkDraw.lib")
#pragma comment(lib, "TKLCAF.lib")
#pragma comment(lib, "TKMath.lib")
#pragma comment(lib, "TKMesh.lib")
#pragma comment(lib, "TKMeshVS.lib")
#pragma comment(lib, "TKOffset.lib")
#pragma comment(lib, "TKOpenGl.lib")
#pragma comment(lib, "TKPrim.lib")
#pragma comment(lib, "TKQADraw.lib")
#pragma comment(lib, "TKService.lib")
#pragma comment(lib, "TKShHealing.lib")
#pragma comment(lib, "TKStd.lib")
#pragma comment(lib, "TKStdL.lib")
#pragma comment(lib, "TKSTEP.lib")
#pragma comment(lib, "TKSTEP209.lib")
#pragma comment(lib, "TKSTEPAttr.lib")
#pragma comment(lib, "TKSTEPBase.lib")
#pragma comment(lib, "TKSTL.lib")
#pragma comment(lib, "TKTObj.lib")
#pragma comment(lib, "TKTObjDRAW.lib")
#pragma comment(lib, "TKTOpAlgo.lib")
#pragma comment(lib, "TKTopTest.lib")
#pragma comment(lib, "TKV3d.lib")
#pragma comment(lib, "TKVCAF.lib")
#pragma comment(lib, "TKViewerTest.lib")
#pragma comment(lib, "TKVRML.lib")
#pragma comment(lib, "TKXCAF.lib")
#pragma comment(lib, "TKXDEDRAW.lib")
#pragma comment(lib, "TKXDEIGES.lib")
#pragma comment(lib, "TKXDESTEP.lib")
#pragma comment(lib, "TKXMesh.lib")
#pragma comment(lib, "TKXml.lib")
#pragma comment(lib, "TKXmlL.lib")
#pragma comment(lib, "TKXmlTObj.lib")
#pragma comment(lib, "TKXmlXCAF.lib")
#pragma comment(lib, "TKXSBase.lib")
#pragma comment(lib, "TKXSDRAW.lib")



#endif
































