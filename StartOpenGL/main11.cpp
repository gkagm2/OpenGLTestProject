// Vertex Array

// Cube Shape
//    5----6
//  1/---2/|
//  | |  | |
//  | 4--|-7
//  0/---3/
#include <GL/glut.h>

// 육면체 정점의 좌표
GLfloat MyVertices[8][3] = {
	{-0.25, -0.25,0.25},
	{-0.25,0.25,0.25},
	{0.25,0.25,0.25},
	{0.25,-0.25,0.25},
	{-0.25,-0.25,-0.25},
	{-0.25,0.25,-0.25},
	{0.25,0.25,-0.25},
	{0.25,-0.25,-0.25},
};

// 정점의 색
GLfloat MyColor[8][3] = {
	{0.2,0.2,0.2},
	{1.0,0.0,0.0},
	{1.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,1.0,1.0},
	{0.0,1.0,1.0}
};

// 여섯 개의 면이 각각 어떤 정점들에 의해 이루어지는지 
GLbyte MyVertexList[24] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };


GLfloat Angle = 0.0;
GLfloat X = 1.0;
GLfloat Y = 0.0;
GLfloat Z = 0.0; // 바라보는쪽( 투사면 쪽)이 Z축+ 방향 임

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW); // counter-clockwise 표면을 반시계 방향으로 나열하겠다는 뜻.
	glEnable(GL_CULL_FACE);

	// EnableClientState에 의해 정점 배열 기능 활성화.
	// 정점좌표, 컬러, 컬러 인덱스, 법선 벡터, 텍스처 좌표 등에도 적용가능.
	glEnableClientState(GL_COLOR_ARRAY); // 정점 색 적용
	glEnableClientState(GL_VERTEX_ARRAY); // 정점 좌표 적용
	// 3은 배열 요소 하나가 3개의 요소로 이루어짐, GL_FLOAT는 이 요소가 부통 소수 타입임을 나타냄. 0은 배열 요소 사이에 빈 공간(Blank Space)이 없음을 의미.
	glColorPointer(3, GL_FLOAT, 0, MyColor); // 실제 정점 색을 저장한 변수명인 MyColor를 제시함.
	glVertexPointer(3, GL_FLOAT, 0, MyVertices); // 실제 정점 좌표를 저장한 변수명인 MyVertex를 제시함.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(Angle, X, Y, Z); // 반시계 방향으로 회전 <glFrontFace(GL_CW)면 시계방향으로 회전함.>
	
	for (GLint i = 0; i < 6; i++) {
		// 그리고자 하는 것이 다각형임을 나타냄. 다각형 하나는 unsigned byte 타입으로 표시되는 4개의 인덱스로 구성.
		// 마지막 파라미터인 &MyVertexlist[4*i]는 정점 리스트의 시작 주소로, i값이 변함에 따라 다각형을 구성하는 첫 인덱스의 시작 주소를 바꾸기 위한 것.
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]); 
	}
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList); // 위의 for 문과 같음
	glFlush();
}

void MyTimer(int Value) {
	
	Angle += 0.5;
	
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1); // 10ms
}
int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);

	glutTimerFunc(10,MyTimer, 1); // 10ms

	glutMainLoop();

	return 0;
}