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
#endif // DEFINE_IOSTREAM

#include <stdlib.h>
#include "GL/glut.h"

namespace SagacityEngine {
	class GLController {
	public:
		GLfloat x, y, z;
		GLController(const GLfloat x = 0, const GLfloat y = 0, const GLfloat z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;
		}


		void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
		void Debug_Log();
		void GLInit();
	};

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
	
}



using namespace SagacityEngine;
GLController controller;





//////////////////////////////////////////////////////////////////////////


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	  
		glVertex3f(controller.x, -.3, .0);
		glVertex3f(.3, -.3, .0);
		glVertex3f(.3, .3, .0);
		glVertex3f(-.3, .3, .0);

		glVertex3d(3, 5, 0);
		glVertex3d(5, 5, 0);
		glVertex3d(5, 3, 0);
	
	
	glEnd();
	
	glFlush();
}

void MyKeyboard(unsigned char key, GLint x, GLint y) {

}

void MyMouse(GLint button, GLint state, GLint x, GLint y) {

}


void MyIdle() {

}

void MyReshape(int width, int height) {

}

int main() {


	controller.Debug_Log();
	glutCreateWindow("Game"); // 货肺款 扩档快 积己
	controller.GLInit();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouse);
	glutIdleFunc(MyIdle);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	
	return 0;
}