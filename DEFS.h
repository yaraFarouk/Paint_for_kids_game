#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle
	DRAW_CIRCLE,
	DRAW_HEXA,
	DRAW_TRI,
	DRAW_SQUARE,
	TO_SWITCH,
	TO_UNDO,
	TO_REDO,
	C_FRAM,
	C_GREEN,
	C_ORANGE,
	C_RED,
	C_BLUE,
	C_YELLOW,
	C_BLACK,
	TO_SAVE,
	TO_LOAD,
	TO_STOP,
	TO_MOVE,
	TO_CLEAN,
	TO_START,
	TO_PLAY_RECORD,
	TO_SELECT,
	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	TO_HIDE,
	TO_PICK,
	TO_DELETE,
	TO_SWITCH2,
	DRAWINGTOOLBAR,
	TO_PICK_COLOR,
	TO_PICK_COLORED_FIGURE,
	STATUS			//A click on the status bar

	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders
};

#endif