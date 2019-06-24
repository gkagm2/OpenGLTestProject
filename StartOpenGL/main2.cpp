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

	glutCreateWindow("OpenGL Drawing Example");		// 새로운 윈도우 생성
	glutDisplayFunc(MyDisplay);						// MyDisplay 함수를 디스플레이 이벤트에 대한 콜백 함수로 등록.
	glutMainLoop();									// 마지막으로 돌림 (이벤트 루프를 돌려야 하기 때문)
>>>>>>> 5b1235784c7f83bbca37eded0d31c89740aecec2
	return 0;
}