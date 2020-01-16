#pragma once

#include <AntTweakBar/AntTweakBar.h>
#include <iostream>
#include <string>
#include "Figure.h"

using std::string;

//Singleton user interface class

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	float mFigureColor[3];
	float g_Rotation[4];
	FigureType figuretype = BEZIER;
	TwEnumVal mFigureType_enumEV[2] = { {NONE, "NONE"}, {BEZIER, "BEZIER"} }; //iniit of all figures
	TwType mFigureType;


public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setFigureColor(float *color);
	void setFigureType(FigureType type);
	float* getFigureColor();
	FigureType getFigureType();

private:
	///Private constructor
	CUserInterface(); 
};