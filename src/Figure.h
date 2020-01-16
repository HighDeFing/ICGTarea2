#pragma once

#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <algorithm>

enum FigureType
{
	NONE,
	BEZIER
};

class CFigure
{
protected:
	float **mVertices, mColor[3], dColor[3], lColor[3], bColor[3], dsColor[3];
	int mType;
	int clicks;
	bool bbox = false;
	bool bFirst = true;

public:
	class Puntos {
	public:
		float x, y;
		bool selected = false;
		void setxy(float x2, float y2) { x = x2; y = y2; }
		const Puntos& operator=(const Puntos& rPoint) {
			x = rPoint.x;
			y = rPoint.y;
			return *this;
		}
		float getPointx() {
			return x;
		}
		float getPointy() {
			return y;
		}
		bool getSelected() {
			return selected;
		}

	};
	std::vector<Puntos> ControlPoints; //Puntos de control es global
	CFigure();
	virtual ~CFigure();
	float maxf[2], minf[2];
	void setbFirst(bool);
	bool getbFirst();
	void setdColor(float r, float g, float b);
	void setdsColor(float r, float g, float b);
	float* getdsColor();
	void setlColor(float r, float g, float b);
	float* getlColor();
	void setbColor(float r, float g, float b);
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setClicks(int);
	virtual void ColorVertex(int id, bool x) = 0;
	void Figuresetbox(bool x);
	std::vector<Puntos> getControlPPoints();
	virtual void boundingbox() = 0;
	virtual void display() = 0;
	virtual void Elevar_Grado() = 0;
	int getType();
	int getClicks();
	float* getVertex(int id);
	float* getColor();
	virtual void deleteVertex(int id) = 0;
};