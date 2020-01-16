#include "Figure.h"

CFigure::CFigure()
{
	mColor[0] =  1.0f;
	mColor[1] = mColor[2] = 0.f;
}

CFigure::~CFigure()
{
	delete[] mVertices;
}

void CFigure::setbFirst(bool x)
{
	bFirst = x;
}

bool CFigure::getbFirst()
{
	return bFirst;
}

void CFigure::setVertex(int id, float x, float y)
{
	mVertices[id][0] = x;
	mVertices[id][1] = y;
}

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

void CFigure::setdColor(float r, float g, float b)
{
	dColor[0] = r;
	dColor[1] = g;
	dColor[2] = b;
}

void CFigure::setdsColor(float r, float g, float b)
{
	dsColor[0] = r;
	dsColor[1] = g;
	dsColor[2] = b;
}

float* CFigure::getdsColor()
{
	return dsColor;
}

void CFigure::setlColor(float r, float g, float b)
{
	lColor[0] = r;
	lColor[1] = g;
	lColor[2] = b;
}

float* CFigure::getlColor()
{
	return lColor;
}

void CFigure::setClicks(int c)
{
	clicks = c;
}

int CFigure::getClicks()
{
	return clicks;
}

int CFigure::getType()
{
	return mType;
}

float* CFigure::getVertex(int id)
{
	return mVertices[id];
}

float* CFigure::getColor()
{
	return mColor;
}

void CFigure::Figuresetbox(bool x) {
	bbox = x;
}



void  CFigure::setbColor(float r, float g, float b)
{
	bColor[0] = r;
	bColor[1] = g;
	bColor[2] = b;
}

std::vector<CFigure::Puntos> CFigure::getControlPPoints() {
	return ControlPoints;
}
