#include "Bezier.h"
#include <math.h>

#include <iostream>
#include <vector>

/*class Puntos {
public:
	float x, y;
	void setxy(float x2, float y2) { x = x2; y = y2; }
	const Puntos& operator=(const Puntos& rPoint) {
		x = rPoint.x;
		y = rPoint.y;
		return *this;
	}

};*/

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

void CBezier::drawSelectDot(int x, int y)
{
	glColor3fv(dsColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void CBezier::ColorVertex(int id, bool x)
{
	ControlPoints[id].selected = x;
}

void CBezier::deleteVertex(int id)
{
	if (ControlPoints[id].selected)
	{
		//ControlPoints[id].selected = false;
		ControlPoints.erase(ControlPoints.begin() + id);
	}
}

static bool abs_compare(int a, int b)
{
	return (std::abs(a) < std::abs(b));
}

void CBezier::display()
{

	float VertXY1[2];
	double paso = 0.001;
	std::vector<Puntos> C;
	std::vector<Puntos> Caux;
	int NumeroVertices = 0;
	if (bFirst) {
		for (int i = 0; i <= getClicks(); i++)
		{
			Puntos* aux = new Puntos();
			aux->setxy(mVertices[i][0], mVertices[i][1]);
			C.push_back(*aux);
		}
		ControlPoints = C;
	}
	else {
		for (int i = 0; i <= ControlPoints.size(); i++)
		{
			Puntos* aux = new Puntos();
			aux->setxy(mVertices[i][0], mVertices[i][1]);
			C.push_back(*aux);
		}
	}
	//glLineStipple(1, 0xEFEF);
	//glEnable(GL_LINE_STIPPLE);
	NumeroVertices = ControlPoints.size();
	//std::cout << ControlPoints.size() << std::endl;
	for (int i = 0; i <= NumeroVertices - 1; i++) {
		drawDot(ControlPoints[i].x, ControlPoints[i].y);
		if (ControlPoints[i].getSelected())
		{
			drawSelectDot(ControlPoints[i].x, ControlPoints[i].y);
		}
		if (i > 0) {
			drawLine(ControlPoints[i].x, ControlPoints[i].y, ControlPoints[i - 1].x, ControlPoints[i - 1].y);
		}
	}
	glColor3fv(mColor);
	glBegin(GL_LINE_STRIP);
		for (double t = 0.0; t <= 1.0; t += paso)
		{
			C = ControlPoints;
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
	float max[2], min[2]; //max[0]=x max[1]=y min[0]=x min[1]=y
	max[0] = ControlPoints[0].x;
	max[1] = ControlPoints[0].y;
	min[0] = ControlPoints[0].x;
	min[1] = ControlPoints[0].y;
	//std::cout << ControlPoints.size() << std::endl;
	for (int i = 0; i < ControlPoints.size(); i++) {
		for (int j = 0; j < ControlPoints.size(); j++) {
			max[0] = MAX(max[0], MAX(ControlPoints[i].x, ControlPoints[j].x));
			max[1] = MAX(max[1], MAX(ControlPoints[i].y, ControlPoints[j].y));
			min[0] = MIN(min[0], MIN(ControlPoints[i].x, ControlPoints[j].x));
			min[1] = MIN(min[1], MIN(ControlPoints[i].y, ControlPoints[j].y));
		}
	}
	//std::cout << min[0] << std::endl;
	minf[0] = min[0]; minf[1] = min[1]; maxf[0] = max[0]; maxf[1] = max[1];
	if (bbox) {
		draw_rectangle(min[0], max[0], min[1], max[1]);
	}
}

void CBezier::boundingbox()
{
}

void  CBezier::createBezier() {

}

void CBezier::Elevar_Grado()
{
	std::vector<Puntos> PuntosNuevo;
	float NumeroVertices = ControlPoints.size();
	float *bn = this->getVertex(ControlPoints.size() - 1);
	float *b0 = this->getVertex(0);
	this->setVertex(ControlPoints.size() - 1,bn[0], bn[1]); //the last
	this->setVertex(0, b0[0], b0[1]); //first vertex
	float *bjA, *bj;
	Puntos* aux = new Puntos();
	aux->setxy(b0[0], b0[1]);
	PuntosNuevo.push_back(*aux); //the point
	for (float j = 0; j < NumeroVertices - 1; j++)
	{
		bjA = this->getVertex(j);
		bj = this->getVertex(j + 1);
		Puntos* aux = new Puntos();
		aux->setxy((((j / NumeroVertices) * bjA[0]) + ((1 - (j / NumeroVertices)) * bj[0])), (((j / NumeroVertices) * bjA[1]) + (((1 - (j / NumeroVertices)) * bj[1]))));
		PuntosNuevo.push_back(*aux);
		this->setVertex(j,PuntosNuevo[j].getPointx(), PuntosNuevo[j].getPointy());
	}
	Puntos* last = new Puntos();
	last->setxy(bn[0], bn[1]);
	PuntosNuevo.push_back(*last);
	this->setVertex(PuntosNuevo.size() - 1, PuntosNuevo[PuntosNuevo.size() - 1].getPointx(), PuntosNuevo[PuntosNuevo.size() - 1].getPointy());
	std::cout << PuntosNuevo.size() - 2 << " " << PuntosNuevo[PuntosNuevo.size() - 2].getPointx() << " " << PuntosNuevo[PuntosNuevo.size() - 2].getPointy() << std::endl;
	//std::cout << PuntosNuevo.size() << std::endl;
	ControlPoints = PuntosNuevo;

}

void CBezier::drawLine(int x1, int y1, int x2, int y2)
{
	glColor3fv(lColor);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	//glFlush();
}

void CBezier::drawPixel(int x, int y) 
{
	glColor3fv(lColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

/*void CBezier::draw_rectangle(int x1, int x2, int y1, int y2) {
	int xmin = std::min(x1, x2); int xmax = std::max(x1, x2);
	int ymin = std::min(y1, y2); int ymax = std::max(y1, y2);
	for (int i = xmin; i <= xmax; i++) {
		drawPixel(i, ymin);
		drawPixel(i, ymax);
	}
	for (int i = ymin + 1; i <= ymax - 1; i++) {
		drawPixel(xmin, i);
		drawPixel(xmax, i);
	}
}*/

void  CBezier::draw_rectangle(int x1, int x2, int y1, int y2) {
	glColor3fv(bColor);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}



