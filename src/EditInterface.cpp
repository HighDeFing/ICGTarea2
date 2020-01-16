#include "EditInterface.h"
#include "Figure.h"
#include "Quad.h"
#include "Bezier.h"

extern int gWidth, gHeight;
extern void TW_CALL e_ElevarGrado(void* );
// Global static pointer used to ensure a single instance of the class.
CEditInterface* CEditInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CEditInterface* CEditInterface::Instance()
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		mInterface = new CEditInterface();

	return mInterface;
}


CEditInterface::CEditInterface()
{
	mEditInterface = TwNewBar("Edit");

	TwDefine("Edit refresh = '0.0001f'");
	TwDefine("Edit resizable = true");
	TwDefine("Edit fontresizable = false");
	TwDefine("Edit movable = true");
	TwDefine("Edit visible = false");
	TwDefine("Edit position = '20 330'");
	TwDefine("Edit size = '220 260'");



	//mFigureType = TwDefineEnum("mFigureType", mFigureType_enumEV, 6);

	//TwAddVarRO(mEditInterface, "Figure", mFigureType, &figuretype, "label='Type'");

	TwAddVarRO(mEditInterface, "meshType", TW_TYPE_STDSTRING, &mFigureType, "label='Type' readonly=true");
	TwAddVarRW(mEditInterface, "color", TW_TYPE_COLOR3F, &mFigureColor[0], "label = 'Color'");
	TwAddVarRW(mEditInterface, "Line colors", TW_TYPE_COLOR3F, &fFigureColor[0], "label = 'Line Color'");
	//TwAddVarRW(mEditInterface, "Fill color", TW_TYPE_COLOR3F, &fFigureColor[0], "label = 'Fill color'");
	//TwAddVarRW(mEditInterface, "relleno", TW_TYPE_BOOLCPP, &bfill, "label = 'Fill?'");
	TwAddVarRW(mEditInterface, "bounding box", TW_TYPE_BOOLCPP, &bbox, "label = 'Bounding box?'");
	TwAddButton(mEditInterface, "Subir Grado", e_ElevarGrado, NULL, " label='Subir Grado' ");
	
}


CEditInterface::~CEditInterface()
{
}

void CEditInterface::setBox(bool x) {
	bbox = x;
}

void CEditInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}


bool CEditInterface::getBox()
{
	return bbox;
}

void CEditInterface::show()
{
	TwDefine("Edit visible = true");
}

void CEditInterface::hide()
{
	TwDefine("Edit visible = false");
}

void CEditInterface::setFigureColor(float* color)
{
	mFigureColor[0] = color[0];
	mFigureColor[1] = color[1];
	mFigureColor[2] = color[2];
}

void CEditInterface::setFigureType(FigureType type)
{
	figuretype = type;
}

float* CEditInterface::getFigureColor()
{
	return mFigureColor;
}


float* CEditInterface::getFigureFColor()
{
	return fFigureColor;
}

FigureType CEditInterface::getFigureSelected()
{
	return figuretype;
}

void CEditInterface::setFColor(float* color)
{
	fFigureColor[0] = color[0];
	fFigureColor[1] = color[1];
	fFigureColor[2] = color[2];
}

