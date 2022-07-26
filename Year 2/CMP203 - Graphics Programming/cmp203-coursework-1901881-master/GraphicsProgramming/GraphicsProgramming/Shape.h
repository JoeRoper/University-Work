#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include "SOIL.h"
#include "math.h"
#include <vector>
#include "Texture.h"

class Shape
{

	public:
		Shape(GLuint texture);
		~Shape();
		void renderCube();

		void slabCreate(int slabNum);
		void slabRender();

		void planeCreate(int Width, int Depth);
		void planeRender();

		void proceduralBoxCreate(int Width, int Height, int Depth);
		void proceduralBoxRender();

	protected:

		//Slab
		std::vector<GLfloat> slabVerts;
		std::vector<GLfloat> slabNorms;
		std::vector<GLfloat> slabTex;

		//Plane
		std::vector<GLfloat> planeVerts;
		std::vector<GLfloat> planeNorms;
		std::vector<GLfloat> planeTex;

		//Procedural Box
		std::vector<GLfloat> boxVerts;
		std::vector<GLfloat> boxNorms;
		std::vector<GLfloat> boxTex;

		//texture
		GLuint texture;
	
};
#endif 

