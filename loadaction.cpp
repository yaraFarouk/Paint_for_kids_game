#include "loadaction.h"
#include"ApplicationManager.h"
#include<fstream>
#include "GUI\input.h"
#include "GUI\Output.h"
#include"CCircle.h"
#include"CHexa.h"
#include"CSquare.h"
#include"CTriangle.h"
#include"Figures/CRectangle.h"
loadaction::loadaction():Action()
{
}

loadaction::loadaction(ApplicationManager* pApp):Action(pApp)
{
	
}

void loadaction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();   
	Input* pIn = pManager->GetInput();     
	pOut->PrintMessage("Enter Filename");
	FileName = pIn->GetSrting(pOut); 
}

string loadaction::converttostring(color c)
{
	if (c == BLACK) return "BLACK";
	else if (c == ORANGE) return "ORANGE";
	else if (c == BLUE) return "BLUE";
	else if (c == RED) return "RED";
	else if (c == YELLOW) return "YELLOW";
	else if (c == GREEN) return "GREEN";
	else if (c == UI.BkGrndColor) return "NO_FILL";
}

color loadaction::converttoColor(string s)
{
	if (s == "BLACK")
		return BLACK;
	if (s == "BLUE")
		return BLUE;
	if (s == "ORANGE")
		return ORANGE;
	if (s == "RED")
		return RED;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "GREEN")
		return GREEN;
	if (s == "NO_FILL")
		return UI.BkGrndColor;
}

void loadaction::Execute()
{
	
	ifstream InFile;        
	Output* pOut = pManager->GetOutput(); 
	Input* pIn = pManager->GetInput();      
	string name,colordraw, colorfill;
	int Count;
	CFigure* figure;
	
	ReadActionParameters();
	InFile.open(FileName + ".txt"); 
	pManager->ExecuteAction(TO_CLEAN);
	pOut->PrintMessage(FileName);

	InFile >> colordraw  >> colorfill;
	UI.DrawColor =this->converttoColor(colordraw);  
	UI.FillColor = this->converttoColor(colorfill);  
	    
	InFile >> Count;   
	for(int i=0;i<Count;i++)
	{
		InFile >> name;

		if (name == "RECT")
			figure = new CRectangle;
		else if (name == "CIRC")
			figure = new CCircle;
		else if (name == "TRIANG")
			figure = new CTriangle;
		else if (name == "HEXA")
			figure = new CHexa;
		else if (name == "SQUAR")
			figure = new CSquare;
		figure->Load(InFile);
		pManager->AddFigure(figure);
		
	}
}
void loadaction::loadplaymodefigs()
{
	
	FileName = "PlayMode";

	Output* pOut = pManager->GetOutput();
	ifstream InFile;         //object of ifstream class
	string name, colordraw, colorfill;

	int Cnt;
	CFigure* figure;


	InFile.open(FileName + ".txt"); //open the file on the disk with FileName name and .txt exetension
	InFile >> colordraw >> colorfill;     //Read the Current FillColor and DrawColor
	UI.DrawColor = this->converttoColor(colordraw);
	UI.FillColor = this->converttoColor(colorfill);  //To Color type
	pManager->cleanfiglist();        //Delete The figure list
	InFile >> Cnt;    //read the Number of Figures

	while (Cnt)            //For each line on the file we will read it and determine its type
	{
		InFile >> name;

		if (name == "RECT")
			figure = new CRectangle;
		else if (name == "CIRC")
			figure = new CCircle;
		else if (name == "TRIANG")
			figure = new CTriangle;
		else if (name == "HEXA")
			figure = new CHexa;
		else if (name == "SQUAR")
			figure = new CSquare;

		figure->Load(InFile);  //Now we created the object and we should load it
		pManager->AddFigure(figure); //Add to the figure list
		Cnt--; //decrease the count 
	}
	pManager->UpdateInterface();     //Draw the figure list
}
void loadaction::UndoFig(CFigure* F)
{

}
void loadaction::RedoFig(CFigure* F)
{

}