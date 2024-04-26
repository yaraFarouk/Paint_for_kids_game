#pragma once
#include "Figures/CFigure.h"
#include"Actions/Action.h"
class pickbycolor: public Action 
{
protected:
	CFigure* pick;
	Point P;
	GfxInfo pickGfxInfo;
	int Result;
	int figcount;
public:
	pickbycolor(ApplicationManager*pApp,int fc);
	
	virtual void ReadActionParameters();
	virtual void Execute();
	int figcolor(int& Result);
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);
	
};

