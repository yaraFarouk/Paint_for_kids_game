#pragma once

#include "Figures/CFigure.h"

class CHexa : public CFigure
{
private:

	Point Center;
public:
	CHexa(){}
	virtual Point MakeCenter();//to save informtion abount figure
	CHexa(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool IsInside(int a, int b);
	virtual void printtypeoffigureselected(Output* pout);
	virtual void movefigure(int a, int b, Output* pout);
	virtual void Save(ofstream& OutFile);
	
	virtual void Load(ifstream& Infile);
	virtual int figuretype();
	virtual ~CHexa() {}
};
