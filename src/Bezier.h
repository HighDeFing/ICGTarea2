#pragma once

#include "Figure.h"
#include <math.h>
#include <vector>
#include <algorithm>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class CBezier : public CFigure
{
	public:
	CBezier* Curva = this;
	int clicks;
	CBezier();
	~CBezier();
	void boundingbox();
	void drawDot(int, int);
	void drawLine(int x1, int x2, int y1, int y2);
	void drawPixel(int, int);
	void draw_rectangle(int x1, int x2, int y1, int y2);
	void display();
	std::vector<CFigure::Puntos> Elevar_Grado();
	void createBezier();
};