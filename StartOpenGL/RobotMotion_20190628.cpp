#include <Windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <math.h>

static double time = 0;
static double time2 = 0;
static double time3 = 0;
static double time4 = 0;
static double time6 = 0;

GLfloat R_Arm_x = 0; // 오른쪽 어깨
GLfloat R_Arm_y = 0; // 오른 팔
GLfloat L_Arm_x = 0; // 왼쪽 어깨
GLfloat L_Arm_y = 0; // 왼쪽 팔
GLfloat R_Leg_x = 0; // 오른쪽 허벅지
GLfloat R_Leg_y = 0; // 오른쪽 종아리
GLfloat L_Leg_x = 0; // 왼쪽 허벅지
GLfloat L_Leg_y = 0; // 왼쪽 종아리
GLfloat R = 0; //왼쪽 로켓 펀치 움직임 변수
GLfloat R2 = 0; // 오른쪽 로켓 펀치 움직임 변수

GLUquadricObj *cyl; // 실린더 객체 선언

int a = 0; // x축 기준(값이 1일 때 x축을 기준으로 회전)
int b = 0; // y축 기준(값이 1일 때 y축을 기준으로 회전)
int c = 0; // z축 기준(값이 1일 때 z축을 기준으로 회전)

static int flag = 0; // wireframe 모드와 solid rendering 모드 구분 변수
static int key = 0; // 동작 모드와 색상 변경 변수

#define RUN 1
#define JAP 2
#define ROCKET 3
#define YUNA 4
#define EXIT 6

void glInit(void) { // 지엘 초기화 함수
	glEnable(GL_DEPTH_TEST); // 깊이 테스팅 사용
	glEnable(GL_NORMALIZE); // 정규화
	glEnable(GL_SMOOTH); // 각 정점의 색상을 부드럽게 연결하여 칠해지도록
	glEnable(GL_LIGHTING); // 지엘 조명, 빛을 받는 각도에 따라 로봇 색상이 변화
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
	glMatrixMode(GL_PROJECTION); // 모드 설정
	glLoadIdentity(); // CTM 값 초기화
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 가시 범위 설정
}

// 색상을 그리는 함수
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

// 솔리드, 와이어 선택
void Change_Wire_Or_Solid(int i) {
	if (flag == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE); // 스타일을 와이어로 변경
}

// 로봇 왼팔을 그리는 함수
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c); // 파라미터 값만큼 설정
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전. (실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0); // 왼쪽 어깨 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림 

}

// 로봇 왼손을 그리는 함수
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 왼손 시작점
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1); // 깔때기 모양 실린더를 그림
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 왼쪽 주먹
void DrawL_HandRocket() {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R); // 왼쪽 주먹 위치를 파라미터만큼 이동
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 오른팔을 그리는 함수
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c); // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전 (실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); // 오른쪽 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); // 오른쪽 어깨를 y축으로 -15도 회전
	Change_Wire_Or_Solid(flag); 
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

// 로봇 오른손을 그리는 함수
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 오른손 시작점
	glRotatef(y, a, b, c); // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag);
	if (key == YUNA)
		gluCylinder(cyl, 0.05, 0.02, 0.2, 50, 1); // 깔때기 모양 실린더를 그림
	else
		gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 오른쪽 로켓 함수
void DrawR_HandRocket() {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R2); // 오른쪽 주먹 위치를 파라미터만큼 이동
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 몸체를 그리는 함수
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전 (실린더 생성 시 각도 변경을 위해)
	glRotatef(x, a, b, c); // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 왼쪽 허벅지를 그리는 함수
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

// 로봇 왼쪽 종아리를 그리는 함수
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

// 로봇 오른쪽 허벅지를 그리는 함수
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


// 로봇 오른쪽 종아리를 그리는 함수
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

// 로봇 목을 그리는 함수
void DrawNeck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // 색지정 (흰색)
	cyl = gluNewQuadric(); // 실린더 객체 생성

	/// TODO : 9도 혹은 90도 무엇인 맞는것인가
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전 (실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.0, 0.0, -0.045); // 목 시작점
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1); // 실린더를 그림
	glPopMatrix();
}

// 지면을 그리는 함수. 이는 커다란 구로 설정하엿으며 지면이 시간에 따라 회전하여 마치 로봇이 앞으로 뛰어가는 느낌이 들도록 함.
void DrawGround() {
	Draw_Color(flag);
	glTranslatef(0.0, -2.73, 0.0); // 색상 설정
	glRotatef(45.0, 0, 1, 0); // 45도만큼 y축을 기준으로 회전
	glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1); // z축을 기준으로 time4만큼 지면이 회전
	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 2.5, 30, 90);
}

// 로봇 머리를 그리는 함수. 머리에 달린 뿔과 로봇의 눈을 설정함
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0); // 머리 시작점
	glPushMatrix(); // 최초 저장 좌표계 다시 저장
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(flag);
 	Draw_Color(key); // 색상 설정
	gluSphere(cyl, 0.2, 30, 20); // 머리 그리기

	// 왼쪽 뿔 그리기
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더 90도 x축을 기준으로 회전 (실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.16, 0.0, -0.22); // 왼쪽 뿔 시작점
	glRotatef(35.0, 0.0, 1.0, 0.0); // 35도 y축을 기준으로 회전
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1); // 실린더를 그림
	glPopMatrix(); // 최초 저장 좌표계로 돌아간다.
	glPushMatrix(); // 최초 저장 좌표계로 돌아간다.

	// 오른쪽 뿔 그리기
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.16, 0.0, -0.22); // 오른쪽 뿔 시작점
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
	glPopMatrix();
	glPushMatrix();

	// 왼쪽 눈 그리기
	glTranslatef(-0.1, 0.1, 0.13); // 왼쪽 눈 시작점
	glColor3f(0.0, 0.0, 0.0); // 눈 컬러 설정 (흑색)
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix(); // 최초 저장 좌표계로 돌아감
	glPushMatrix(); // 최초 저장 좌표계 다시 저장

	// 오른쪽 눈 그리기
	glTranslatef(0.1, 0.1, 0.13); // 오른쪽 눈 시작점
	//glColor3f(0.0, 0.0, 0.0);
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix();
}

// 로봇 전체
void DrawAndroid() {
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	DrawNeck(); // 목 함수 호출
	DrawHead(); // 머리 호출
	DrawR_Arm(R_Arm_x, 1, 0, 0); // 오른팔
	if (key == ROCKET)
		DrawR_HandRocket(); // 로켓 모드일 때 오른쪽 로켓 호출
	else
		DrawR_Hand(R_Arm_y, 1, 0, 0); // 오른손

	DrawL_Arm(L_Arm_x, 1, 0, 0); // 왼팔
	if (key == ROCKET)
		DrawL_HandRocket(); // 로켓 모드일 때 왼쪽 로켓 호출
	else
		DrawL_Hand(L_Arm_y, 1, 0, 0);
	DrawL_Legs(L_Leg_x, 1, 0, 0); // 왼쪽 다리
	DrawL_foot(L_Leg_y, 1, 0, 0); // 왼쪽 발
	DrawR_Legs(R_Leg_x, 1, 0, 0); // 오른쪽 다리
	DrawR_foot(R_Leg_y, 1, 0, 0); // 오른쪽 발
}

void Run() {
	// TODO : 사운드 헤더 문제
	sndPlaySound(TEXT("C:\\sample1.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); // CTM 초기화
	L_Arm_x = sin(time) * 80; // 왼팔은 80도까지 움직이되 sin()으로 주기적인 움직임 설정
	R_Arm_y = -abs(sin(time) * 60 + 50); // 오른팔 각도 조절 (절댓값을 줌으로써 팔이 뒤로 꺾이지 않음.)
	L_Arm_y = -abs(-sin(time) * 60 + 50); // 왼팔 각도 조절
	R_Leg_y = abs(sin(time) * 30 - 30); // 오른쪽 종아리 각도 조절
	L_Leg_y = abs(sin(time) * 30 - 30); // 왼쪽 종아리 각도 조절
	R_Leg_x = sin(time) * 60; // 오른쪽 다리는 60도까지 움직이되 sin()으로 주기적인 움직임 설정
	L_Leg_x = -R_Leg_x; // 왼쪽 다리는 오른쪽 다리 반대로

	cyl = gluNewQuadric(); // 실리더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 초기화
	glMatrixMode(GL_MODELVIEW); // 모드 설정

	DrawGround(); // 지면을 그림
	glLoadIdentity(); // CTM 초기화

	// 로봇이 달리면서 앞, 뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
	glRotatef(-230.0, 0, 1, 0);
	glRotatef(abs(sin(time) * 16), 1, 0, 0); // x축을 기준으로 16도까지 각도가 틀어짐.
	glRotatef(sin(time) * 16, 0, 1, 0); // y축을 기준으로 16도까지 각도가 틀어짐, sin() 함수로 주기적인 움직임 설정

	// 로봇이 달리면서 상하로 움직이는 것을 표현
	float i = 0;
	i = abs(sin(time) * 0.08); // i 변수 값 설정
	glPushMatrix(); // 최초 저장 좌표계 다시 저장
	glTranslatef(0.0, i, 0); // 로봇의 몸체가 y축 방향으로 변수 i만큼 이동
	glTranslatef(0.0, 0.5, 0.0); // 로봇의 최초 위치
	DrawAndroid();
	glutSwapBuffers();
}

// 로봇이 잽을 날리는 동작을 표현한 함수
void Jap() {
	sndPlaySound(TEXT("C:\\"), SND_ASYNC | SND_NOSTOP);
	// TODO : 여기서 부터 해야 함.
}





int main(int argc, char **argv) {

	return 0;
}