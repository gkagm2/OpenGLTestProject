//
// DATE : 20190719 ~
// DEV : Framework
//
#pragma warning(disable:4996)

#define DEFINE_STDIO_H 1
#ifdef DEFINE_IOSTREAM
#include <iostream>
#elif DEFINE_STDIO_H
#include <stdio.h>
#endif // DEFINE_IcOSTREAM

#include <stdlib.h>
#include "GL/glut.h"

namespace SagacityEngine {
	class GLController {
	private:
		int width;
		int height;
	public:
		GLfloat x, y, z;
		GLfloat screenX, screenY;
		

		GLController(const GLfloat x = 0, const GLfloat y = 0, const GLfloat z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;

			width = 0;
			height = 0;
		}



		void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
		void GLInit();
		void ShowScreen();
		void SetWindowSize(int width, int height);
		int GetWidth();
		int GetHeight();
		void MakeCube();
		void MakeRect();
		void MakePanel(const float x, const float y, const float width, const float heigth);

		void CallError(const char *message);
		void Debug(const char *message);
		void ChangeNormalizationToScreenCoordinate(float x, float y, float width, float heigth);
		
	};


	//// FUNCTION

	void GLController::CallError(const char *message) {
#ifdef DEFINE_IOSTREAM
		std::cout << "error !" << message << std::endl;
#elif DEFINE_STDIO_H
		printf(" error 1! %s\n", message);
#endif	
	}
	void GLController::Debug(const char *message) {
#ifdef DEFINE_IOSTREAM
		std::cout << "Debug : "<< message << std::endl;
#elif DEFINE_STDIO_H
		printf("Debug : %s\n", message);
#endif	
	}
	

	void GLController::MakePanel(const float x, const float y, const float width, const float height) {
		// TODO : rgb 배열의 index가 늘거나 줄면 큰일남. 예외처리 해야 함
		
		printf("%f %f %f %f \n", x, y, width, height);

		glViewport(GetWidth() / 2, 0, GetWidth() / 2, GetHeight());

		glBegin(GL_POLYGON);
		
		// make panel
		glVertex3f(x, y, 0);
		glVertex3f(x + width, y, 0);
		glVertex3f(x + width, y + height, 0);
		glVertex3f(x, y + height, 0);
		glEnd();
	}


	void GLController::SetPosition(const GLfloat x, const GLfloat y, const GLfloat z) {

	}
	void GLController::GLInit() {

	}

	void GLController::ShowScreen() {

	}
	void GLController::SetWindowSize(int width, int height) {
		this->width = width;
		this->height = height;
	}

	int GLController::GetWidth() {
		return width;
	}
	int GLController::GetHeight() {
		return height;
	}

	void GLController::MakeCube() {
		glutSolidCube(5.0);
	}
	void GLController::MakeRect() {
		glBegin(GL_POLYGON);
		glVertex3f(-.5, -.5, 0);
		glVertex3f(.5, -.5, 0);
		glVertex3f(.5, .5, 0);
		glVertex3f(-.5, .5, 0);
		glEnd();
	}

	void GLController::ChangeNormalizationToScreenCoordinate(float x, float y, float width, float height) {

		// change normalization coordinate to screen coordinate 
		screenX = width * (0.5 - (-1.0)) / 2.0;
		screenY = height * (0.5 - (-1.0)) / -2.0;
	}
	
}


using namespace SagacityEngine;
GLController controller;


// view screen
void ViewScreen() {
	glColor3f(0.2, 0.2, 0.2);
	//
	glViewport(0, 0, controller.GetWidth()/2, controller.GetHeight()/2);
	printf("widht :  %d, height : %d\n", controller.GetWidth(), controller.GetHeight()/2);
	//

	controller.MakeRect();

	printf("Display 호출\n");
}

// project panel
void ProjectScreen() {

	glColor3f(0.1, 1.0, 0.1);
	glViewport(controller.GetWidth() / 2, 0, controller.GetWidth() / 2, controller.GetHeight());
	controller.MakePanel(controller.GetWidth() / 2, 0, controller.GetWidth() / 2, controller.GetHeight()/2);
	controller.MakeRect();
	printf("ProjectPanel 호출\n");
}




//////////////////////////////////////////////////////////////////////////


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	ViewScreen(); // 3d view screen
	ProjectScreen(); // project Screen
	glFlush();
}

void MyKeyboard(unsigned char key, GLint x, GLint y) {

}

void MyMouse(GLint button, GLint state, GLint x, GLint y) {

}


void MyIdle() {
}

void MyReshape(int width, int height) {
	printf("width : %d, height : %d\n", width, height);
	controller.SetWindowSize(width, height);
}

int main() {


	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game"); // 새로운 윈도우 생성
	controller.GLInit();
	glClearColor(0.5, 0.5, 0.5, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouse);
	glutIdleFunc(MyIdle);
	glutReshapeFunc(MyReshape);
	//

	glutMainLoop();
	
	return 0;
}
