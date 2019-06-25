// 디스플레이 리스트 (GL 보류 모드(Retained Mode))

#include <GL/glut.h>

int MyListID;
void MyCreateList() {
	MyListID = glGenLists(1); // 사용 안 된 일련의 아이디 값을 검색하기 위한 것. 원하는 아이디의 개수를 파라미터로 받음. 

	// 실제로 리스트를 만들고 내용을 채우기 위한 것. (생성될 리스트의 아이디, 명령어 실행 모드)
	// GL_COMPILE : 실행되지 않고 디스플레이 리스트에만 저장. GL_COMPILE_AND_EXECUTE : 직접 모드처럼 명령어가 즉시 실행됨과 동시에 디스플레이 리스트에도 저장 됨.
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

	MyCreateList(); // 디스플레이 리스트를 생성하기 위한 것.

	glutMainLoop();
	return 0;
}