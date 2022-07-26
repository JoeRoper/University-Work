#pragma once
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
class Light
{
public:
	void renderLight0();
	void renderLight1();
	void renderLight2();
	void renderLight3();
	void renderLight4();
	void renderLight5();
	void renderLight6();
	void renderLight7();
	void disableLight(int lightNum);
	void enableLight(int lightNum);

private:

	
};

