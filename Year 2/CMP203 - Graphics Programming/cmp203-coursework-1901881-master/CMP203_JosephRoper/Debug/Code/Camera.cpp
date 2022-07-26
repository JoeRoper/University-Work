#include "Camera.h"

Camera::Camera(Input* in)
{
	input = in;

}

Camera::~Camera()
{
}

void Camera::update()
{
	float cosR, cosP, cosY;		//temp values for sin/cos from
	float sinR, sinP, sinY;
	//Roll, Pitch and Yall are variables stored by the camera
	//handle rotation
	cosP = cosf(Pitch * 3.1415 / 180);//x rotation
	cosY = cosf(Yaw * 3.1415 / 180);//y rotation within 3d space
	cosR = cosf(Roll * 3.1415 / 180);//z rotation 
	sinY = sinf(Yaw * 3.1415 / 180);
	sinP = sinf(Pitch * 3.1415 / 180);
	sinR = sinf(Roll * 3.1415 / 180);

	//This using thw parametric equation of a sphere

	//Calculates the three vectors to put into glu Lookat
	//Look direction, position and the up vector
	//This function also calculates the right vector

	forward.x = sinY * cosP; 
	forward.y = sinP;
	forward.z = cosP * -cosY;

	//Look at point
	lookAt = position;
	lookAt.add(forward);

	//up vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	//Side Vector (right)
	//thiss is a cross product between the forward and up vector
	right = forward.cross(up);

	//used to update the camera in scene
	gluLookAtArray[0] = { position.x };
	gluLookAtArray[1] = { position.y };
	gluLookAtArray[2] = { position.z };

	gluLookAtArray[3] = { lookAt.x };
	gluLookAtArray[4] = { lookAt.y };
	gluLookAtArray[5] = { lookAt.z };

	gluLookAtArray[6] = { up.x };
	gluLookAtArray[7] = { up.y };
	gluLookAtArray[8] = { up.z };
}
void Camera::keyboardInput(float dt)
{
	int speed = 1;
	double cameraSpeed = 0.6;
	Vector3 tempVec;
	if (input->isKeyDown('w'))//forward
	{
		tempVec = forward;
		tempVec.scale(cameraSpeed);
		position += tempVec;
		input->setKeyUp('w');
	}
	if (input->isKeyDown('s'))//back
	{
		tempVec = forward;
		tempVec.scale(cameraSpeed);
		position -= tempVec;
		input->setKeyUp('s');
	}

	if (input->isKeyDown('d'))//right
	{
		tempVec = right;
		tempVec.scale(cameraSpeed);
		position += tempVec;
		input->setKeyUp('d');
	}
	if (input->isKeyDown('a'))//left
	{
		tempVec = right;
		tempVec.scale(cameraSpeed);
		position -= tempVec;
		input->setKeyUp('a');
	}

	if (input->isKeyDown('e'))//up
	{
		tempVec = up;
		tempVec.scale(cameraSpeed);
		position += tempVec;
		input->setKeyUp('e');
	}
	if (input->isKeyDown('q'))//down
	{
		tempVec = up;
		tempVec.scale(cameraSpeed);
		position -= tempVec;
		input->setKeyUp('q');
	}
}


void Camera::mouseInput(float dt, float width, float height)
{
	glutSetCursor(GLUT_CURSOR_NONE);//resets mouse

	screenWidth = width;
	screenHeight = height;

	float mouseDifferenceX, mouseDifferenceY, centrePositionX, centrePositionY;
	float scale = 55.0;//used to scale down the mouse movement speed

	centrePositionX = screenWidth / 2;
	centrePositionY = screenHeight / 2;

	mouseDifferenceX = input->getMouseX() - centrePositionX;//calculates how much the mouse should be moved left or right
	mouseDifferenceY = input->getMouseY() - centrePositionY;//calculates how much the mouse should be moved up or down

	Yaw = Yaw + (mouseDifferenceX * scale * dt);//up and down
	Pitch = Pitch - (mouseDifferenceY * scale * dt);//left and right
	glutWarpPointer(centrePositionX, centrePositionY);//sets mouse position to be the middle of the screen

	//mouse code in scene cpp resize and constructor
}
;
