#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "UserInterface.h"
#include "Bezier.h"

using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress, gbezier, gbezier2;
CUserInterface * userInterface;
vector <CFigure *> figures;
FigureType figureSelected;
int picked;
bool first = true; bool second = false; bool third = false; bool newb = true; bool fourth = false; bool fifth = false; bool sexth = false;
vector <bool *> clicking;
int click = 0;

void pick(int x, int y)
{
	picked = -1;
	userInterface->hide();

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		float *v1 = figures[i]->getVertex(0);
		float *v2 = figures[i]->getVertex(1);
		float max[2];
		float min[2];

		// This should be precalculated

		max[0] = MAX(v1[0], v2[0]);
		max[1] = MAX(v1[1], v2[1]);

		min[0] = MIN(v1[0], v2[0]);
		min[1] = MIN(v1[1], v2[1]);

		if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
		{
			picked = i;

			userInterface->setFigureColor(figures[picked]->getColor());
			userInterface->show();

			int type = figures[picked]->getType();

			if (type == LINE)
				userInterface->setFigureType("Line");
			else
				userInterface->setFigureType("Quad");

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
	glPointSize(3);
	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_P:
			figureSelected = NONE;
			userInterface->hide();
			break;

		case GLFW_KEY_B:
			first = true; second = false; third = false; newb = true;
			figureSelected = BEZIER;
			click = 0;
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			userInterface->hide();
			break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && first) {
			float ax = float(x);
				float ay = gHeight - float(y);
				CBezier* bezier = new CBezier();
				bezier->setColor(1.0, 0, 0);
				bezier->setdColor(0.4157, 0.051, 0.6784);
				bezier->setlColor(0.0, 0.0, 1.0);
				bezier->setVertex(0, ax, ay);
				//bezier->setVertex(1, ax, ay);
				figures.push_back(bezier);
				//gPress = true;
				click = 0;
				first = false;
				second = true;
		}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && second) {
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

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}