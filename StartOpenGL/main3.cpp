#include <GL/glut.h>
//#include <GL/GLU.h>
//#include <GL/GL.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); // ���÷��� �ݹ� �Լ�
	glViewport(0, 0, 300, 300);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.0);

	glEnd();
	glFlush();
}

int main(int argc, char **argv) {

	// ������ �ʱ�ȭ
	glutInit(&argc, argv); // GLUT ������ �Լ�
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	
	// ������ ����
	glutCreateWindow("OpenGL Drawing Example");

	glClearColor(0.0, 0.0, 0.0, 1.0); // GL ���� ���� ����
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0 , 1.0, -1.0, 1.0); // ���翵 ����?
	glutDisplayFunc(MyDisplay);// �ݹ� �Լ� ���
	glutMainLoop(); //�̺�Ʈ ������ ����


	return 0;

	
}