#pragma once
#include"Actions/Action.h"
class ToRecord : public Action
{
protected:
	enum { MAX_ACTIONS = 20 };
	int ActCount;
	Action* Actn;
	struct node {
		Action* Actnx;
		ActionType ac;
		ActionType ac1;
		Point p;
		Point p1;
		Point p2;
		CFigure* cf;
		Action* ActTosnd;
		Action* Actnxtoredo;
		CFigure* cftoredo;
		color cfill;
		color cdraw;
	};
	node ActList[MAX_ACTIONS];
public:

	ToRecord(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	void AddAction(Action* ActTR);
	int getActCount();
	node* GetActList() { return ActList; }
	virtual void UndoFig(CFigure* F);
	virtual void RedoFig(CFigure* F1);
	/*CFigure* getfig(int i);
	Action* getactionfromlist(int i);*/
};