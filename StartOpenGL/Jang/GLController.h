#ifndef GL
#include "GL/glut.h"
#endif




#define DEFINE_STDIO_H 1
#ifdef DEFINE_IOSTREAM
#include <iostream>
#elif DEFINE_STDIO_H
#include <stdio.h>
#endif // DEFINE_IcOSTREAM

namespace SagacityEngine {

	enum Mode {
		Mode_DrawSphere_E,
		Mode_DrawBox_E
	};

	class GLController {
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
}
