#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>



void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);

	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5,-0.5, 0.0);
	glVertex3f(0.5,0.5,0.0);
	glVertex3f(0.0,0.8,0.0);
	glVertex3f(0.5,0.5,0.0);

	glEnd();
	glFlush();
}



int main() {
	

	glutCreateWindow("OpenGL Drawing Example");		// ���ο� ������ ����
	glutDisplayFunc(MyDisplay);						// MyDisplay �Լ��� ���÷��� �̺�Ʈ�� ���� �ݹ� �Լ��� ���.
	glutMainLoop();									// ���������� ���� (�̺�Ʈ ������ ������ �ϱ� ����)
	return 0;
}