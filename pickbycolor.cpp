#include "pickbycolor.h"
#include"loadaction.h"
#include"CCircle.h"
#include"CHexa.h"
#include"CSquare.h"
#include"CTriangle.h"
#include"Figures/CRectangle.h"
#include"Figures/CFigure.h"
pickbycolor::pickbycolor(ApplicationManager* pApp, int fc) : Action(pApp)
{
	figcount = fc;
}



void pickbycolor::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();

	pIn->GetPointClicked(P.x, P.y);
}

void pickbycolor::Execute()
{
	ActionType Actiontype;
	Output* pOut = pManager->GetOutput();
	Input* pIN = pManager->GetInput();

	Result = 0;


	int t = this->figcolor(Result);

	if (t == 1)
		pOut->PrintMessage("pick all red figures");
	else if (t == 2)
		pOut->PrintMessage("pick all yellow figures");
	else if (t == 3)
		pOut->PrintMessage("pick all green figures");
	else if (t == 4)
		pOut->PrintMessage("pick all blue figures");
	else if (t == 5)
		pOut->PrintMessage("pick all orange figures");
	else if (t == 6)
		pOut->PrintMessage("pick all black figures");

	pManager->UpdateInterface();



	if (t != 0)
	{
		int i, Counter = 0;
		int Res = Result;

		for (i = 0; i < 200;)
		{
			if (Result == 0)
				break;

			ReadActionParameters();
			if (P.y >= 0 && P.y <= UI.ToolBarHeight)
			{
				if (P.x < UI.MenuItemWidth)
					Actiontype = TO_PICK_COLOR;

				else
					continue;
				pManager->ExecuteAction(Actiontype);
				return;
			}
			else if (P.y > UI.height - UI.StatusBarHeight)
				continue;

			pick = pManager->GetFigure(P.x, P.y);

			if (pick != NULL)
			{
				i++;

				color c = pick->GetFillColor();

				if (t == 1 && c == RED)
					Result--;
				else if (t == 2 && c == YELLOW)
					Result--;
				else if (t == 3 && c == GREEN)
					Result--;
				else if (t == 4 && c == BLUE)
					Result--;
				else if (t == 5 && c == ORANGE)
					Result--;
				else if (t == 6 && c == BLACK)
					Result--;
				pick->SetSelected(true);
				pManager->ExecuteAction(TO_DELETE);
				pManager->UpdateInterface();
				pick = NULL;
			}
			Counter++;
		}
		pOut->PrintMessage(to_string(Res) + " Correct & " + to_string(Counter - Res) + " InCorrect");
	}
}

int pickbycolor::figcolor(int& Result)
{

	int type1(0);
	color c;
	//int count = 10 * figcount;
	if (figcount != 0)
	{

		int type = rand() % figcount + 0;
		c = pManager->figurecolor(type);



		if (c != UI.BkGrndColor)
		{
			if (c == RED)
				type1 = 1;
			else if (c == YELLOW)
				type1 = 2;
			else if (c == GREEN)
				type1 = 3;
			else if (c == BLUE)
				type1 = 4;
			else if (c == ORANGE)
				type1 = 5;
			else if (c == BLACK)
				type1 = 6;


			for (int i = 0; i < figcount; i++)
			{

				c = pManager->figurecolor(i);

				if (type1 == 1 && c == RED)
					Result++;
				else if (type1 == 2 && c == YELLOW)
					Result++;
				else if (type1 == 3 && c == GREEN)
					Result++;
				else if (type1 == 4 && c == BLUE)
					Result++;
				else if (type1 == 5 && c == ORANGE)
					Result++;
				else if (type1 == 6 && c == BLACK)
					Result++;
			}
		}
	}
	return type1;
}
void pickbycolor::UndoFig(CFigure* F)
{

}
void pickbycolor::RedoFig(CFigure* F)
{

}


