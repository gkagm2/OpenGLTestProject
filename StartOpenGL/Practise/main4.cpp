// Ű���� �ݹ�
#include <GL/glut.h>
#include <iostream>
#define GAME_ESCAPE 27
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	//�÷� ���ۿ� �ʱ�ȭ ���� ����
	glColor3f(0.5, 0.5, 0.5);		//ȸ��

	glBegin(GL_POLYGON);			//�簢��

	glVertex3f(-0.5, -0.5, 0.0);	//���ϴ� ��ǥ
	glVertex3f(0.5, -0.5, 0.0);		//���ϴ� ��ǥ
	glVertex3f(0.5, 0.5, 0.0);		//���� ��ǥ
	glVertex3f(-0.5, 0.5, 0.0);		//�»�� ��ǥ
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

	glClearColor(1.0, 1.0, 1.0,1.0); //  �ʱ�ȭ ���� ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MyKeyboard2); // ����Ű, �Լ� Ű �� Ư�� Ű�� ���� �ݹ��Լ� �� ����.
	glutMainLoop();

	return 0;
}

