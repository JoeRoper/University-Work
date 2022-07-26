#include "SkyBox.h"

SkyBox::SkyBox(GLuint texture)
{
	shape = new Shape(texture);
}

SkyBox::~SkyBox()
{
}

void SkyBox::update()
{
	cubeCenter = camera->getPostion();//sets the cube center to the camera position so the skybox stays with the camera
	renderNew();
}

void SkyBox::renderNew()
{
	glPushMatrix();
	glTranslatef(cubeCenter.x, cubeCenter.y, cubeCenter.z);//moves the skybox to the camera
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	shape->renderCube();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}