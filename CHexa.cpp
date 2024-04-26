#include "CHexa.h"
#include <fstream>
#include"saveaction.h"
CHexa::CHexa(Point P1, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
}
void CHexa::Draw(Output* pOut) const
{
	//Call Output::DrawHexa to draw a hexa on the screen	
	pOut->DrawHexagon(Center, FigGfxInfo, Selected);
}
bool CHexa::IsInside(int a, int b)
{
	float radius = 100;
	Point p1, p2, p3, p4, p5, p6;
	float const PI = 3.14159265;
	p1.x = Center.x + radius; p1.y = Center.y;
	p2.x = Center.x + (radius / 2); p2.y = Center.y - (sin(PI / 3) * radius);
	p3.x = Center.x - (radius / 2); p3.y = Center.y - (sin(PI / 3) * radius);
	p4.x = Center.x - radius; p4.y = Center.y;
	p5.x = Center.x - (radius / 2); p5.y = Center.y + (sin(PI / 3) * radius);
	p6.x = Center.x + (radius / 2); p6.y = Center.y + (sin(PI / 3) * radius);
	if (a >= p4.x && a <= p1.x && b >= p3.y && b <= p5.y)
	{
		float a1, a2, a3, a4, a5, a6;
		a1 = p4.x; a2 = p3.y; a3 = p3.x; a4 = p3.y; a5 = p4.x; a6 = p4.y;
		float A = abs((a1 * (a4 - a6) +a3 * (a6 - a2) + a5 * (a2 - a4)) / 2.0);
		float A1= abs((a * (a4 - a6) + a3 * (a6 - b) + a5 * (b - a4)) / 2.0);
		float A2= abs((a1 * (b - a6) + a * (a6 - a2) + a5 * (a2 - b)) / 2.0);
		float A3= abs((a1 * (a4 - b) + a3 * (b - a2) + a * (a2 - a4)) / 2.0);
		if (FigGfxInfo.DrawClr == UI.BkGrndColor)
		{//check figure deleted
			return false;
		}
		if (A == A1 + A2 + A3)
		{
			return false;
		}
		else
		{
			a1 = p1.x; a2 = p2.y; a3 = p2.x; a4 = p2.y; a5 = p1.x; a6 = p1.y;
			float A = abs((a1 * (a4 - a6) + a3 * (a6 - a2) + a5 * (a2 - a4)) / 2.0);
			float A1 = abs((a * (a4 - a6) + a3 * (a6 - b) + a5 * (b - a4)) / 2.0);
			float A2 = abs((a1 * (b - a6) + a * (a6 - a2) + a5 * (a2 - b)) / 2.0);
			float A3 = abs((a1 * (a4 - b) + a3 * (b - a2) + a * (a2 - a4)) / 2.0);
			if (A == A1 + A2 + A3)
			{
				return false;
			}
			else
			{
				a1 = p1.x; a2 = p6.y; a3 = p6.x; a4 = p6.y; a5 = p1.x; a6 = p1.y;
				float A = abs((a1 * (a4 - a6) + a3 * (a6 - a2) + a5 * (a2 - a4)) / 2.0);
				float A1 = abs((a * (a4 - a6) + a3 * (a6 - b) + a5 * (b - a4)) / 2.0);
				float A2 = abs((a1 * (b - a6) + a * (a6 - a2) + a5 * (a2 - b)) / 2.0);
				float A3 = abs((a1 * (a4 - b) + a3 * (b - a2) + a * (a2 - a4)) / 2.0);
				if (A == A1 + A2 + A3)
				{
					return false;
				}
				
				else
				{
					a1 = p4.x; a2 = p5.y; a3 = p4.x; a4 = p4.y; a5 = p5.x; a6 = p5.y;
					float A = abs((a1 * (a4 - a6) + a3 * (a6 - a2) + a5 * (a2 - a4)) / 2.0);
					float A1 = abs((a * (a4 - a6) + a3 * (a6 - b) + a5 * (b - a4)) / 2.0);
					float A2 = abs((a1 * (b - a6) + a * (a6 - a2) + a5 * (a2 - b)) / 2.0);
					float A3 = abs((a1 * (a4 - b) + a3 * (b - a2) + a * (a2 - a4)) / 2.0);
					if (A == A1 + A2 + A3)
					{
						return false;
					}
					return true;
				}
			}
		}
	}
	return false;
}
void CHexa::printtypeoffigureselected(Output* pout)
{
	pout->PrintMessage("you select a hexagon");
}
void CHexa::movefigure(int a, int b, Output* pout)
{
	Center.x = a;
	Center.y = b;
	pout->DrawHexagon(Center, FigGfxInfo, Selected);
}

void CHexa::Save(ofstream& OutFile)
{
	
	
	OutFile << "HEXA" <<"\t"<<ID << "\t" << Center.x << "\t" << Center.y << "\t" << this->converttostring(UI.DrawColor) << "\t" << this->converttostring(CFigure::GetFillColor());

	
}



void CHexa::Load(ifstream& Infile)
{
	string s;
	Infile >> ID >> Center.x >> Center.y;
	
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
Point CHexa::MakeCenter()
{
	Point P;
	P.x = Center.x;
	P.y = Center.y;
	return P;
}
int CHexa::figuretype()
{
	return 2;
}