#pragma once

#include <GLFW/glfw3.h>

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	BEZIER
};

class CFigure
{
protected:
	float **mVertices, mColor[3], dColor[3], lColor[3];
	int mType;
	int clicks;

public:
	CFigure();
	virtual ~CFigure();
	void setdColor(float r, float g, float b);
	void setlColor(float r, float g, float b);
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setClicks(int);
	virtual void display() = 0;
	int getType();
	int getClicks();
	float* getVertex(int id);
	float* getColor();
};