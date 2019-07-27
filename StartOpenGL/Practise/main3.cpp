// 리셰이프 콜백

#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	//컬러 버퍼에 초기화 색을 가함
	glColor3f(0.5, 0.5, 0.5);		//회색

	glBegin(GL_POLYGON);			//사각형

	glVertex3f(-0.5, -0.5, 0.0);	//좌하단 좌표
	glVertex3f(0.5, -0.5, 0.0);		//우하단 좌표
	glVertex3f(0.5, 0.5, 0.0);		//우상단 좌표
	glVertex3f(-0.5, 0.5, 0.0);		//좌상단 좌표
	glEnd();
	glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)300;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0* HeightFactor, -1.0, 1.0);
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
