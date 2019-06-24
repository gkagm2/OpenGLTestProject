// idle callback and left right move
#include <GL/glut.h>

GLfloat Delta = 0.0;
GLfloat DeltaY = 0.0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);

	glColor3f(0.0, 0.5, 0.8);
	glVertex3f(-1.0 + Delta, -0.5 + DeltaY, 0.0);
	glVertex3f(0.0 + Delta, -0.5 + DeltaY, 0.0);
	glVertex3f(0.0 + Delta, 0.5 + DeltaY, 0.0);
	glVertex3f(-1.0 + Delta, 0.5 + DeltaY, 0.0);
	glEnd();
	glutSwapBuffers();
}

void MyIdle() {
	DeltaY = DeltaY + 0.001;
	glutPostRedisplay();
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	switch (KeyPressed) {
	case 'a':
	case 'A':
		Delta = Delta - 0.01;
		break;
	case 'd':
	case 'D':
		Delta = Delta + 0.01;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyIdle);

	glutKeyboardFunc(MyKeyboard);

	glutMainLoop();

	return 0;
}