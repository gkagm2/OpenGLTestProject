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
	
<<<<<<< HEAD
	glutCreateWindow("OpenGL Drawing Example");
	
	glutDisplayFunc(MyDisplay);

	glutMainLoop(); 
=======

	glutCreateWindow("OpenGL Drawing Example");		// ���ο� ������ ����
	glutDisplayFunc(MyDisplay);						// MyDisplay �Լ��� ���÷��� �̺�Ʈ�� ���� �ݹ� �Լ��� ���.
	glutMainLoop();									// ���������� ���� (�̺�Ʈ ������ ������ �ϱ� ����)
>>>>>>> 5b1235784c7f83bbca37eded0d31c89740aecec2
	return 0;
}