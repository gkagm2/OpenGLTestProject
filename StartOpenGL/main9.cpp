// Timer callback
#include <GL/glut.h>

GLfloat Delta = 0.0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	//TODO:: this
	glEnd();
	glutSwapBuffers();
}


void MyTime(int Value) {

}
void InitSetting(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char **argv) {
	InitSetting(argc, argv);
	
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}