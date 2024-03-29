

#include "OCCTProxy.h"
#include "MakeBottle.h"
#include "MaterialModel.h"
#include "MakeCrossSection.h"
/// <summary>
/// Proxy class encapsulating calls to OCCT C++ classes within 
/// C++/CLI class visible from .Net (CSharp)
/// </summary>
public ref class OCCTProxy
{
public:
	// ============================================
	// Viewer functionality
	// ============================================

	/// <summary>
	///Initialize a viewer
	/// </summary>
	/// <param name="theWnd">System.IntPtr that contains the window handle (HWND) of the control</param>
	bool InitViewer(System::IntPtr theWnd)
	{
		try
		{
			Handle(Aspect_DisplayConnection) aDisplayConnection;
			myGraphicDriver() = new OpenGl_GraphicDriver (aDisplayConnection);


		}
		catch (Standard_Failure)
		{
			return false;
		}

		myViewer() = new V3d_Viewer (myGraphicDriver());
		myViewer()->SetDefaultLights();
		myViewer()->SetLightOn();
		myView() = myViewer()->CreateView();

		//20190529
		myView()->SetComputedMode(Standard_False);


		Handle(WNT_Window) aWNTWindow = new WNT_Window (reinterpret_cast<HWND> (theWnd.ToPointer()));
		myView()->SetWindow(aWNTWindow);
		if (!aWNTWindow->IsMapped())
		{
			aWNTWindow->Map();
		}
		myAISContext() = new AIS_InteractiveContext( myViewer() );
		myAISContext()->UpdateCurrentViewer();
		myView()->Redraw();
		myView()->MustBeResized();
		return true;
	}

	/// <summary>
	/// Make dump of current view to file
	/// </summary>
	/// <param name="theFileName">Name of dump file</param>
	bool Dump(char *theFileName)
	{
		if (myView().IsNull())
		{
			return false;
		}
		myView()->Redraw();
		return myView()->Dump(theFileName) != Standard_False;
	}

	/// <summary>
	///Redraw view
	/// </summary>
	void RedrawView(void)
	{
		if (!myView().IsNull())
		{
			myView()->Redraw();
		}
	}

	/// <summary>
	///Update view
	/// </summary>
	void UpdateView(void)
	{
		if (!myView().IsNull())
		{
			myView()->MustBeResized();
		}
	}

	/// <summary>
	///Set computed mode in false
	/// </summary>
	void SetDegenerateModeOn(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetComputedMode (Standard_False);
		}
	}

	/// <summary>
	///Set computed mode in true
	/// </summary>
	void SetDegenerateModeOff(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetComputedMode (Standard_True);
		}
	}

	/// <summary>
	///Fit all
	/// </summary>
	void WindowFitAll(int theXmin, int theYmin, int theXmax, int theYmax)
	{
		if (!myView().IsNull())
		{
			myView()->WindowFitAll(theXmin, theYmin, theXmax, theYmax);
		}
	}

	/// <summary>
	///Current place of window
	/// </summary>
	/// <param name="theZoomFactor">Current zoom</param>
	void Place(int theX, int theY, float theZoomFactor)
	{	
		Quantity_Factor aZoomFactor = theZoomFactor;
		if (!myView().IsNull())
		{
			myView()->Place(theX, theY, aZoomFactor);
		}
	}

	/// <summary>
	///Set Zoom
	/// </summary>
	void Zoom(int theX1, int theY1, int theX2, int theY2)
	{
		if (!myView().IsNull())
		{
			myView()->Zoom(theX1, theY1, theX2, theY2);
		}
	}

	/// <summary>
	///Set Pan
	/// </summary>
	void Pan(int theX, int theY)
	{
		if (!myView().IsNull())
		{
			myView()->Pan(theX, theY);
		}
	}

	/// <summary>
	///Rotation
	/// </summary>
	void Rotation(int theX, int theY)
	{
		if (!myView().IsNull())
		{
			myView()->Rotation(theX, theY);
		}
	}

	/// <summary>
	///Start rotation
	/// </summary>
	void StartRotation(int theX, int theY)
	{
		if (!myView().IsNull())
		{
			myView()->StartRotation(theX, theY);
		}
	}

	/// <summary>
	///Select by rectangle
	/// </summary>
	void Select(int theX1, int theY1, int theX2, int theY2)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->Select(theX1, theY1, theX2, theY2, myView());
		}
	}

	/// <summary>
	///Select by click
	/// </summary>
	void Select()
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->Select();
		}
	}


	//rSelecttype返回选中obj的类型
	int Select(int rSelectType)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->Select();

			Handle(AIS_InteractiveObject) Ais_InteractiveObj;

			Ais_InteractiveObj = myAISContext()->Current();

			/*if (AIS_KOI_Dimension == Ais_InteractiveObj->Type())
			{
				return (int)AIS_KOI_Dimension;
			}*/

			return 0xFFFFFFFF;
		}

		//0910：自行添加
		return 0;
	}

	/// <summary>
	///Move view
	/// </summary>
	void MoveTo(int theX, int theY)
	{
		if ((!myAISContext().IsNull()) && (!myView().IsNull()))
		{
			myAISContext()->MoveTo(theX, theY, myView());
		}
	}

	/// <summary>
	///Select by rectangle with pressed "Shift" key
	/// </summary>
	void ShiftSelect(int theX1, int theY1, int theX2, int theY2)
	{
		if ((!myAISContext().IsNull()) && (!myView().IsNull()))
		{
			myAISContext()->ShiftSelect(theX1, theY1, theX2, theY2, myView());
		}
	}

	/// <summary>
	///Select by "Shift" key
	/// </summary>
	void ShiftSelect(void)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->ShiftSelect();
		}
	}

	/// <summary>
	///Set background color
	/// </summary>
	void BackgroundColor(int& theRed, int& theGreen, int& theBlue)
	{
		Standard_Real R1;
		Standard_Real G1;
		Standard_Real B1;
		if (!myView().IsNull())
		{
			myView()->BackgroundColor(Quantity_TOC_RGB,R1,G1,B1);
		}
		theRed = (int)R1*255;
		theGreen = (int)G1*255;
		theBlue = (int)B1*255;
	}

	/// <summary>
	///Get background color Red
	/// </summary>
	int GetBGColR(void)
	{
		int aRed, aGreen, aBlue;
		BackgroundColor(aRed, aGreen, aBlue);
		return aRed;
	}

	/// <summary>
	///Get background color Green
	/// </summary>
	int GetBGColG(void)
	{
		int aRed, aGreen, aBlue;
		BackgroundColor(aRed, aGreen, aBlue);
		return aGreen;
	}

	/// <summary>
	///Get background color Blue
	/// </summary>
	int GetBGColB(void)
	{
		int aRed, aGreen, aBlue;
		BackgroundColor(aRed, aGreen, aBlue);
		return aBlue;
	}

	/// <summary>
	///Update current viewer
	/// </summary>
	void UpdateCurrentViewer(void)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	///Front side
	/// </summary>
	void FrontView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Yneg);
		}
	}

	/// <summary>
	///Top side
	/// </summary>
	void TopView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Zpos);
		}
	}

	/// <summary>
	///Left side
	/// </summary>
	void LeftView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Xneg);
		}
	}

	/// <summary>
	///Back side
	/// </summary>
	void BackView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Ypos);
		}
	}

	/// <summary>
	///Right side
	/// </summary>
	void RightView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Xpos);
		}
	}

	/// <summary>
	///Bottom side
	/// </summary>
	void BottomView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Zneg);
		}
	}

	/// <summary>
	///Axo side
	/// </summary>
	void AxoView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_XposYnegZpos);
		}
	}

	/// <summary>
	///Scale
	/// </summary>
	float Scale(void)
	{
		if (myView().IsNull())
		{
			return -1;
		}
		else
		{
			return (float)myView()->Scale();
		}
	}

	/// <summary>
	///Zoom in all view
	/// </summary>
	void ZoomAllView(void)
	{
		if (!myView().IsNull())
		{
			myView()->FitAll();
			myView()->ZFitAll();
		}
	}

	/// <summary>
	///Reset view
	/// </summary>
	void Reset(void)
	{
		if (!myView().IsNull())
		{
			myView()->Reset();
		}
	}

	/// <summary>
	///Set display mode of objects
	/// </summary>
	/// <param name="theMode">Set current mode</param>
	void SetDisplayMode(int theMode)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		AIS_DisplayMode aCurrentMode;
		if (theMode == 0)
		{
			aCurrentMode=AIS_WireFrame;
		}
		else
		{
			aCurrentMode=AIS_Shaded;
		}

		if(myAISContext()->NbCurrents()==0 || myAISContext()->NbSelected()==0)
		{
			myAISContext()->SetDisplayMode(aCurrentMode);
		}
		else 
		{
			for(myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextCurrent())
			{
				myAISContext()->SetDisplayMode(myAISContext()->Current(), theMode, Standard_False);
			}
		}
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	///Set color
	/// </summary>
	void SetColor(int theR, int theG, int theB)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		Quantity_Color aCol =  Quantity_Color(theR/255.,theG/255.,theB/255.,Quantity_TOC_RGB);
		for (;myAISContext()->MoreCurrent ();myAISContext()->NextCurrent ())
		{
			myAISContext()->SetColor (myAISContext()->Current(),aCol.Name());
		}
	}

	/// <summary>
	///Get object color red
	/// </summary>
	int GetObjColR(void)
	{
		int aRed, aGreen, aBlue;
		ObjectColor(aRed, aGreen, aBlue);
		return aRed;
	}

	/// <summary>
	///Get object color green
	/// </summary>
	int GetObjColG(void)
	{
		int aRed, aGreen, aBlue;
		ObjectColor(aRed, aGreen, aBlue);
		return aGreen;
	}

	/// <summary>
	///Get object color R/G/B
	/// </summary>
	void ObjectColor(int& theRed, int& theGreen, int& theBlue)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		theRed=255;
		theGreen=255;
		theBlue=255;
		Handle(AIS_InteractiveObject) aCurrent ;
		Quantity_Color anObjCol;
		myAISContext()->InitCurrent();
		if (!myAISContext()->MoreCurrent())
		{
			return;
		}
		aCurrent = myAISContext()->Current();
		if ( aCurrent->HasColor () ) 
		{
			anObjCol = myAISContext()->Color(myAISContext()->Current());
			Quantity_Parameter r1, r2, r3;
			anObjCol.Values(r1, r2, r3, Quantity_TOC_RGB);
			theRed=(int)r1*255;
			theGreen=(int)r2*255;
			theBlue=(int)r3*255;
		}
	}

	/// <summary>
	///Get object color blue
	/// </summary>
	int GetObjColB(void)
	{
		int aRed, aGreen, aBlue;
		ObjectColor(aRed, aGreen, aBlue);
		return aBlue;
	}

	/// <summary>
	///Set background color R/G/B
	/// </summary>
	void SetBackgroundColor(int theRed, int theGreen, int theBlue)
	{
		if (!myView().IsNull())
		{
			myView()->SetBackgroundColor(Quantity_TOC_RGB, theRed/255.,theGreen/255.,theBlue/255.);
		}
	}

	/// <summary>
	///Erase objects
	/// </summary>
	void EraseObjects(void)
	{
		if (myAISContext().IsNull())
		{
			return;
		}

		myAISContext()->EraseSelected (Standard_True);
		myAISContext()->ClearCurrents();
	}

	/// <summary>
	///Get version
	/// </summary>
	float GetOCCVersion(void)
	{
		return (float)OCC_VERSION;
	}

	/// <summary>
	///set material
	/// </summary>
	void SetMaterial(int theMaterial)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		for ( myAISContext()->InitCurrent(); myAISContext()->MoreCurrent (); myAISContext()->NextCurrent () )
		{
			myAISContext()->SetMaterial( myAISContext()->Current(), (Graphic3d_NameOfMaterial)theMaterial );
		}
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	///set transparency
	/// </summary>
	void SetTransparency(int theTrans)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		for( myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextSelected() )
		{
			myAISContext()->SetTransparency( myAISContext()->Current(), ((Standard_Real)theTrans) / 10.0 );
		}
	}

	/// <summary>
	///Return true if object is selected
	/// </summary>
	bool IsObjectSelected(void)
	{
		if (myAISContext().IsNull())
		{
			return false;
		}
		myAISContext()->InitCurrent();
		return myAISContext()->MoreCurrent() != Standard_False;
	}

	/// <summary>
	///Return display mode
	/// </summary>
	int DisplayMode(void)
	{
		if (myAISContext().IsNull())
		{
			return -1;
		}
		int aMode = -1;
		bool OneOrMoreInShading = false;
		bool OneOrMoreInWireframe = false;
		for (myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextCurrent())
		{
			if ( myAISContext()->IsDisplayed( myAISContext()->Current(), 1 ) )
			{
				OneOrMoreInShading = true;
			}
			if ( myAISContext()->IsDisplayed( myAISContext()->Current(), 0 ) )
			{
				OneOrMoreInWireframe = true;
			}
		}
		if (OneOrMoreInShading && OneOrMoreInWireframe)
		{
			aMode=10;
		}
		else if(OneOrMoreInShading)
		{
			aMode=1;
		}
		else if (OneOrMoreInWireframe)
		{
			aMode=0;
		}

		return aMode;
	}

	/// <summary>
	///Create new view
	/// </summary>
	/// <param name="theWnd">System.IntPtr that contains the window handle (HWND) of the control</param>
	void CreateNewView(System::IntPtr theWnd)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		myView() = myAISContext()->CurrentViewer()->CreateView();
		if (myGraphicDriver().IsNull())
		{
			myGraphicDriver() = new OpenGl_GraphicDriver (Handle(Aspect_DisplayConnection)());
		}
		Handle(WNT_Window) aWNTWindow = new WNT_Window (reinterpret_cast<HWND> (theWnd.ToPointer()));
		myView()->SetWindow(aWNTWindow);
		Standard_Integer w=100, h=100;
		aWNTWindow->Size(w,h);
		if (!aWNTWindow->IsMapped())
		{
			aWNTWindow->Map();
		}
	}

	/// <summary>
	///Set AISContext
	/// </summary>
	bool SetAISContext(OCCTProxy^ theViewer)
	{
		this->myAISContext() = theViewer->GetContext();
		if (myAISContext().IsNull())
		{
			return false;
		}
		return true;
	}

	/// <summary>
	///Get AISContext
	/// </summary>
	Handle(AIS_InteractiveContext) GetContext(void)
	{
		return myAISContext();
	}

public:
	// ============================================
	// Import / export functionality
	// ============================================

	/// <summary>
	///Import BRep file
	/// </summary>
	/// <param name="theFileName">Name of import file</param>
	bool ImportBrep(System::String^ theFileName)
	{
		bool isResult = false;
		int aLength = theFileName->Length;
		char* aFilename = new char[aLength+1];
		for(int i = 0; i<aLength; i++)
		{
			aFilename[i] = (char)theFileName->ToCharArray()[i];
		}
		aFilename[aLength] = '\0';
		isResult = ImportBrep(aFilename);
		return isResult;
	}

	/// <summary>
	///Import BRep file
	/// </summary>
	/// <param name="theFileName">Name of import file</param>
	bool ImportBrep(char* theFileName)
	{
		Standard_CString aFileName = (Standard_CString) theFileName;
		TopoDS_Shape aShape;
		BRep_Builder aBuilder;
		Standard_Boolean isResult = BRepTools::Read(aShape,aFileName,aBuilder);
		if (!isResult)
		{
			return false;
		}
		if(myAISContext()->HasOpenedContext())
		{
			myAISContext()->CloseLocalContext();
		}
		myAISContext()->Display(new AIS_Shape(aShape));
		return true;
	}

	/// <summary>
	///Import Step file
	/// </summary>
	/// <param name="theFileName">Name of import file</param>
	bool ImportStep(char* theFileName)
	{
		Standard_CString aFileName = (Standard_CString) theFileName;
		STEPControl_Reader aReader;
		IFSelect_ReturnStatus aStatus = aReader.ReadFile(aFileName);
		if ( aStatus == IFSelect_RetDone )
		{
			bool isFailsonly = false;
			aReader.PrintCheckLoad( isFailsonly, IFSelect_ItemsByEntity );

			int aNbRoot = aReader.NbRootsForTransfer();
			aReader.PrintCheckTransfer( isFailsonly, IFSelect_ItemsByEntity );
			for ( Standard_Integer n = 1; n <= aNbRoot; n++ )
			{
				Standard_Boolean ok = aReader.TransferRoot( n );
				int aNbShap = aReader.NbShapes();
				if ( aNbShap > 0 )
				{
					for ( int i = 1; i <= aNbShap; i++ )
					{
						TopoDS_Shape aShape = aReader.Shape( i );
						myAISContext()->Display(new AIS_Shape(aShape));
					}
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	/// <summary>
	///Import Iges file
	/// </summary>
	/// <param name="theFileName">Name of import file</param>
	bool ImportIges(char* theFileName)
	{
		Standard_CString aFileName = (Standard_CString) theFileName;
		IGESControl_Reader aReader;
		int aStatus = aReader.ReadFile( aFileName );

		if ( aStatus == IFSelect_RetDone )
		{
			aReader.TransferRoots();
			TopoDS_Shape aShape = aReader.OneShape();
			myAISContext()->Display(new AIS_Shape(aShape));
		}
		else
		{
			return false;
		}

		myAISContext()->UpdateCurrentViewer();
		return true;
	}

	/// <summary>
	///Export BRep file
	/// </summary>
	/// <param name="theFileName">Name of export file</param>
	bool ExportBRep(char* theFileName)
	{
		myAISContext()->InitCurrent();
		if (!myAISContext()->MoreCurrent())
		{
			return false;
		}

		Handle(AIS_InteractiveObject) anIO = myAISContext()->Current();
		Handle(AIS_Shape) anIS = Handle(AIS_Shape)::DownCast(anIO);
		return BRepTools::Write (anIS->Shape(), (Standard_CString)theFileName) != Standard_False;
	}

	/// <summary>
	///Export Step file
	/// </summary>
	/// <param name="theFileName">Name of export file</param>
	bool ExportStep(char* theFileName)
	{
		STEPControl_StepModelType aType = STEPControl_AsIs;
		IFSelect_ReturnStatus aStatus;
		STEPControl_Writer aWriter;
		for ( myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextCurrent() )
		{
			Handle(AIS_InteractiveObject) anIO = myAISContext()->Current();
			Handle(AIS_Shape) anIS=Handle(AIS_Shape)::DownCast(anIO);
			TopoDS_Shape aShape = anIS->Shape();
			aStatus = aWriter.Transfer( aShape , aType );
			if ( aStatus != IFSelect_RetDone )
			{
				return false;
			}
		}

		aStatus = aWriter.Write( (Standard_CString)theFileName );
		if ( aStatus != IFSelect_RetDone )
		{
			return false;
		}

		return true;
	}

	/// <summary>
	///Export Iges file
	/// </summary>
	/// <param name="theFileName">Name of export file</param>
	bool ExportIges(char* theFileName)
	{
		IGESControl_Controller::Init();
		IGESControl_Writer aWriter( Interface_Static::CVal( "XSTEP.iges.unit" ),
			Interface_Static::IVal( "XSTEP.iges.writebrep.mode" ) );

		for ( myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextCurrent() )
		{
			Handle(AIS_InteractiveObject) anIO = myAISContext()->Current();
			Handle(AIS_Shape) anIS=Handle(AIS_Shape)::DownCast(anIO);
			TopoDS_Shape aShape = anIS->Shape();
			aWriter.AddShape ( aShape );
		}

		aWriter.ComputeModel();
		return aWriter.Write( (Standard_CString)theFileName) != Standard_False;
	}

	/// <summary>
	///Export Vrml file
	/// </summary>
	/// <param name="theFileName">Name of export file</param>
	bool ExportVrml(char* theFileName)
	{
		TopoDS_Compound aRes;
		BRep_Builder aBuilder;
		aBuilder.MakeCompound( aRes );

		for ( myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextCurrent() )
		{
			Handle(AIS_InteractiveObject) anIO = myAISContext()->Current();
			Handle(AIS_Shape) anIS=Handle(AIS_Shape)::DownCast(anIO);
			TopoDS_Shape aShape = anIS->Shape();
			if ( aShape.IsNull() )
			{
				return false;
			}

			aBuilder.Add( aRes, aShape );
		}

		VrmlAPI_Writer aWriter;
		aWriter.Write( aRes, (Standard_CString)theFileName );

		return true;
	}

	/// <summary>
	///Export Stl file
	/// </summary>
	/// <param name="theFileName">Name of export file</param>
	bool ExportStl(char* theFileName)
	{
		TopoDS_Compound aComp;
		BRep_Builder aBuilder;
		aBuilder.MakeCompound( aComp );

		for ( myAISContext()->InitCurrent(); myAISContext()->MoreCurrent(); myAISContext()->NextCurrent() )
		{
			Handle(AIS_InteractiveObject) anIO = myAISContext()->Current();
			Handle(AIS_Shape) anIS=Handle(AIS_Shape)::DownCast(anIO);
			TopoDS_Shape aShape = anIS->Shape();
			if ( aShape.IsNull() ) 
			{
				return false;
			}
			aBuilder.Add( aComp, aShape );
		}

		StlAPI_Writer aWriter;
		aWriter.Write( aComp, (Standard_CString)theFileName );
		return true;
	}

	/// <summary>
	///Define which Import/Export function must be called
	/// </summary>
	/// <param name="theFileName">Name of Import/Export file</param>
	/// <param name="theFormat">Determines format of Import/Export file</param>
	/// <param name="theIsImport">Determines is Import or not</param>
	bool TranslateModel(System::String^ theFileName, int theFormat, bool theIsImport)
	{
		bool isResult;
		int aLength = theFileName->Length;
		char* aFilename = new char[aLength+1];
		for(int i = 0; i<aLength; i++)
		{
			aFilename[i] = (char)theFileName->ToCharArray()[i];
		}
		aFilename[aLength] = '\0';

		if (theIsImport)
		{
			switch(theFormat)
			{
			case 0:
				isResult = ImportBrep(aFilename);
				break;
			case 1:
				isResult = ImportStep(aFilename);
				break;
			case 2:
				isResult = ImportIges(aFilename);
				break;
			default:
				isResult = false;
			}
		}
		else 
		{
			switch(theFormat)
			{
			case 0:
				isResult = ExportBRep(aFilename);
				break;
			case 1:
				isResult = ExportStep(aFilename);
				break;
			case 2:
				isResult = ExportIges(aFilename);
				break;
			case 3:
				isResult = ExportVrml(aFilename);
				break;
			case 4:
				isResult = ExportStl(aFilename);
				break;
			case 5:
				isResult = Dump(aFilename);
				break;
			default:
				isResult = false;
			}
		}
		return isResult;
	}

	/// <summary>
	///Initialize OCCTProxy
	/// </summary>
	void InitOCCTProxy(void)
	{
		myGraphicDriver()=NULL;
		myViewer()=NULL;
		myView()=NULL;
		myAISContext()=NULL;
	}

	void ShowBottle(const Standard_Real width, const Standard_Real height, const Standard_Real thickness )
	{
		TopoDS_Shape myShape;

		myShape = MakeBottle(width, height, thickness);

		Handle(AIS_Shape) aisShape = new AIS_Shape(myShape);

		myAISContext()->SetColor(aisShape,Quantity_NOC_BROWN, Standard_False);
		myAISContext()->SetMaterial(aisShape,Graphic3d_NOM_GOLD, Standard_False );

		myAISContext()->Display(aisShape);
	}

	//void showMaterial(clsMaterialModel curMaterial) 
	//{

	//}

	void showRect(Standard_Real length, Standard_Real width,  Standard_Real height, Standard_Real thickness, Standard_Real FilletRadius)
	{
		TopoDS_Shape myShape;

		myShape = MakeRectPrism(length, width, height, thickness,FilletRadius);

		Handle(AIS_Shape) aisShape = new AIS_Shape(myShape);

		myAISContext()->SetColor(aisShape,Quantity_NOC_BROWN, Standard_False);
		myAISContext()->SetMaterial(aisShape,Graphic3d_NOM_GOLD, Standard_False );

		myAISContext()->Display(aisShape);


		gp_Pnt FirstPoint(0,0,0);
		gp_Pnt SecondPoint(length, width,0);
		gp_Pnt FirstPointY(FirstPoint.X(), SecondPoint.Y(), 0);
		gp_Pnt SecondPointX(SecondPoint.X(),FirstPoint.Y(),0);
		gp_Pnt ForthPoint(SecondPoint.X()+30, FirstPoint.Y(),0);
		TopoDS_Edge Edge1 = BRepBuilderAPI_MakeEdge(FirstPoint, FirstPointY);
		TopoDS_Edge Edge2 = BRepBuilderAPI_MakeEdge(FirstPointY, SecondPoint);

		//0604显示尺寸
		TopoDS_Edge anEdge = Edge1;

		TopoDS_Vertex aFirstVertex, aSecondVertex;
		TopExp::Vertices(TopoDS::Edge(anEdge), aFirstVertex, aSecondVertex);

		gp_Pnt aP1 = BRep_Tool::Pnt(aFirstVertex);
		gp_Pnt aP2 = BRep_Tool::Pnt(aSecondVertex);
		gp_Pnt aP3(aP2.X()-10, aP2.Y()-10, aP2.Z());

		GC_MakePlane aMakePlane(aP1,aP2,aP3);
		Handle(Geom_Plane) aPlane = aMakePlane.Value();

		Handle(AIS_LengthDimension) aLenDim = 
			new AIS_LengthDimension(TopoDS::Edge(anEdge), aPlane->Pln());
		Handle(Prs3d_DimensionAspect) anAspect = new Prs3d_DimensionAspect();

		anAspect->MakeArrows3d(Standard_False);

		anAspect->MakeText3d(Standard_True);
		anAspect->TextAspect()->SetHeight(15);
		anAspect->MakeTextShaded(Standard_True);
		anAspect->SetCommonColor(Quantity_NOC_GREEN);
		anAspect->MakeUnitsDisplayed(Standard_False);
		//TCollection_AsciiString strUnit("mm");
		//aLenDim->SetDisplayUnits(strUnit);
		aLenDim->SetDimensionAspect(anAspect);
		aLenDim->SetFlyout(20);
		myAISContext()->Display(aLenDim);

		anEdge = Edge2;
		Handle(AIS_LengthDimension) aLenDim2 = new AIS_LengthDimension(TopoDS::Edge(anEdge), aPlane->Pln());
		aLenDim2->SetDimensionAspect(anAspect);
		aLenDim2->SetFlyout(20);
		myAISContext()->Display(aLenDim2);


	}


private:
	// fields
	NCollection_Haft<Handle(V3d_Viewer)> myViewer;
	NCollection_Haft<Handle(V3d_View)> myView;
	NCollection_Haft<Handle(AIS_InteractiveContext)> myAISContext;
	NCollection_Haft<Handle(OpenGl_GraphicDriver)> myGraphicDriver;
};
