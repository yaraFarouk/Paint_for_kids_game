#pragma once

#include "Actions/Action.h"

//Add hexa Action class
class AddHexaAction : public Action
{
private:
	Point P1; //hexa Center
	GfxInfo HexaGfxInfo;
public:
	AddHexaAction(ApplicationManager* pApp);

	//Reads hexa parameters
	virtual void ReadActionParameters();

	//Add hexa to the ApplicationManager
	virtual void Execute();
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);//function for redo fig

};
