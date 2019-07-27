//
// DATE : 20190719 ~
// DEV : Framework
//
#pragma warning(disable:4996)


#include "GLController.h"
#ifndef GL
#include "GL/glut.h"
#endif


#ifdef DEFINE_IOSTREAM
#include <iostream>
#elif DEFINE_STDIO_H
#include <stdio.h>
#include <stdlib.h>
#endif // DEFINE_IcOSTREAM


using namespace SagacityEngine;
GLController controller;


// view screen
void ViewScreen() {
	glColor3f(0.2, 0.2, 0.2);
	//
	glViewport(0, 0, controller.GetWidth()/2, controller.GetHeight()/2);
	printf("widht :  %d, height : %d\n", controller.GetWidth(), controller.GetHeight()/2);
	//

	controller.MakeRect(1); // size 1

	printf("Display 호출\n");
}

// project panel
void ProjectScreen() {

	glColor3f(0.1, 1.0, 0.1);
	glViewport(controller.GetWidth() / 2, 0, controller.GetWidth() / 2, controller.GetHeight());
	controller.MakePanel(controller.GetWidth() / 2, 0, controller.GetWidth() / 2, controller.GetHeight()/2);
	controller.MakeRect(1); //size 1
	printf("ProjectPanel 호출\n");
}




//////////////////////////////////////////////////////////////////////////


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	ViewScreen(); // 3d view screen
	ProjectScreen(); // project Screen
	glFlush();
}

void MyKeyboard(unsigned char key, GLint x, GLint y) {
	printf("[MyKeyboard] x : %d, y : %d\n", x, y);
	switch (key) {
	case 'q': 
	case 'Q':
	case 27: // esc or q 
		exit(1); // exit program
		break;
		

	}

}

void MyMouse(GLint button, GLint state, GLint x, GLint y) {
	printf("[MyMouse] button : %d, state : %d, x : %d, y : %d\n", button, state, x, y);
}


// IDLE
void MyIdle() {
}


// 재생성
void MyReshape(int width, int height) {
	printf("width : %d, height : %d\n", width, height);
	controller.SetWindowSize(width, height);

	controller.ResizeWindow(width, height);
	
	

}

// 특수 문자 입력 시 
void MySpecial(int key, int x, int y) {
	printf("[MySpecial] x : %d, y : %d\n", x, y);
	switch (key) {
	case GLUT_KEY_UP:
		controller.Debug("press key up");
		break;
	case GLUT_KEY_DOWN:
		controller.Debug("press key down");
		break;
	case GLUT_KEY_LEFT:
		controller.Debug("press key left");
		break;
	case GLUT_KEY_RIGHT:
		controller.Debug("press key right");
		break;
			
	}
}

// 마우스를 누른 상태에서 움직일 때
void MyMotion(int x, int y) {
	printf("마우스 누를 때 %d, %d \n", x, y);
}

// 아무런 버튼도 누르지 않은 상태에서 움직일 때
void MyPassiveMotion(int x, int y) {
	printf("아무것도 누르지 않은 상태에서 마우스를 움직이는 좌표%d, %d\n", x, y);
}

// 마우스가 윈도우 안으로 들어오거나 밖으로 나갈 때
void MyEntry(int state) {
	printf("state : %d\n", state);

}

void MyMainMenu(int entryID) {
	if (entryID == 1) { // sphere
		controller.menuMode = Mode_DrawSphere_E;
		printf("main menu1 -=> entryid 1\n");
	}
	else if (entryID == 2) { // box
		controller.menuMode = Mode_DrawBox_E;
		printf("main menu1 -=> entryid 2\n");
	}
}

void MyMainMenu2(int entryID) {
	if (entryID == 1) {
		printf("main menu2 -=> entryid 1\n");
	}
	else if (entryID == 2) {
		printf("main menu2 -=> entryid 2\n");
	}
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);


	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game"); // 새로운 윈도우 생성
	controller.GLInit();
	glClearColor(0.5, 0.5, 0.5, 1.0); // init color

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	// Display
	glutDisplayFunc(MyDisplay); //display

	// Keyboard
	glutKeyboardFunc(MyKeyboard); // char key
	glutSpecialFunc(MySpecial); // special key

	// Mouse
	glutMouseFunc(MyMouse); // mouse
	glutMotionFunc(MyMotion); // mouse 누른 상태에서 움직일 때 
	glutPassiveMotionFunc(MyPassiveMotion); // 아무런 버튼도 누르지 않은 상태에서 마우스를 움직이는 것
	glutEntryFunc(MyEntry);

	// Menu 1
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Box", 2);
	glutAttachMenu(GLUT_MIDDLE_BUTTON); // 오른쪽 버튼을 눌렀을 경우
	// Menu 2
	GLint MyMainMenuID2 = glutCreateMenu(MyMainMenu2);
	glutAddMenuEntry("Menu1", 1);
	glutAddMenuEntry("Menu2", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 오른쪽 버튼을 눌렀을 경우
	
	glutIdleFunc(MyIdle); // idle
	glutReshapeFunc(MyReshape); // reshape

	glutMainLoop();
	
	return 0;
}
