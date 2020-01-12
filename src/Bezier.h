#pragma once

#include "Figure.h"
#include <math.h>
class CBezier : public CFigure
{
	public:
	int clicks;
	CBezier();
	~CBezier();
	void drawDot(int, int);
	void drawLine(int x1, int x2, int y1, int y2);
	void drawPixel(int, int);
	void display();
	void createBezier();
};