// �¾�� �𵨸�
#include <GL/glut.h>
#include <iostream>
static int Day = 0, Time = 0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Ms : �¾�, Me : ����, Mm : ��
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16); // �¾��� �׸���.

	glPushMatrix(); // ������ �� ��ǥ��, �� �¾��� �������� �� ��ǥ�� Ms�� ���ÿ� Ǫ���Ͽ� ����.
	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0); // �� �� ��ǥ�� Ms�� y���� �������� ���� Day��ŭ ȸ����Ų��.
	glTranslatef(0.7, 0.0, 0.0); // �¾����κ��� 0.7��ŭ ���������� �̵����� Me�� ����� ������.
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // ���� Time��ŭ ȸ����Ų��.
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8); // ������ �׸���.
	glPushMatrix(); // ������ �� ��ǥ�� Me�� �����Ѵ�.
	
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // �� ������ �� ��ǥ�踦 y�� �������� ���� TIme��ŭ ȸ����Ų��.
	glTranslatef(0.2, 0.0, 0.0); // 0.2��ŭ �̵� ��Ų��.
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8); // ���⿡ ���� �׷�����.
	glPopMatrix();// �� ��ǥ��� Me�� ����
	glPopMatrix();// �� ��ǥ��� Ms�� ����
	glutSwapBuffers();

}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day = (Day + 10) % 360;
		std::cout << "Day : " << Day << std::endl;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		std::cout << "Time : " << Time << std::endl;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();



	return 0;
}