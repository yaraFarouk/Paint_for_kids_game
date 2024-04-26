#pragma once

#include"Actions/Action.h"
class Clear : public Action
{

public:
	Clear(ApplicationManager* pApp);


	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();//Ececute clear action
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};
