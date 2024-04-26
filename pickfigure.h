#pragma once
#include "Figures\CFigure.h"
#include "ApplicationManager.h"
#include"Actions/Action.h"

class pickfigure: public Action
{
protected:
	CFigure* pick;
	Point P;
	int Result;
	int FigC;
public:
	pickfigure(ApplicationManager*pApp,int fc);
	virtual void ReadActionParameters();
	virtual void Execute();
	int Figuretype(int& Result);
	~pickfigure();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);
};

