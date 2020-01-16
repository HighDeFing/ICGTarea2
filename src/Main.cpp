#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "UserInterface.h"
#include "Bezier.h"
#include "Figure.h"
#include "EditInterface.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool ispicked;
bool gPress, gbezier, gbezier2;
CUserInterface * userInterface;
CEditInterface * editInterface;
vector <CFigure *> figures;
FigureType figureSelected;

int picked;
int pickedver;
bool first = true; bool second = false; bool third = false; bool newb = true; bool fourth = false; bool fifth = false; bool sexth = false;
vector <bool *> clicking;
int click = 0;

void pick(int x, int y)
{
	picked = -1;
	pickedver = -1;

	ispicked = false;
	//userInterface->hide();
	editInterface->show();
	editInterface->setBox(false);
	float *ver;

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		figures[i]->Figuresetbox(false);
		float max[2], min[2]; //max[0]=x max[1]=y min[0]=x min[1]=y
		max[0] = figures[i]->maxf[0];
		max[1] = figures[i]->maxf[1];
		min[0] = figures[i]->minf[0];
		min[1] = figures[i]->minf[1];
		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			
			picked = i;
			ispicked = true;
			userInterface->setFigureColor(figures[picked]->getColor());
			userInterface->show();
			int type = figures[picked]->getType();
			editInterface->setBox(true);
			figures[picked]->Figuresetbox(true);
			figures[picked]->setbFirst(false);
			for (unsigned int i = 0; i < figures[picked]->ControlPoints.size(); i++)
			{
				ver = figures[picked]->getVertex(i);
				figures[picked]->ColorVertex(i, false);
				if (x >= ver[0] - 5 && x<=ver[0]+5 && y >= ver[1] - 5 && y<=ver[1] + 5)
				{
					pickedver = i;
					figures[picked]->ColorVertex(i, true);
				}
			}
			break;
		}
	}
}

void updateUserInterface()
{
	if (picked > -1)
	{
		float * color = userInterface->getFigureColor();
		figures[picked]->setColor(color[0], color[1], color[2]);
	}
}

void updateEditInterface() {
	if (picked > -1 && ispicked)
	{
		editInterface->show();  //Show edit interface when clicked
		/*float* ecolor = editInterface->getFigureColor();
		figures[picked]->setColor(ecolor[0], ecolor[1], ecolor[2]); //line color

		float* fcolor = editInterface->getFigureFColor();
		figures[picked]->setfColor(fcolor[0], fcolor[1], fcolor[2]); //fill color
		*/

		//editInterface->setFill(figures[picked]->getbfill()); //set if fill don't know why it works but it works lmao.
		figures[picked]->Figuresetbox(editInterface->getBox()); //set if bounding box

	}
	else if (!ispicked && picked < -1) {
		editInterface->hide(); //hide edit interface when not cliking on a figure
		editInterface->setFigureType(NONE);
	}
	if (picked > -1) {
		float* ecolor = editInterface->getFigureColor();
		figures[picked]->setColor(ecolor[0], ecolor[1], ecolor[2]); //line color

		float* fcolor = editInterface->getFigureFColor();
		figures[picked]->setlColor(fcolor[0], fcolor[1], fcolor[2]); //fill color

		//figures[picked]->Figuresetfill(editInterface->getFill()); //set if fill but only on one figure properties.

		figures[picked]->Figuresetbox(editInterface->getBox()); //set if bounding box
	}
	else {
		editInterface->hide(); //hide edit interface when not cliking on a figure
		editInterface->setFigureType(NONE);
	}

}

void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);
	glPointSize(5);
	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;
	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);
	float ax = float(x);
	float ay = gHeight - float(y);
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			first = false; second = false; third = false; newb = true;
			pick(int(ax), int(ay));
			figureSelected = NONE;
			break;

		case GLFW_KEY_B:
			first = true; second = false; third = false; newb = true;
			figureSelected = BEZIER;
			click = 0;
			break;
		case GLFW_KEY_DELETE:
			if (picked > -1) {
				if (pickedver > -1) {
					figures[picked]->deleteVertex(pickedver);
				}
			}
		}
	}
}

void TW_CALL e_ElevarGrado(void* /*clientData*/)
{
	if (picked > -1) {
		figures[picked]->Elevar_Grado();
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);


		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && figureSelected == NONE) {
			float ax = float(x);
			float ay = gHeight - float(y);
			first = false; second = false; third = false; newb = true;
			userInterface->setFigureType(NONE);
			figureSelected = NONE;
			pick(int(ax), int(ay));
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && first && figureSelected == BEZIER) {
			float ax = float(x);
			float ay = gHeight - float(y);
			CBezier* bezier = new CBezier();
			bezier->setColor(1.0, 0, 0);
			bezier->setdColor(0.4157, 0.051, 0.6784);
			bezier->setdsColor(0.61, 0.53, 0.05);
			bezier->setlColor(0.0, 0.0, 1.0);
			bezier->setbColor(0, 255, 255);
			bezier->setVertex(0, ax, ay);
			bezier->setVertex(1, ax, ay);
			figures.push_back(bezier);
			userInterface->setFigureType(BEZIER);
			editInterface->setFigureColor(bezier->getColor());
			editInterface->setFColor(bezier->getlColor());
			//gPress = true;
			click = 0;
			first = false;
			second = true;
		}
		else figureSelected = userInterface->getFigureType();

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && second && figureSelected == BEZIER) {
		//std::cout << "click:"<< click;
		float ax = float(x);
		float ay = gHeight - float(y);
		click++;
		figures.back()->setClicks(click);
		figures.back()->setVertex(click, ax, ay);
	}
	/*
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		if (figureSelected == NONE)
			pick(int(ax), int(ay));
		if (gbezier) {
			figures.back()->setVertex(2, ax, ay);
			gbezier2 = true;
			gbezier = false;
			}else if (figureSelected == BEZIER)
			{

			CBezier *bezier = new CBezier();
			bezier->setColor(1.0, 0, 0);
			bezier->setVertex(0, ax, ay);
			bezier->setVertex(1, ax, ay);
			bezier->setVertex(2, ax, ay);
			bezier->setVertex(3, ax, ay);
			figures.push_back(bezier);
			gbezier = true;
			gPress = true;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			if (gbezier2) {
				float ax = float(x);
				float ay = gHeight - float(y);
				figures.back()->setVertex(3, ax, ay);
				gbezier2 = false;
			}
		gPress = false;
		}*/
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;

	/*if (gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);
		if(first)
		figures.back()->setVertex(1, ax, ay);
		if (second) {
			figures.back()->setVertex(2, ax, ay);
		}
		/*if (third) {
			figures.back()->setVertex(3, ax, ay);
		}
		
	}*/
	
	
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "ICG - Plantilla", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	editInterface = CEditInterface::Instance();
	userInterface = CUserInterface::Instance();
	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	figureSelected = BEZIER;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		
		TwDraw();

		updateUserInterface();
		updateEditInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}