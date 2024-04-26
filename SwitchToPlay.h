#pragma once
#include "Actions/Action.h"

class SwitchToPlay : public Action
{
public:
	SwitchToPlay(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);
};