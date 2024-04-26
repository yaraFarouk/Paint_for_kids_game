#include "CCircle.h"
#include <fstream>
#include"Actions/Action.h"
#include "ApplicationManager.h"


#include"saveaction.h"

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	Corner2 = P2;
	
}
void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawCircle(Center, Corner2, FigGfxInfo, Selected);
}
bool CCircle::IsInside(int a, int b)
{
	float r, d;
	r = sqrt(pow(Center.x - Corner2.x, 2) + pow(Center.y - Corner2.y, 2));
	d = sqrt(pow(Center.x - a, 2) + pow(Center.y - b, 2));
	if (FigGfxInfo.DrawClr == UI.BkGrndColor)
	{//check if figure deleted or not
		return false;
	}
	if (d <= r)
	{
		return true;
	}
	return false;
}
void CCircle::printtypeoffigureselected(Output* pout)
{
	pout->PrintMessage("you select a circle");
}
void CCircle::movefigure(int a, int b,Output* pout)
{
	float r = sqrt(pow(Center.x - Corner2.x, 2) + pow(Center.y - Corner2.y, 2));
	Center.x = a;
	Center.y = b;
	Corner2.x = a + r;
	Corner2.y = b;
	pout->DrawCircle(Center, Corner2, FigGfxInfo, Selected);
}

void CCircle::Save(ofstream& OutFile)
{
	
	
	OutFile << "CIRC" <<"\t"<< ID << "\t" << Center.x << "\t" << Center.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << this->converttostring(UI.DrawColor) << "\t" << this->converttostring(CFigure::GetFillColor());
	
}



void CCircle::Load(ifstream& Infile)
{
	string s;
	Infile >> ID >> Center.x >> Center.y >> Corner2.x >> Corner2.y;
	
	Infile >> s;
	FigGfxInfo.DrawClr = this->converttoColor(s);

	Infile >> s;
	if (s == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = this->converttoColor(s);
	}

	
	Selected = false;
}
Point CCircle::MakeCenter()
{
	Point P;
	P.x = Center.x;
	P.y = Center.y;
	return P;
}
int CCircle::figuretype()
{
	return 1;
}