#include <GL/glut.h>
//#include <GL/GLU.h>
//#include <GL/GL.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); // 디스플레이 콜백 함수
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

	// 윈도우 초기화
	glutInit(&argc, argv); // GLUT 윈도우 함수
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	
	// 윈도우 생성
	glutCreateWindow("OpenGL Drawing Example");

	glClearColor(0.0, 0.0, 0.0, 1.0); // GL 상태 변수 설정
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0 , 1.0, -1.0, 1.0); // 정사영 세팅?
	glutDisplayFunc(MyDisplay);// 콜백 함수 등록
	glutMainLoop(); //이벤트 루프로 진입


	return 0;

	
}