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

#include "Camera.h"
#include "Shape.h"
#include "Texture.h"
class SkyBox
{
public:
	SkyBox(GLuint texture);
	~SkyBox();
	void update();
	void renderNew();

	void setCubeCenter(float x, float y, float z) { cubeCenter.set(x,y,z); };

	Vector3 getCubeCenter() { return cubeCenter; };

	void setCamera(Camera* camera) { this->camera = camera; };

private:

	Camera* camera;
	Shape* shape;
	Vector3 cubeCenter;
};

