// ���÷��� ����Ʈ (GL ���� ���(Retained Mode))

#include <GL/glut.h>

int MyListID;
void MyCreateList() {
	MyListID = glGenLists(1); // ��� �� �� �Ϸ��� ���̵� ���� �˻��ϱ� ���� ��. ���ϴ� ���̵��� ������ �Ķ���ͷ� ����. 

	// ������ ����Ʈ�� ����� ������ ä��� ���� ��. (������ ����Ʈ�� ���̵�, ��ɾ� ���� ���)
	// GL_COMPILE : ������� �ʰ� ���÷��� ����Ʈ���� ����. GL_COMPILE_AND_EXECUTE : ���� ���ó�� ��ɾ ��� ����ʰ� ���ÿ� ���÷��� ����Ʈ���� ���� ��.
	glNewList(MyListID, GL_COMPILE); 

	glBegin(GL_POLYGON);

	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);

	glEnd();
	glEndList();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 300, 300);
	glCallList(MyListID);
	glFlush();
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Example Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0); // white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);

	MyCreateList(); // ���÷��� ����Ʈ�� �����ϱ� ���� ��.

	glutMainLoop();
	return 0;
}