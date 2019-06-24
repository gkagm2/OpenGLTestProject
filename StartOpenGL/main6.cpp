// menu callback
#include <GL/glut.h>
#include <iostream>
GLboolean IsSphere = true;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.0, 0.5);

	if (IsSphere) {
		glutWireSphere(0.2, 20, 20);
	}
	else {
		glutWireTorus(0.2, 0.3, 40, 20);
	}
	glFlush();
}


void MyMainMenu(int entryID) {
	if (entryID == 1)
		IsSphere = true;
	else if (entryID == 2)
		IsSphere = false;
	else if (entryID == 3)
		exit(1);
	glutPostRedisplay();
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Example Drawing");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // ���ο� �޴��� �����.
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ������ ���콺 ��ư�� ���� �� �� �޴����˾� ��.

	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}