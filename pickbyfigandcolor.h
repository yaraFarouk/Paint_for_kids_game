#pragma once
#include "Figures/CFigure.h"
#include"Actions/Action.h"
#include"ApplicationManager.h"
class pickbyfigandcolor: public Action
{
protected:
		CFigure* pick;
		Point P;
		int Result;
		int FigCount;
		GfxInfo pickGfxInfo;
	public:
		pickbyfigandcolor(ApplicationManager* pApp,int fc);
		virtual void ReadActionParameters();
		virtual void Execute();
		int coloredfigure(int& Result);
		virtual void UndoFig(CFigure* F);
		virtual void RedoFig(CFigure* F1);
};

