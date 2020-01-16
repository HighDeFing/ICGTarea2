#pragma once

#include <AntTweakBar/AntTweakBar.h>
#include <iostream>
#include <string>
#include "Figure.h"
#include <vector>

using std::string;

//Singleton user interface class

class CEditInterface
{
private:
	static CEditInterface* mInterface; //Holds the instance of the class
	TwBar* mEditInterface;
	float mFigureColor[3], fFigureColor[3];
	float g_Rotation[4];
	bool bfill = false;
	bool bbox = true;
	bool bElevarGrado = false;
	bool GradoElevado = false;
	string smFigureType;
	FigureType figuretype = BEZIER;
	//TwEnumVal mFigureType_enumEV[6] = { {NONE, "NONE"}, {LINE, "LINE"}, {QUAD, "QUAD"}, {CIRCLE, "CIRCLE"}, {TRIANGLE, "TRIANGLE" }, {ELIPSE, "ELIPSE"} }; //iniit of all figures
	TwType mFigureType;
	float rotSpeed = 0;

public:
	///Method to obtain the only instance of the calls
	CFigure *figure;
	static CEditInterface* Instance();
	~CEditInterface();
	void reshape();
	void show();
	void hide();
	void setBox(bool);
	void setFigureColor(float* color);
	void setFigureType(FigureType type);
	void setFColor(float* color);
	float* getFigureColor();
	float* getFigureFColor();
	FigureType getFigureSelected();
	bool getBox();

private:
	///Private constructor
	CEditInterface();
};
