#pragma once
#include "Figures/CFigure.h"

class CSquare : public CFigure
{
private:
	Point center;
public:
	CSquare();
	CSquare(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool IsInside(int a, int b);
	virtual void printtypeoffigureselected(Output* pout);
	virtual void movefigure(int a, int b, Output* pout);
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& Infile);
	virtual Point MakeCenter();
	virtual int figuretype();
	virtual ~CSquare() {}

};
