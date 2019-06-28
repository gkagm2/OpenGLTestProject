#include <Windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <math.h>

static double time = 0;
static double time2 = 0;
static double time3 = 0;
static double time4 = 0;
static double time6 = 0;

GLfloat R_Arm_x = 0; // ������ ���
GLfloat R_Arm_y = 0; // ���� ��
GLfloat L_Arm_x = 0; // ���� ���
GLfloat L_Arm_y = 0; // ���� ��
GLfloat R_Leg_x = 0; // ������ �����
GLfloat R_Leg_y = 0; // ������ ���Ƹ�
GLfloat L_Leg_x = 0; // ���� �����
GLfloat L_Leg_y = 0; // ���� ���Ƹ�
GLfloat R = 0; //���� ���� ��ġ ������ ����
GLfloat R2 = 0; // ������ ���� ��ġ ������ ����

GLUquadricObj *cyl; // �Ǹ��� ��ü ����

int a = 0; // x�� ����(���� 1�� �� x���� �������� ȸ��)
int b = 0; // y�� ����(���� 1�� �� y���� �������� ȸ��)
int c = 0; // z�� ����(���� 1�� �� z���� �������� ȸ��)

static int flag = 0; // wireframe ���� solid rendering ��� ���� ����
static int key = 0; // ���� ���� ���� ���� ����

#define RUN 1
#define JAP 2
#define ROCKET 3
#define YUNA 4
#define EXIT 6

void glInit(void) { // ���� �ʱ�ȭ �Լ�
	glEnable(GL_DEPTH_TEST); // ���� �׽��� ���
	glEnable(GL_NORMALIZE); // ����ȭ
	glEnable(GL_SMOOTH); // �� ������ ������ �ε巴�� �����Ͽ� ĥ��������
	glEnable(GL_LIGHTING); // ���� ����, ���� �޴� ������ ���� �κ� ������ ��ȭ
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f ,1.0f };
	GLfloat position[] = { 400.0, 300.0, -700.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION); // ��� ����
	glLoadIdentity(); // CTM �� �ʱ�ȭ
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ���� ���� ����
}

// ������ �׸��� �Լ�
void Draw_Color(int i) {
	if (i == RUN) {
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (i == JAP) {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (i == ROCKET) {
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (i == YUNA) {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (i == EXIT) {
		glColor3f(0.2, 0.2, 0.2);
	}
}

// �ָ���, ���̾� ����
void Change_Wire_Or_Solid(int i) {
	if (flag == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE); // ��Ÿ���� ���̾�� ����
}

// �κ� ������ �׸��� �Լ�
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c); // �Ķ���� ����ŭ ����
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ��. (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.25, 0.0, 0.0); // ���� ��� ���������� �̵�
	glRotatef(15.0, 0.0, 1.0, 0.0);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸� 

}

// �κ� �޼��� �׸��� �Լ�
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22); // �޼� ������
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1); // �򶧱� ��� �Ǹ����� �׸�
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ���� �ָ�
void DrawL_HandRocket() {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0, 0, R); // ���� �ָ� ��ġ�� �Ķ���͸�ŭ �̵�
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� �������� �׸��� �Լ�
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c); // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ�� (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.25, 0.0, 0.0); // ������ ��� ���������� �̵�
	glRotatef(-15.0, 0.0, 1.0, 0.0); // ������ ����� y������ -15�� ȸ��
	Change_Wire_Or_Solid(flag); 
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
}

// �κ� �������� �׸��� �Լ�
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22); // ������ ������
	glRotatef(y, a, b, c); // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 50, 1); // �򶧱� ��� �Ǹ����� �׸�
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ������ ���� �Լ�
void DrawR_HandRocket() {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0, 0, R2); // ������ �ָ� ��ġ�� �Ķ���͸�ŭ �̵�
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ��ü�� �׸��� �Լ�
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ�� (�Ǹ��� ���� �� ���� ������ ����)
	glRotatef(x, a, b, c); // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ���� ������� �׸��� �Լ�
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

// �κ� ���� ���Ƹ��� �׸��� �Լ�
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
		gluCylinder(cyl, 0.05, 0.03, 0.2, 50, 1);
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
	glPopMatrix();
}

// �κ� ������ ������� �׸��� �Լ�
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}


// �κ� ������ ���Ƹ��� �׸��� �Լ�
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
		gluCylinder(cyl, 0.05, 0.03, 0.2, 15, 1);
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

// �κ� ���� �׸��� �Լ�
void DrawNeck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // ������ (���)
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����

	/// TODO : 9�� Ȥ�� 90�� ������ �´°��ΰ�
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ�� (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.0, 0.0, -0.045); // �� ������
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// ������ �׸��� �Լ�. �̴� Ŀ�ٶ� ���� �����Ͽ����� ������ �ð��� ���� ȸ���Ͽ� ��ġ �κ��� ������ �پ�� ������ �鵵�� ��.
void DrawGround() {
	Draw_Color(flag);
	glTranslatef(0.0, -2.73, 0.0); // ���� ����
	glRotatef(45.0, 0, 1, 0); // 45����ŭ y���� �������� ȸ��
	glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1); // z���� �������� time4��ŭ ������ ȸ��
	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 2.5, 30, 90);
}

// �κ� �Ӹ��� �׸��� �Լ�. �Ӹ��� �޸� �԰� �κ��� ���� ������
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0); // �Ӹ� ������
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(flag);
 	Draw_Color(key); // ���� ����
	gluSphere(cyl, 0.2, 30, 20); // �Ӹ� �׸���

	// ���� �� �׸���
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ��� 90�� x���� �������� ȸ�� (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.16, 0.0, -0.22); // ���� �� ������
	glRotatef(35.0, 0.0, 1.0, 0.0); // 35�� y���� �������� ȸ��
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1); // �Ǹ����� �׸�
	glPopMatrix(); // ���� ���� ��ǥ��� ���ư���.
	glPushMatrix(); // ���� ���� ��ǥ��� ���ư���.

	// ������ �� �׸���
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.16, 0.0, -0.22); // ������ �� ������
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
	glPopMatrix();
	glPushMatrix();

	// ���� �� �׸���
	glTranslatef(-0.1, 0.1, 0.13); // ���� �� ������
	glColor3f(0.0, 0.0, 0.0); // �� �÷� ���� (���)
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix(); // ���� ���� ��ǥ��� ���ư�
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����

	// ������ �� �׸���
	glTranslatef(0.1, 0.1, 0.13); // ������ �� ������
	//glColor3f(0.0, 0.0, 0.0);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
}

// �κ� ��ü
void DrawAndroid() {
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	DrawNeck(); // �� �Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawR_Arm(R_Arm_x, 1, 0, 0); // ������
	if (key == ROCKET)
		DrawR_HandRocket(); // ���� ����� �� ������ ���� ȣ��
	else
		DrawR_Hand(R_Arm_y, 1, 0, 0); // ������

	DrawL_Arm(L_Arm_x, 1, 0, 0); // ����
	if (key == ROCKET)
		DrawL_HandRocket(); // ���� ����� �� ���� ���� ȣ��
	else
		DrawL_Hand(L_Arm_y, 1, 0, 0);
	DrawL_Legs(L_Leg_x, 1, 0, 0); // ���� �ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0); // ���� ��
	DrawR_Legs(R_Leg_x, 1, 0, 0); // ������ �ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0); // ������ ��
}

void Run() {
	// TODO : ���� ��� ����
	sndPlaySound(TEXT("C:\\sample1.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); // CTM �ʱ�ȭ
	L_Arm_x = sin(time) * 80; // ������ 80������ �����̵� sin()���� �ֱ����� ������ ����
	R_Arm_y = -abs(sin(time) * 60 + 50); // ������ ���� ���� (������ �����ν� ���� �ڷ� ������ ����.)
	L_Arm_y = -abs(-sin(time) * 60 + 50); // ���� ���� ����
	R_Leg_y = abs(sin(time) * 30 - 30); // ������ ���Ƹ� ���� ����
	L_Leg_y = abs(sin(time) * 30 - 30); // ���� ���Ƹ� ���� ����
	R_Leg_x = sin(time) * 60; // ������ �ٸ��� 60������ �����̵� sin()���� �ֱ����� ������ ����
	L_Leg_x = -R_Leg_x; // ���� �ٸ��� ������ �ٸ� �ݴ��

	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); // ��� ����

	DrawGround(); // ������ �׸�
	glLoadIdentity(); // CTM �ʱ�ȭ

	// �κ��� �޸��鼭 ��, �ڷ� �ڶװŸ��� ���� Ʋ������ ���� ǥ��
	glRotatef(-230.0, 0, 1, 0);
	glRotatef(abs(sin(time) * 16), 1, 0, 0); // x���� �������� 16������ ������ Ʋ����.
	glRotatef(sin(time) * 16, 0, 1, 0); // y���� �������� 16������ ������ Ʋ����, sin() �Լ��� �ֱ����� ������ ����

	// �κ��� �޸��鼭 ���Ϸ� �����̴� ���� ǥ��
	float i = 0;
	i = abs(sin(time) * 0.08); // i ���� �� ����
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
	glTranslatef(0.0, i, 0); // �κ��� ��ü�� y�� �������� ���� i��ŭ �̵�
	glTranslatef(0.0, 0.5, 0.0); // �κ��� ���� ��ġ
	DrawAndroid();
	glutSwapBuffers();
}

// �κ��� ���� ������ ������ ǥ���� �Լ�
void Jap() {
	sndPlaySound(TEXT("C:\\"), SND_ASYNC | SND_NOSTOP);
	// TODO : ���⼭ ���� �ؾ� ��.
}





int main(int argc, char **argv) {

	return 0;
}