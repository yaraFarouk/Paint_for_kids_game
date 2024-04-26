#pragma once
#include"Actions/Action.h"
#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"
class loadaction:public Action
{
protected:
	string FileName;
	
public:
	loadaction();
	loadaction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	void loadplaymodefigs();
	string converttostring(color c);
	color  converttoColor(string s);
	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);
};

