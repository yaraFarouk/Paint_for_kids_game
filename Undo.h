#pragma once
#include "Actions/Action.h"
class Undo :public Action
{
	Action* Act;//to assigument the last action in arrAction in the Act
	CFigure* Fig;//to assigument the last fig which change in arrFig in the Fig
	
public:

	Undo(ApplicationManager* pApp, Action* A, CFigure* F);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};