// Vertex Array

// Cube Shape
//    5----6
//  1/---2/|
//  | |  | |
//  | 4--|-7
//  0/---3/
#include <GL/glut.h>

// ����ü ������ ��ǥ
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

// ������ ��
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

// ���� ���� ���� ���� � �����鿡 ���� �̷�������� 
GLbyte MyVertexList[24] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };


GLfloat Angle = 0.0;
GLfloat X = 1.0;
GLfloat Y = 0.0;
GLfloat Z = 0.0; // �ٶ󺸴���( ����� ��)�� Z��+ ���� ��

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW); // counter-clockwise ǥ���� �ݽð� �������� �����ϰڴٴ� ��.
	glEnable(GL_CULL_FACE);

	// EnableClientState�� ���� ���� �迭 ��� Ȱ��ȭ.
	// ������ǥ, �÷�, �÷� �ε���, ���� ����, �ؽ�ó ��ǥ ��� ���밡��.
	glEnableClientState(GL_COLOR_ARRAY); // ���� �� ����
	glEnableClientState(GL_VERTEX_ARRAY); // ���� ��ǥ ����
	// 3�� �迭 ��� �ϳ��� 3���� ��ҷ� �̷����, GL_FLOAT�� �� ��Ұ� ���� �Ҽ� Ÿ������ ��Ÿ��. 0�� �迭 ��� ���̿� �� ����(Blank Space)�� ������ �ǹ�.
	glColorPointer(3, GL_FLOAT, 0, MyColor); // ���� ���� ���� ������ �������� MyColor�� ������.
	glVertexPointer(3, GL_FLOAT, 0, MyVertices); // ���� ���� ��ǥ�� ������ �������� MyVertex�� ������.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(Angle, X, Y, Z); // �ݽð� �������� ȸ�� <glFrontFace(GL_CW)�� �ð�������� ȸ����.>
	
	for (GLint i = 0; i < 6; i++) {
		// �׸����� �ϴ� ���� �ٰ������� ��Ÿ��. �ٰ��� �ϳ��� unsigned byte Ÿ������ ǥ�õǴ� 4���� �ε����� ����.
		// ������ �Ķ������ &MyVertexlist[4*i]�� ���� ����Ʈ�� ���� �ּҷ�, i���� ���Կ� ���� �ٰ����� �����ϴ� ù �ε����� ���� �ּҸ� �ٲٱ� ���� ��.
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]); 
	}
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, MyVertexList); // ���� for ���� ����
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