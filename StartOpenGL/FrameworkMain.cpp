//
// DATE : 20190719 ~
// DEV : Framework
//
#pragma warning(disable:4996)

#define DEFINE_STDIO_H 1
#ifdef DEFINE_IOSTREAM
#include <iostream>
#elif DEFINE_STDIO_H
#include <stdio.h>
#endif // DEFINE_IcOSTREAM

#include <stdlib.h>
#include "GL/glut.h"

namespace SagacityEngine {	
	enum Mode {
		Mode_DrawSphere_E,
		Mode_DrawBox_E
	};


	class ScreenController {

	};

	class GLController : public ScreenController {
	private:
		int width;
		int height;

		

	public:
		GLfloat x, y, z;
		GLfloat screenX, screenY;

		
		Mode menuMode;
		

		GLController(const GLfloat x = 0, const GLfloat y = 0, const GLfloat z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;

			width = 0;
			height = 0;
		};



		void SetPosition(const GLfloat x, const GLfloat y, const GLfloat z);
		void GLInit();
		void ShowScreen();
		void SetWindowSize(int width, int height);
		int GetWidth();
		int GetHeight();
		void MakeCube();
		void MakeRect(float size);
		void MakePanel(const float x, const float y, const float width, const float heigth);

		void CallError(const char *message);
		void Debug(const char *message);
		void ChangeNormalizationToScreenCoordinate(float x, float y, float width, float heigth);

		void ResizeWindow(int width, int height); // resize window
		
	};


	//// FUNCTION

	void GLController::ResizeWindow(int width, int height) {
		
		glViewport(0, 0, width, height);
		GLfloat widthFactor = (GLfloat)width / (GLfloat)1280;
		GLfloat heightFactor = (GLfloat)height / (GLfloat)720;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1.0 * heightFactor, 1.0 * heightFactor, -1.0, 1.0);
	}

	void GLController::CallError(const char *message) {
#ifdef DEFINE_IOSTREAM
		std::cout << "error !" << message << std::endl;
#elif DEFINE_STDIO_H
		printf(" error 1! %s\n", message);
#endif	
	}
	void GLController::Debug(const char *message) {
#ifdef DEFINE_IOSTREAM
		std::cout << "Debug : "<< message << std::endl;
#elif DEFINE_STDIO_H
		printf("Debug : %s\n", message);
#endif	
	}

	

	void GLController::MakePanel(const float x, const float y, const float width, const float height) {
		// TODO : rgb 배열의 index가 늘거나 줄면 큰일남. 예외처리 해야 함
		
		printf("%f %f %f %f \n", x, y, width, height);

		glViewport(GetWidth() / 2, 0, GetWidth() / 2, GetHeight());

		glBegin(GL_POLYGON);
		
		// make panel
		glVertex3f(x, y, 0);
		glVertex3f(x + width, y, 0);
		glVertex3f(x + width, y + height, 0);
		glVertex3f(x, y + height, 0);
		glEnd();
	}


	void GLController::SetPosition(const GLfloat x, const GLfloat y, const GLfloat z) {

	}
	void GLController::GLInit() {

	}

	void GLController::ShowScreen() {

	}
	void GLController::SetWindowSize(int width, int height) {
		this->width = width;
		this->height = height;
	}

	int GLController::GetWidth() {
		return width;
	}
	int GLController::GetHeight() {
		return height;
	}

	void GLController::MakeCube() {
		glutSolidCube(5.0);
	}
	void GLController::MakeRect(float size) {
		if (size <= 0 || size > 1) {
			CallError(" 사각형 사이즈는 0에서 1까지만 가능합니다.");
			return;
		}
		glBegin(GL_POLYGON);
		glVertex3f(-size, -size, 0);
		glVertex3f(size, -size, 0);
		glVertex3f(size, size, 0);
		glVertex3f(-size, size, 0);
		glEnd();
	}

	void GLController::ChangeNormalizationToScreenCoordinate(float x, float y, float width, float height) {

		// change normalization coordinate to screen coordinate 
		screenX = width * (0.5 - (-1.0)) / 2.0;
		screenY = height * (0.5 - (-1.0)) / -2.0;
	}
	
}


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

	



	//

	glutMainLoop();
	
	return 0;
}
