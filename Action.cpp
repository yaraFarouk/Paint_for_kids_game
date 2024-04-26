#include"Actions/Action.h"
#include"ApplicationManager.h"
#include"Figures/CRectangle.h"
#include"CCircle.h"
#include"CHexa.h"
#include"CSquare.h"
#include"CTriangle.h"
//count for but information Color


Action::Action(ApplicationManager* pApp) {
	pManager = pApp;
	ButAct = false;
}


void Action::AddArrPoint(Point P)
{
	if (CountIn < 5)
	{
		ArrPoint[CountIn++] = P;
	}
	else
	{
		for (int i = 0; i < CountIn - 1; i++)
		{
			ArrPoint[i] = ArrPoint[i + 1];
		}
		CountIn -= 1;
		ArrPoint[CountIn++] = P;
	}
}
void Action::AddArrColor(GfxInfo c)
{
	if (CountC < 5)
	{
		ArrColor[CountC++] = c;
	}
	else
	{
		for (int i = 0; i < CountC - 1; i++)
		{
			ArrColor[i] = ArrColor[i + 1];
		}
		CountC -= 1;
		ArrColor[CountC++] = c;
	}
}

void Action::AddArrPointRedo(Point P)
{
	if (CountIn2 < 5)
	{
		ArrPoint2[CountIn2++] = P;
	}
	else
	{
		for (int i = 0; i < CountIn2 - 1; i++)
		{
			ArrPoint2[i] = ArrPoint2[i + 1];
		}
		CountIn2 -= 1;
		ArrPoint2[CountIn2++] = P;
	}
}
void Action::AddArrColorRedo(GfxInfo c)
{
	if (CountC2 < 5)
	{
		ArrColor2[CountC2++] = c;
	}
	else
	{
		for (int i = 0; i < CountC2 - 1; i++)
		{
			ArrColor2[i] = ArrColor2[i + 1];
		}
		CountC2 -= 1;
		ArrColor2[CountC2++] = c;
	}
}
void Action::SetAct(bool b)
{
	ButAct = b;//put id i will put in arr or not
}
bool Action::getAct()
{
	return ButAct;
}

