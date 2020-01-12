#include "Bezier.h"
#include <math.h>

#include <iostream>
#include <vector>

class Puntos {
public:
	float x, y;
	void setxy(float x2, float y2) { x = x2; y = y2; }
	const Puntos& operator=(const Puntos& rPoint) {
		x = rPoint.x;
		y = rPoint.y;
		return *this;
	}

};


CBezier::CBezier()
{
	mVertices = new float* [100];
	for (int i = 0; i < 100; ++i)
		mVertices[i] = new float[100];

	mType = BEZIER;
}

CBezier::~CBezier()
{
	for (int i = 0; i < 100; ++i)
		delete[] mVertices[i];
}

void CBezier::drawDot(int x, int y)
{
	glColor3fv(dColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CBezier::display()
{

	int xa, ya, xb, yb;
	int x1, x2, x3, y1, y2, y3;
	int x, y;
	x1 = mVertices[0][0]; x2 = mVertices[1][0]; x3 = mVertices[2][0];
	y1 = mVertices[0][1]; y2 = mVertices[1][1]; y3 = mVertices[2][1];
	
	std::vector<Puntos> C;
	/*Puntos* rev = new Puntos();
	rev->setxy(mVertices[0][0], mVertices[0][1]);
	C.push_back(*rev);
	drawDot(C[0].x, C[0].y);*/
	for (int i = 0; i <= getClicks(); i++)
	{
		Puntos *aux = new Puntos();
		aux->setxy(mVertices[i][0], mVertices[i][1]);
		C.push_back(*aux);
		//C[i].x = mVertices[i][0];
		//C[i].y = mVertices[i][1];
		drawDot(C[i].x, C[i].y);
		if (i > 0)
			drawLine(C[i].x, C[i].y, C[i - 1].x, C[i - 1].y);
	}
	float VertXY1[2];
	int NumeroVertices = C.size();
	double paso = 0.001;
	glColor3fv(mColor);
	//glLineStipple(1, 0xEFEF);
	//glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_STRIP);
		for (double t = 0.0; t <= 1.0; t += paso)
		{
			
			for (int r = 0; r < (NumeroVertices - 1); r++) 
			{
				for (int i = 0; i < ((NumeroVertices - 1) - r); i++)
				{
				C[i].x = float((1.0 - t) * C[i].x) + float(t * C[i + 1].x);
				C[i].y = float((1.0 - t) * C[i].y) + float(t * C[i + 1].y);
				}
			}
			VertXY1[0] = C[0].x;
			VertXY1[1] = C[0].y;
			glVertex2fv(VertXY1);
		}
	glEnd();
	glFlush();
}

void  CBezier::createBezier() {

}

void CBezier::drawLine(int x1, int y1, int x2, int y2) {

	glColor3fv(lColor);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	//glFlush();
}

void CBezier::drawPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}



