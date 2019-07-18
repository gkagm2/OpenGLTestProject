//
// DATE : 20190719 ~
// DEV : Framework
//

#define DEFINE_STDIO_H 1
#ifdef DEFINE_IOSTREAM
#include <iostream>
#elif DEFINE_STDIO_H
#include <stdio.h>
#endif // DEFINE_IOSTREAM

#include "GL/glut.h"


class GLController{
public:
	GLfloat x, y, z;
	GLController(const GLfloat x = 0, const GLfloat y = 0, const GLfloat z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
	void Debug_Log();
};

void GLController::Debug_Log() {
#ifdef DEFINE_STDIO_H
	printf("error!");
#elif DEFINE_IOSTREAM
	std::cout << "error!";
#endif
}

void GLController::SetPosition(const GLfloat x , const GLfloat y, const GLfloat z) {

}





//////////////////////////////////////////////////////////////////////////


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(-.3, -.3, .0);
	glVertex3f(.3, -.3, .0);
	glVertex3f(.3, .3, .0);
	glVertex3f(-.3, .3, .0);

	glVertex3d(3, 5,0);
	glVertex3d(5, 5,0);
	glVertex3d(5, 3,0);
	glEnd();
	glFlush();
}



int main() {
	GLController controller;
	controller.Debug_Log();
	glutCreateWindow("Game");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}