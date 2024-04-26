#pragma once
#include "Figures/CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
public:
	CTriangle(){}
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool IsInside(int a, int b);
	virtual void printtypeoffigureselected(Output* pout);
	virtual void movefigure(int a, int b, Output* pout);
	virtual void Save(ofstream& OutFile);
	
	virtual void Load(ifstream& Infile);
	virtual Point MakeCenter();
	virtual int figuretype();
	virtual ~CTriangle() {}
};