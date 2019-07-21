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
		GLController(const GLfloat x = 0, const GLfloat y = 0, const GLfloat z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;

			width = 0;
			height = 0;
		}



		void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
		void Debug_Log();
		void GLInit();
		void ShowScreen();
		void SetWindowSize(int width, int height);
		int GetWidth();
		int GetHeight();
		void MakeCube();
		void MakeRect();
	};

	//// FUNCTION
	void GLController::Debug_Log() {
#ifdef DEFINE_STDIO_H
		printf("error!");
#elif DEFINE_IOSTREAM
		std::cout << "error!";
#endif
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
	
}



using namespace SagacityEngine;
GLController controller;





//////////////////////////////////////////////////////////////////////////


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//
	glViewport(0, 0, controller.GetWidth(), controller.GetHeight());
	printf("widht :  %d, height : %d\n", controller.GetWidth(), controller.GetHeight());
	//

	controller.MakeRect();

	printf("Display 龋免\n");
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


	controller.Debug_Log();
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game"); // 货肺款 扩档快 积己
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
