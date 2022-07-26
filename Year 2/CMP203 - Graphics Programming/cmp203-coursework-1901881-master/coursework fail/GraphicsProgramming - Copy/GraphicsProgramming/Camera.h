#pragma once
// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include "Vector3.h"
#include "Input.h"
#include <string>
using namespace std;
class Camera
{
public:
	Camera(Input* in);
	~Camera();
	void update();
	void keyboardInput(float dt);
	void mouseInput(float dt, float width, float height);
	//getters
	Vector3 getPostion() { return position; }
	Vector3 getLookAt() { return lookAt; }
	Vector3 getRotation() { return rotation; }
	//setters
	void setPosition(float x, float y, float z) { position.set(x, y, z); }
	void setLookAt(float x, float y, float z) { lookAt.set(x, y, z); }
	void setRotation(float x, float y, float z) { rotation.set(x, y, z); }

	float gluLookAtArray[9];

private:

	Vector3 forward, up, right, position, lookAt, rotation;
	float Pitch, Yaw, Roll;
	float screenWidth, screenHeight;
	Input* input;//to access input functions
};

