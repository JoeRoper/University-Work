#include "glut.h"
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include "math.h"
#include <vector>
#pragma once
class Texture
{
public:
	Texture();
	~Texture();

private:

	GLuint crate, rubixCube, skyBox, slabTexture, cobbleTexture, stoneTexture, grassTexture, carpetTexture, lampOnTexture, lampOffTexture, woodTexture, windowTexture, skyboxTexture, doorTopTexture, doorBottomTexture;
	GLuint imposterTableTexture;
};

