// 태양계 모델링
#include <GL/glut.h>
#include <iostream>
static int Day = 0, Time = 0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Ms : 태양, Me : 지구, Mm : 달
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16); // 태양을 그린다.

	glPushMatrix(); // 현재의 모델 좌표계, 즉 태양을 기준으로 한 좌표계 Ms를 스택에 푸시하여 저장.
	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0); // 현 모델 좌표계 Ms를 y축을 기준으로 각도 Day만큼 회전시킨다.
	glTranslatef(0.7, 0.0, 0.0); // 태양으로부터 0.7만큼 오른쪽으로 이동시켜 Me를 만드는 과정임.
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // 각도 Time만큼 회전시킨다.
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8); // 지구를 그린다.
	glPushMatrix(); // 지구의 모델 좌표계 Me를 저장한다.
	
	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // 현 지구의 모델 좌표계를 y축 기준으로 각도 TIme만큼 회전시킨다.
	glTranslatef(0.2, 0.0, 0.0); // 0.2만큼 이동 시킨다.
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8); // 여기에 달을 그려낸다.
	glPopMatrix();// 모델 좌표계는 Me로 복귀
	glPopMatrix();// 모델 좌표계는 Ms로 복귀
	glutSwapBuffers();

}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day = (Day + 10) % 360;
		std::cout << "Day : " << Day << std::endl;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		std::cout << "Time : " << Time << std::endl;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();



	return 0;
}