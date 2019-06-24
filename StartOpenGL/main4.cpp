// 키보드 콜백
#include <GL/glut.h>
#include <iostream>
#define GAME_ESCAPE 27
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	//컬러 버퍼에 초기화 색을 가함
	glColor3f(0.5, 0.5, 0.5);		//회색

	glBegin(GL_POLYGON);			//사각형

	glVertex3f(-0.5, -0.5, 0.0);	//좌하단 좌표
	glVertex3f(0.5, -0.5, 0.0);		//우하단 좌표
	glVertex3f(0.5, 0.5, 0.0);		//우상단 좌표
	glVertex3f(-0.5, 0.5, 0.0);		//좌상단 좌표
	glEnd();
	glFlush();
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	std::cout << "MyKeyboard KeyPressed : " << KeyPressed << std::endl;
	std::cout << "X : " << X << " Y : " << Y << std::endl;

	switch (KeyPressed) {
	case 'Q':
	case 'q':
	case GAME_ESCAPE: // 'esc' key
		exit(0);
		break;
	}
}

void MyKeyboard2(int keyPressed, int x, int y) {
	std::cout << "MyKeyboard2 pressed : " << keyPressed << std::endl;
	std::cout << "x : " << x << "y : " << y << std::endl;

}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");

	glClearColor(1.0, 1.0, 1.0,1.0); //  초기화 색은 백색
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MyKeyboard2); // 방향키, 함수 키 등 특수 키에 대한 콜백함수 떄 사용됨.
	glutMainLoop();

	return 0;
}

