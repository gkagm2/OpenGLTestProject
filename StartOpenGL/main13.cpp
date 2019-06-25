// Modeling
#include <GL/glut.h>
#include <iostream>

// flatshading과 wireframe을 토글링하기 위한 부울 변수
int FlatShaded = 0;
int Wireframed = 0;

// 마우스 움직임에 따라 시점을 바꾸기 위한 변수
int ViewX = 0, ViewY = 0;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 3.0 }; 
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ViewX, ViewY, 0.5, 0.5, 0.5, -1.0, 1.0, 1.0, 0.0);
	
	if (Wireframed) {
		glutWireTeapot(0.2); // example
	}
	else {
		glutSolidTeapot(0.2); // example
	}
	glFlush();
}
void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033': //  same 27 (esc)
	//case 27:
		exit(1);
		break;
	case 's':
		if (FlatShaded) {
			FlatShaded = 0;
			glShadeModel(GL_SMOOTH);
		}
		else {
			FlatShaded = 1;
			glShadeModel(GL_FLAT);
		}
		glutPostRedisplay();
		break;
	case 'w':
		if (Wireframed) {
			Wireframed = 0;
		}
		else {
			Wireframed = 1;
		}
		break;
	}
	glutPostRedisplay();
}
void MyMouseMove(GLint button, GLint state, GLint x, GLint y) {
	// TODO: 수정 해야 함.
	// 마우스 움직임X, Y를 전역 변수인 ViewX, ViewY에 할당
	ViewX = x;
	std::cout << "ViewX : " << ViewX/1000.0 << std::endl;
	ViewY = y;
	std::cout << "ViewY : " << ViewY/1000.0 << std::endl;
	
	glutPostRedisplay();
}
void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_POLYGON);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	return 0;
}