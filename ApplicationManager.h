#pragma once
#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include"ToRecord.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures
private:
	int FigCount;		//Actual number of figures
	int CountF;//count of arrfig
	int CountF2;//Count for redo
	int CountA2;//count for action redo
	int CountA;
	CFigure* ArrFigUndo[5];//arr to save the last 5 fig 
	CFigure* ArrFigRedo[5];//arr for figure redo
	Action* ArrActionRedo[5];
	Action* ArrActionUndo[5];
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* SelectedFig; //Pointer to the selected figure
	//Pointers to Input and Output classes
	ActionType A;
	Input *pIn;
	Output *pOut;
	GfxInfo pickGfxInfo;
	ToRecord* TR;
	bool isclick;
	int Pcount;
	bool ispclicked;
	Action* LAAct;
	int reundocnt;
	int reredocnt;
	CFigure* ftg;
	int redoinfo;
	int rr;
	//int undocnt;
public:	
	ApplicationManager(); 
	~ApplicationManager();
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);  //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window
	void UnSelectAll();
	bool IsAnyFigureIsSelected();
	CFigure* GetTheSelected();
	void ClearAll();
	ActionType GetTheAlreadyAction();//get the last action
	void SetTheLastAction(ActionType Act);
	void DeleteFigure(CFigure* ptr);
	void rearrange(CFigure* ptr);
	void SaveAll( ofstream& OutFile);
	
	ToRecord* GetRecordControl();
	bool isclicked();
	void seticclicked(bool a);
	bool Getispclicked();
	void setispclicked(bool a);
	int GetPcount();
	void setPcount(int a);
	bool isfigurelistempty();
	void AddAction(Action* p);//add action to arractioundo
	void DeleteAction();
	void AddFigForUndo(CFigure* f);
	void AddActionRedo(Action* p);//add action to arractinredo
	void AddFigForRedo(CFigure* f);
	void DeleteActionRedo();
	void CallLoad();
	void CallSave();
	void cleanfiglist();
	void setlastact(Action* acr);
	Action* getlastact();
	void getundoedactionandfig();
	void setlastfig(CFigure* acr);
	CFigure* getlastfig();
	int getundocount();
	void setundocount(int a);
	//void setreundocnt(int a);
	void getredoedactionandfig(Action* ttr, CFigure* cgg);
	/*int getrndocount();
	void setrndocount(int a);*/
	void setredoinfo(int a) { redoinfo = a; }
	int getredoinfo() { return redoinfo; }
	void IfNotUndo();
	void setrr(int a) { rr=a; }
	int getrr() { return rr; }
	int figuretype(int i);
	color figurecolor(int i);
};

