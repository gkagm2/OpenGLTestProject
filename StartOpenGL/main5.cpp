
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
	/// GLUT의 재생 상태 변수(Redisplay State Variable)값을 세탕한다.
	///GLUT는 이벤트 루프가 한 번 돌 때마다 맨 마지막에 무조건 이 상태 변수 값을 확인해보고 세팅 상태이면 디스플레이 콜백을 자동으로 실행한다.
	/// 다음 이벤트 루프가 돌 때 반드시 디스플레이 함수를 다시 실행하라는 것.
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
	glutPassiveMotionFunc(MyMouseMove); // 마우스를 누르지 않은 상태에서 움직이는 마우스 좌표를 잡을 때 사용

	// keyboard
	glutKeyboardFunc(MyKeyboard); // keyboard callback

	glutMainLoop();



	return 0;
}