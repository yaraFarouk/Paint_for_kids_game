#pragma once

#include "Figures/CFigure.h"

class CCircle : public CFigure
{
private:
	Point Center;
	Point Corner2;
public:
	CCircle(){}
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool IsInside(int a, int b);
	virtual void printtypeoffigureselected(Output* pout);
	virtual void movefigure(int a, int b,Output* pout);
	virtual void Save(ofstream& OutFile) ;
	
	virtual void Load(ifstream& Infile);
	virtual Point MakeCenter();//to save informtion abount figure
	virtual int figuretype();
	virtual ~CCircle() {}
};


