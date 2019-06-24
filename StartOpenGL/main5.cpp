
#include <GL/glut.h>
#include <iostream>
using namespace std;
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

GLboolean IsSphere = true;

void MyDisplay() {
	glViewport(0, 0, 300, 300);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);

	glBegin(GL_POLYGON);
	glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
	cout <<"(1)"<< TopLeftX / 300.0 << ", " << (300 - TopLeftY) / 300.0 << endl;
	glVertex3f(TopLeftX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
	cout << "(2)" << TopLeftX / 300.0 << ", " << (300 - BottomRightY) / 300.0 << endl;
	glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
	cout << "(3)" << BottomRightX / 300.0 << ", " << (300 - BottomRightY) / 300.0 << endl;
	glVertex3f(BottomRightX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
	cout << "(4)" << BottomRightX / 300.0 << ", " << (300 - TopLeftY) / 300.0 << endl;
	glEnd();
	glFlush();

}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	cout << "mouse click" << endl;
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = X;
		TopLeftY = Y;
	}
}
void MyMouseMove(GLint X, GLint Y) {
	cout << "mouse move";
	BottomRightX = X;
	BottomRightY = Y;
	
	/*
	/// GLUT�� ��� ���� ����(Redisplay State Variable)���� �����Ѵ�.
	///GLUT�� �̺�Ʈ ������ �� �� �� ������ �� �������� ������ �� ���� ���� ���� Ȯ���غ��� ���� �����̸� ���÷��� �ݹ��� �ڵ����� �����Ѵ�.
	/// ���� �̺�Ʈ ������ �� �� �ݵ�� ���÷��� �Լ��� �ٽ� �����϶�� ��.
	*/
	glutPostRedisplay();

}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch(KeyPressed) {
	case 'Q':
	case 'q':
	case 27: // esc
		exit(0);
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1.0,0, 1.0, -1.0, 1.0);

	// display 
	glutDisplayFunc(MyDisplay); 

	// mouse 
	glutMouseFunc(MyMouseClick); // mouse click callback
	glutMotionFunc(MyMouseMove); // mouse move callback
	glutPassiveMotionFunc(MyMouseMove); // ���콺�� ������ ���� ���¿��� �����̴� ���콺 ��ǥ�� ���� �� ���

	// keyboard
	glutKeyboardFunc(MyKeyboard); // keyboard callback

	glutMainLoop();



	return 0;
}