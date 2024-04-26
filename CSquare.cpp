#include "CSquare.h"
#include<fstream>
#include"saveaction.h"
CSquare::CSquare():CFigure()
{
}
CSquare::CSquare(Point p1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	center = p1;
}
void CSquare::Draw(Output* pOut) const
{
	//Call Output::DrawSquare to draw a square on the screen	
	pOut->DrawSquare(center, FigGfxInfo, Selected);
}
bool CSquare::IsInside(int a, int b)
{
	Point p1, p2;
	p1.x = center.x - 90;
	p1.y = center.y - 90;
	p2.x = center.x + 90;
	p2.y = center.y + 90;
	if (FigGfxInfo.DrawClr == UI.BkGrndColor)
	{//check figure deleted
		return false;
	}
	if ((a >= p1.x && a <= p2.x) && (b >= p1.y && b <= p2.y))
	{
		return true;
	}
	return false;
}
void CSquare::printtypeoffigureselected(Output* pout)
{
	pout->PrintMessage("you select a square");
}
void CSquare::movefigure(int a, int b, Output* pout)
{
	center.x = a;
	center.y = b;
	pout->DrawSquare(center, FigGfxInfo, Selected);

}

void CSquare::Save(ofstream& OutFile)
{
	
	
	OutFile << "SQUAR" <<"\t" << ID << "\t" << center.x << "\t" << center.y  << "\t" << this->converttostring(UI.DrawColor) << "\t" << this->converttostring(CFigure::GetFillColor());

	
}




void CSquare::Load(ifstream& Infile)
{
	string s;
	Infile >> ID >> center.x >> center.y;

	Infile >> s;
	FigGfxInfo.DrawClr = CFigure::converttoColor(s);

	Infile >> s;
	if (s == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = CFigure::converttoColor(s);
	}


	Selected = false;
}
Point CSquare::MakeCenter()
{
	Point P;
	P.x = center.x;
	P.y = center.y;
	return P;
}
int CSquare::figuretype()
{
	return 4;
}
