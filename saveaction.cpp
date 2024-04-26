#include "saveaction.h"
#include"Actions/Action.h"
#include "ApplicationManager.h"

/*saveaction::saveaction():Action()
{
}*/

saveaction::saveaction(ApplicationManager* pApp,int fc) : Action(pApp)
{
	FileName = "TEST";
	FigCt = fc;    //We need the figure number to write it on the file
}
void saveaction::ReadActionParameters()
{
	Output* pOut= pManager->GetOutput();   //Pointer to Output
	Input* pIn= pManager->GetInput();      //Pointer to Input

	pOut->PrintMessage("Enter Filename");
	FileName = pIn->GetSrting(pOut);  //read the file name
}

string saveaction::colorname(color c)
{
	if (c == BLACK) return "BLACK";
	else if (c == ORANGE) return "ORANGE";
	else if (c == BLUE) return "BLUE";
	else if (c == RED) return "RED";
	else if (c == YELLOW) return "YELLOW";
	else if (c == GREEN) return "GREEN";
	else if (c == UI.BkGrndColor) return "NO_FILL";
	
}

color saveaction::Color(string s)
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

void saveaction::Execute()
{
	ReadActionParameters();
	
	ofstream OutFile; 
	OutFile.open(FileName + ".txt");  
	OutFile <<this->colorname(UI.DrawColor) << "\t" << this->colorname(UI.FillColor) << "\t" << endl;
	OutFile << FigCt << "\t" << endl;
	pManager->SaveAll( OutFile);
	OutFile.close();

}
void saveaction::saveplaymodefigs()
{
	FileName = "PlayMode";
	ofstream OutFile;   //object of ofstream to write on the disk
	OutFile.open(FileName + ".txt");  // create a file with FileName and .txt exetention
	OutFile << this->colorname(UI.DrawColor) << "\t" << this->colorname(UI.FillColor) << "\t" << endl;
	OutFile << FigCt << "\n";  //and Current Fill Color and in the second line write the number of figures 
	pManager->SaveAll(OutFile);  //Now Start Saving each figure proccess 
	OutFile.close(); //Good By :)
}
void saveaction::UndoFig(CFigure* F)
{

}
void saveaction::RedoFig(CFigure* F)
{

}