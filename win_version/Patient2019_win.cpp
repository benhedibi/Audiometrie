//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Unit5.cpp", OpInfoFrm);
USEFORM("Unit4.cpp", OpListFrm);
USEFORM("Unit3.cpp", MedInfoFrm);
USEFORM("Unit2.cpp", MedListFrm);
USEFORM("Unit17.cpp", DemoStatFrm);
USEFORM("Unit6.cpp", SplshFrm);
USEFORM("Unit9.cpp", TympImpFrm);
USEFORM("Unit8.cpp", TympPrevFrm);
USEFORM("Unit7.cpp", InfosFrm);
USEFORM("Unit16.cpp", LoginFrm);
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit10.cpp", GainpPrevFrm);
USEFORM("Unit15.cpp", AudiogImpFrm);
USEFORM("Unit14.cpp", AudiogPrevFrm);
USEFORM("Unit13.cpp", AvocImpFrm);
USEFORM("Unit12.cpp", AvocPrevFrm);
USEFORM("Unit11.cpp", GainpImpFrm);
USEFORM("Unit18.cpp", GeoFrm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
