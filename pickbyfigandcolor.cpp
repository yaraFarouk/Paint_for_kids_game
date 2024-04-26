#include "pickbyfigandcolor.h"
#include "pickfigure.h"
#include"CCircle.h"
#include"ApplicationManager.h"
#include"CHexa.h"
#include"CSquare.h"
#include"CTriangle.h"
#include"Figures/CRectangle.h"
#include"loadaction.h"
#include"Actions/Action.h"
pickbyfigandcolor::pickbyfigandcolor(ApplicationManager* pApp, int fc) : Action(pApp)
{
	FigCount = fc;
}

void pickbyfigandcolor::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();

	pIn->GetPointClicked(P.x, P.y);
}

void pickbyfigandcolor::Execute()
{

	ActionType Actiontype;
	Output* pOut = pManager->GetOutput();
	Input* pIN = pManager->GetInput();
	Result = 0;

	int t = this->coloredfigure(Result);
	if (t == 11)
		pOut->PrintMessage("pick all red circles");
	else if (t == 12)
		pOut->PrintMessage("pick all yellow circles");
	else if (t == 13)
		pOut->PrintMessage("pick all green circles");
	else if (t == 14)
		pOut->PrintMessage("pick all blue circles");
	else if (t == 15)
		pOut->PrintMessage("pick all orange circles");
	else if (t == 16)
		pOut->PrintMessage("pick all black circles");
	else if (t == 21)
		pOut->PrintMessage("pick all red hexagons");
	else if (t == 22)
		pOut->PrintMessage("pick all yellow hexagons");
	else if (t == 23)
		pOut->PrintMessage("pick all green hexagons");
	else if (t == 24)
		pOut->PrintMessage("pick all blue hexagons");
	else if (t == 25)
		pOut->PrintMessage("pick all orange hexagons");
	else if (t == 26)
		pOut->PrintMessage("pick all black hexagons");
	else if (t == 31)
		pOut->PrintMessage("pick all red recangles");
	else if (t == 32)
		pOut->PrintMessage("pick all yellow recangles");
	else if (t == 33)
		pOut->PrintMessage("pick all green recangles");
	else if (t == 34)
		pOut->PrintMessage("pick all blue recangles");
	else if (t == 35)
		pOut->PrintMessage("pick all orange recangles");
	else if (t == 36)
		pOut->PrintMessage("pick all black recangles");
	else if (t == 41)
		pOut->PrintMessage("pick all red squares");
	else if (t == 42)
		pOut->PrintMessage("pick all yellow squares");
	else if (t == 43)
		pOut->PrintMessage("pick all green squares");
	else if (t == 44)
		pOut->PrintMessage("pick all blue squares");
	else if (t == 45)
		pOut->PrintMessage("pick all orange squares");
	else if (t == 46)
		pOut->PrintMessage("pick all black squares");
	else if (t == 51)
		pOut->PrintMessage("pick all red triangles");
	else if (t == 52)
		pOut->PrintMessage("pick all yellow triangles");
	else if (t == 53)
		pOut->PrintMessage("pick all green triangles");
	else if (t == 54)
		pOut->PrintMessage("pick all blue triangles");
	else if (t == 55)
		pOut->PrintMessage("pick all orange triangles");
	else if (t == 56)
		pOut->PrintMessage("pick all black triangles");


	pManager->UpdateInterface();

	if (t != 0)
	{
		int i, counter = 0;
		int Res = Result;

		for (i = 0; i < 200;)
		{
			if (Result == 0) //break when figures that should be selected finishes
				break;

			ReadActionParameters();

			if (P.y >= 0 && P.y <= UI.ToolBarHeight)
			{
				if (P.x < UI.MenuItemWidth)
					Actiontype = TO_PICK_COLORED_FIGURE;

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
				CCircle* circ = dynamic_cast<CCircle*>(pick);
				CRectangle* rect = dynamic_cast<CRectangle*>(pick);
				CSquare* squar = dynamic_cast<CSquare*>(pick);
				CHexa* hexa = dynamic_cast<CHexa*>(pick);
				CTriangle* tri = dynamic_cast<CTriangle*>(pick);

				color c = pick->GetFillColor();

				if (circ != NULL && t == 11 && c == RED)
					Result--;
				else if (circ != NULL && t == 12 && c == YELLOW)
					Result--;
				else if (circ != NULL && t == 13 && c == GREEN)
					Result--;
				else if (circ != NULL && t == 14 && c == BLUE)
					Result--;
				else if (circ != NULL && t == 15 && c == ORANGE)
					Result--;
				else if (circ != NULL && t == 16 && c == BLACK)
					Result--;
				else if (hexa != NULL && t == 21 && c == RED)
					Result--;
				else if (hexa != NULL && t == 22 && c == YELLOW)
					Result--;
				else if (hexa != NULL && t == 23 && c == GREEN)
					Result--;
				else if (hexa != NULL && t == 24 && c == BLUE)
					Result--;
				else if (hexa != NULL && t == 25 && c == ORANGE)
					Result--;
				else if (hexa != NULL && t == 26 && c == BLACK)
					Result--;
				else if (rect != NULL && t == 31 && c == RED)
					Result--;
				else if (rect != NULL && t == 32 && c == YELLOW)
					Result--;
				else if (rect != NULL && t == 33 && c == GREEN)
					Result--;
				else if (rect != NULL && t == 34 && c == BLUE)
					Result--;
				else if (rect != NULL && t == 35 && c == ORANGE)
					Result--;
				else if (rect != NULL && t == 36 && c == BLACK)
					Result--;
				else if (squar != NULL && t == 41 && c == RED)
					Result--;
				else if (squar != NULL && t == 42 && c == YELLOW)
					Result--;
				else if (squar != NULL && t == 43 && c == GREEN)
					Result--;
				else if (squar != NULL && t == 44 && c == BLUE)
					Result--;
				else if (squar != NULL && t == 45 && c == ORANGE)
					Result--;
				else if (squar != NULL && t == 46 && c == BLACK)
					Result--;
				else if (tri != NULL && t == 51 && c == RED)
					Result--;
				else if (tri != NULL && t == 52 && c == YELLOW)
					Result--;
				else if (tri != NULL && t == 53 && c == GREEN)
					Result--;
				else if (tri != NULL && t == 54 && c == BLUE)
					Result--;
				else if (tri != NULL && t == 55 && c == ORANGE)
					Result--;
				else if (tri != NULL && t == 56 && c == BLACK)
					Result--;



				pick->SetSelected(true);
				pManager->ExecuteAction(TO_DELETE);

				pManager->UpdateInterface();
				pick = NULL;

			}
			counter++;

		}
		pOut->PrintMessage(to_string(Res) + " Correct & " + to_string(counter - Res) + " InCorrect");
	}

}
int pickbyfigandcolor::coloredfigure(int& Result)
{
	int tc(0);
	int tfig(0);
	color c;
	int count = 10 * FigCount;
	if (FigCount != 0)
	{
		int type = rand() % FigCount + 0;


		c = pManager->figurecolor(type);


		if (c != UI.BkGrndColor)//return the color of the figure should be selected
		{
			if (c == RED)
				tc = 1;
			else if (c == YELLOW)
				tc = 2;
			else if (c == GREEN)
				tc = 3;
			else if (c == BLUE)
				tc = 4;
			else if (c == ORANGE)
				tc = 5;
			else if (c == BLACK)
				tc = 6;
		}

		int ttype = pManager->figuretype(type); //return type of current  figure should be selected

		if (ttype == 1 && tc == 1)
			tfig = 11;

		else if (ttype == 1 && tc == 2)
			tfig = 12;

		else if (ttype == 1 && tc == 3)
			tfig = 13;

		else if (ttype == 1 && tc == 4)
			tfig = 14;

		else if (ttype == 1 && tc == 5)
			tfig = 15;
		else if (ttype == 1 && tc == 6)
			tfig = 16;

		else if (ttype == 2 && tc == 1)
			tfig = 21;
		else if (ttype == 2 && tc == 2)
			tfig = 22;
		else if (ttype == 2 && tc == 3)
			tfig = 23;
		else if (ttype == 2 && tc == 4)
			tfig = 24;
		else if (ttype == 2 && tc == 5)
			tfig = 25;
		else if (ttype == 2 && tc == 6)
			tfig = 26;
		else if (ttype == 3 && tc == 1)
			tfig = 31;
		else if (ttype == 3 && tc == 2)
			tfig = 32;
		else if (ttype == 3 && tc == 3)
			tfig = 33;
		else if (ttype == 3 && tc == 4)
			tfig = 34;
		else if (ttype == 3 && tc == 5)
			tfig = 35;
		else if (ttype == 3 && tc == 6)
			tfig = 36;
		else if (ttype == 4 && tc == 1)
			tfig = 41;
		else if (ttype == 4 && tc == 2)
			tfig = 42;
		else if (ttype == 4 && tc == 3)
			tfig = 43;
		else if (ttype == 4 && tc == 4)
			tfig = 44;
		else if (ttype == 4 && tc == 5)
			tfig = 45;
		else if (ttype == 4 && tc == 6)
			tfig = 46;
		else if (ttype == 5 && tc == 1)
			tfig = 51;
		else if (ttype == 5 && tc == 2)
			tfig = 52;
		else if (ttype == 5 && tc == 3)
			tfig = 53;
		else if (ttype == 5 && tc == 4)
			tfig = 54;
		else if (ttype == 5 && tc == 5)
			tfig = 55;
		else if (ttype == 5 && tc == 6)
			tfig = 56;

		for (int i = 0;i < FigCount;i++) //for loopcalculate number of figure the kid should select
		{
			int t = pManager->figuretype(i);
			if (t == 1 && tfig == 11 && c == RED)
				Result++;
			else if (t == 1 && tfig == 12 && c == YELLOW)
				Result++;
			else if (t == 1 && tfig == 13 && c == GREEN)
				Result++;
			else if (t == 1 && tfig == 14 && c == BLUE)
				Result++;
			else if (t == 1 && tfig == 15 && c == ORANGE)
				Result++;
			else if (t == 1 && tfig == 16 && c == BLACK)
				Result++;
			else if (t == 2 && tfig == 21 && c == RED)
				Result++;
			else if (t == 2 && tfig == 22 && c == YELLOW)
				Result++;
			else if (t == 2 && tfig == 23 && c == GREEN)
				Result++;
			else if (t == 2 && tfig == 24 && c == BLUE)
				Result++;
			else if (t == 2 && tfig == 25 && c == ORANGE)
				Result++;
			else if (t == 2 && tfig == 26 && c == BLACK)
				Result++;
			else if (t == 3 && tfig == 31 && c == RED)
				Result++;
			else if (t == 3 && tfig == 32 && c == YELLOW)
				Result++;
			else if (t == 3 && tfig == 33 && c == GREEN)
				Result++;
			else if (t == 3 && tfig == 34 && c == BLUE)
				Result++;
			else if (t == 3 && tfig == 35 && c == ORANGE)
				Result++;
			else if (t == 3 && tfig == 36 && c == BLACK)
				Result++;
			else if (t == 4 && tfig == 41 && c == RED)
				Result++;
			else if (t == 4 && tfig == 42 && c == YELLOW)
				Result++;
			else if (t == 4 && tfig == 43 && c == GREEN)
				Result++;
			else if (t == 4 && tfig == 44 && c == BLUE)
				Result++;
			else if (t == 4 && tfig == 45 && c == ORANGE)
				Result++;
			else if (t == 4 && tfig == 46 && c == BLACK)
				Result++;
			else if (t == 5 && tfig == 51 && c == RED)
				Result++;
			else if (t == 5 && tfig == 52 && c == YELLOW)
				Result++;
			else if (t == 5 && tfig == 53 && c == GREEN)
				Result++;
			else if (t == 5 && tfig == 54 && c == BLUE)
				Result++;
			else if (t == 5 && tfig == 55 && c == ORANGE)
				Result++;
			else if (t == 5 && tfig == 56 && c == BLACK)
				Result++;

		}

	}
	return tfig;
}
void pickbyfigandcolor::UndoFig(CFigure* F)
{

}
void pickbyfigandcolor::RedoFig(CFigure* F)
{

}