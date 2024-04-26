#include "CTriangle.h"
#include<fstream>
#include"saveaction.h"

CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}
void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawTriangle(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}
bool CTriangle::IsInside(int a, int b)
{


	float A = abs((Corner1.x * (Corner2.y - Corner3.y) + Corner2.x * (Corner3.y - Corner1.y) + Corner3.x * (Corner1.y - Corner2.y)) / 2.0);
	float A1 = abs((a * (Corner2.y - Corner3.y) + Corner2.x * (Corner3.y - b) + Corner3.x * (b - Corner2.y)) / 2.0);
	float A2 = abs((Corner1.x * (b - Corner3.y) + a * (Corner3.y - Corner1.y) + Corner3.x * (Corner1.y - b)) / 2.0);
	float A3 = abs((Corner1.x * (Corner2.y - b) + Corner2.x * (b - Corner1.y) + a * (Corner1.y - Corner2.y)) / 2.0);
	if (FigGfxInfo.DrawClr == UI.BkGrndColor)
	{//check figure deleted
		return false;
	}
	if(A == A1 + A2 + A3)
		return true;
	return false;
}

void CTriangle::printtypeoffigureselected(Output* pout)
{
	pout->PrintMessage("you select a triangle");
}
void CTriangle::movefigure(int a, int b, Output* pout)
{
	float dy, dx;
	dy = (Corner1.y + Corner2.y + Corner3.y) / 3;
	dx = (Corner1.x + Corner2.x + Corner3.x) / 3;
	int xmax, xmin;
	xmax = max(Corner1.x, max(Corner2.x, Corner3.x));
	xmin = min(Corner1.x, min(Corner2.x, Corner3.x));
	Point farthestpoint,nearestpoint,middlepoint;
	if (xmax == Corner1.x)
	{
		farthestpoint = Corner1;
	}
	else
	{
		if (xmin == Corner1.x)
		{
			nearestpoint = Corner1;
		}
		else
		{
			middlepoint = Corner1;
		}
	}
	if (xmax == Corner2.x)
	{
		farthestpoint = Corner2;
	}
	else
	{
		if (xmin == Corner2.x)
		{
			nearestpoint = Corner2;
		}
		else
		{
			middlepoint = Corner2;
		}
	}
	if (xmax == Corner3.x)
	{
		farthestpoint = Corner3;
	}
	else
	{
		if (xmin == Corner3.x)
		{
			nearestpoint = Corner3;
		}
		else
		{
			middlepoint = Corner3;
		}
	}
	//pout->PrintMessage(to_string(nearestpoint.x)); 

	middlepoint.x = abs(a-(dx-middlepoint.x));
	middlepoint.y = abs(b - (dy - middlepoint.y));
	nearestpoint.x = abs(a - (dx - nearestpoint.x));
	nearestpoint.y = abs(b - (dy - nearestpoint.y));
	farthestpoint.x = abs(a + (farthestpoint.x-dx));
	farthestpoint.y = abs(b + (farthestpoint.y - dy));
	Corner1 = middlepoint;
	Corner2 = nearestpoint;
	Corner3 = farthestpoint;
	pout->DrawTriangle(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}

void CTriangle::Save(ofstream& OutFile)
{
	
	OutFile << "TRIANG" << "\t"<<ID<<"\t"<< Corner1.x <<"\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << Corner3.x << "\t" << Corner3.y << "\t"  << "\t" << this->converttostring(UI.DrawColor) << "\t" << this->converttostring(CFigure::GetFillColor());

	
}


void CTriangle::Load(ifstream& Infile)
{

	string s;
	Infile >> ID >>Corner1.x >> Corner1.y
		>> Corner2.x >> Corner2.y
		>> Corner3.x >> Corner3.y;
	
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
Point CTriangle::MakeCenter()
{
	Point P;
	P.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	P.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	return P;
}
int CTriangle::figuretype()
{
	return 5;
}
