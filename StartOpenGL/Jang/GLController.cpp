#include "GLController.h"

using namespace SagacityEngine;

namespace SagacityEngine {

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
		std::cout << "Debug : " << message << std::endl;
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