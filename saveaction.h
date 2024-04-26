#pragma once
#include"Actions/Action.h"
#include "fstream"
class saveaction: public Action
{
protected:
	string FileName;
	int FigCt;
public:
	saveaction();
	saveaction(ApplicationManager* pApp,int fc);
	virtual void ReadActionParameters();
	string colorname(color c);
	color Color(string s);
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);
	void saveplaymodefigs();
	virtual void Execute();
};

