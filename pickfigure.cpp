#include "pickfigure.h"
#include "ApplicationManager.h"
#include"Actions/Action.h"
#include"CCircle.h"
#include"CHexa.h"
#include"CSquare.h"
#include"CTriangle.h"
#include"Figures/CRectangle.h"
#include"loadaction.h"
#include"Delete.h"
pickfigure::pickfigure(ApplicationManager* pApp, int fc) : Action(pApp)
{
	FigC = fc;
}


void pickfigure::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();

	pIn->GetPointClicked(P.x, P.y);

}

void pickfigure::Execute()
{
	ActionType Actiontype;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	Result = 0;

	int t = this->Figuretype(Result);
	if (t == 1)
		pOut->PrintMessage("pick all circles");
	else if (t == 2)
		pOut->PrintMessage("pick all hexagon");
	else if (t == 3)
		pOut->PrintMessage("pick all rectangles");
	else if (t == 4)
		pOut->PrintMessage("pick all squares");
	else if (t == 5)
		pOut->PrintMessage("pick all triangles");

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
					Actiontype = TO_PICK;

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
				CCircle* circ = dynamic_cast<CCircle*>(pick); //make a pointer of the figure should be selected
				CRectangle* rect = dynamic_cast<CRectangle*>(pick);
				CSquare* squar = dynamic_cast<CSquare*>(pick);
				CHexa* hexa = dynamic_cast<CHexa*>(pick);
				CTriangle* tri = dynamic_cast<CTriangle*>(pick);

				if (circ != NULL && t == 1)
					Result--;
				else if (hexa != NULL && t == 2)
					Result--;
				else if (rect != NULL && t == 3)
					Result--;
				else if (squar != NULL && t == 4)
					Result--;
				else if (tri != NULL && t == 5)
					Result--;

				pick->SetSelected(true);
				pManager->ExecuteAction(TO_DELETE);
				pManager->UpdateInterface();
				pick = NULL;
			}
			counter++;//number of figure selected
		}
		pOut->PrintMessage(to_string(Res) + " Correct & " + to_string(counter - Res) + " InCorrect"); //print final result

	}
}

int pickfigure::Figuretype(int& Result)
{

	int type1(0);
	if (FigC != 0)
	{
		int type = rand() % FigC + 0;


		type1 = pManager->figuretype(type);


		for (int i = 0; i < FigC; i++)//for loopcalculate number of figure the kid should select
		{
			int t = pManager->figuretype(i);
			if (type1 == 1 && t == 1)
				Result++;
			else if (type1 == 2 && t == 2)
				Result++;
			else if (type1 == 3 && t == 3)
				Result++;
			else if (type1 == 4 && t == 4)
				Result++;
			else if (type1 == 5 && t == 5)
				Result++;
		}
	}
	return type1;
}

pickfigure::~pickfigure()
{
}
void pickfigure::UndoFig(CFigure* F)
{

}
void pickfigure::RedoFig(CFigure* F)
{

}