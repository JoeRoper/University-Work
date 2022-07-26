#include "Light.h"

void Light::renderLight0()//Street Lamp 0
{
	GLfloat Light_Diffuse0[] = { 1.67f, 0.0f, 2.55f, 1.0f };//purple
	GLfloat Light_Position0[] = { 2.0f, 8.0f, 5.5f, 1.0f };
	GLfloat Light_Direction0[] = { 0.0f, -1.0f, 0.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse0);//sets light data up
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position0);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0f);//sets light cone shape
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light_Direction0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 50.0);
	glPopMatrix();
}

void Light::renderLight1()//street lamp 1
{
	GLfloat Light_Diffuse1[] = { 0.0f, 2.04f, 2.04f, 1.0f };//teal blue
	GLfloat Light_Position1[] = { 16.0f, 8.0f, 5.5f, 1.0f };
	GLfloat Light_Direction1[] = { 0.0f, -1.0f, 0.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0f);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light_Direction1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);
	glPopMatrix();
}

void Light::renderLight2()//street lamp 2
{
	//GLfloat Light_Ambient0[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse2[] = { 2.55f, 1.53f, 0.51f, 1.0f };//orange
	GLfloat Light_Position2[] = { 2.0f, 8.0f, 12.5f, 1.0f };
	GLfloat Light_Direction2[] = { 0.0f, -1.0f, 0.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position2);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0f);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Light_Direction2);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 50.0);
	glPopMatrix();
}

void Light::renderLight3()//street lamp 3
{
	GLfloat Light_Diffuse3[] = { 1.0f, 1.0f, 1.0f, 1.0f };//white
	GLfloat Light_Position3[] = { 16.0f, 8.0f, 12.5f, 1.0f };
	GLfloat Light_Direction3[] = { 0.0f, -1.0f, 0.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse3);
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position3);

	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0f);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, Light_Direction3);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 50.0);
	glPopMatrix();
}

void Light::renderLight4()//scene ambient light
{
	GLfloat Light_Ambient4[] = { 0.255f, 0.214f, 0.170f, 1.0f };
	GLfloat Light_Position4[] = { 0.0f, 0.0f, 1.0f, 0.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT4, GL_AMBIENT, Light_Ambient4);
	glLightfv(GL_LIGHT4, GL_POSITION, Light_Position4);
	glEnable(GL_LIGHT4);
	glPopMatrix();
}

void Light::renderLight5()//inside cafe light
{
	GLfloat Light_Diffuse5[] = { 0.255f, 0.197f, 0.143f, 1.0f };//warm room light colour
	GLfloat Light_Position5[] = { 29.0f, 5.0f, 0.5f, 1.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Light_Diffuse5);
	glLightfv(GL_LIGHT5, GL_POSITION, Light_Position5);

	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.002);//sets attenuation to low so that the light doesnt appear outside of the room
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.002);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.01);
	glPopMatrix();
}

void Light::renderLight6()//bathroom light
{
	GLfloat Light_Diffuse6[] = { 0.255f, 0.197f, 0.143f, 1.0f };//warm room light colour
	GLfloat Light_Position6[] = { 43.0f, 2.0f, 0.5f, 1.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT6, GL_DIFFUSE, Light_Diffuse6);
	glLightfv(GL_LIGHT6, GL_POSITION, Light_Position6);

	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0.0006);
	glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.0006);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.01);
	glPopMatrix();
}

void Light::renderLight7()//outside cafe light
{
	GLfloat Light_Diffuse7[] = { 0.255f, 0.197f, 0.143f, 1.0f };//warm room light colour
	GLfloat Light_Position7[] = { 30.0f, 9.0f, 15.0f, 1.0f };

	glPushMatrix();
	glLightfv(GL_LIGHT7, GL_DIFFUSE, Light_Diffuse7);
	glLightfv(GL_LIGHT7, GL_POSITION, Light_Position7);

	glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0.0006);
	glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 0.0006);
	glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.01);
	glPopMatrix();
}

void Light::disableLight(int lightNum)
{
	//switch statement to easily disable each light individually
	switch (lightNum) {
	case 0:
		glDisable(GL_LIGHT0);
		break;
	case 1:
		glDisable(GL_LIGHT1);
		break;
	case 2:
		glDisable(GL_LIGHT2);
		break;
	case 3:
		glDisable(GL_LIGHT3);
		break;
	case 4:
		glDisable(GL_LIGHT4);
		break;
	case 5:
		glDisable(GL_LIGHT5);
		break;
	case 6:
		glDisable(GL_LIGHT6);
		break;
	case 7:
		glDisable(GL_LIGHT7);
		break;
	}
}

void Light::enableLight(int lightNum)
{
	//switch statement to easily enable each light individually
	switch (lightNum) {
	case 0:
		glEnable(GL_LIGHT0);
		break;
	case 1:
		glEnable(GL_LIGHT1);
		break;
	case 2:
		glEnable(GL_LIGHT2);
		break;
	case 3:
		glEnable(GL_LIGHT3);
		break;
	case 4:
		glEnable(GL_LIGHT4);
		break;
	case 5:
		glEnable(GL_LIGHT5);
		break;
	case 6:
		glEnable(GL_LIGHT6);
		break;
	case 7:
		glEnable(GL_LIGHT7);
		break;
	}
}
