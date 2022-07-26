#include "shape.h"

//Cube24
extern float normsCube24[] = {
	//Front
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	//Back
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	//Left
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	//Right
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	//Up
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	0, -1, 0,
	//Down
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0
};

extern float texcoordsCube24[] = {
	//Front
	0.25, 0.25,
	0.25, 0.5,
	0.5, 0.5,
	0.5, 0.25,
	//Back
	1, 0.5,
	1, 0.25,
	0.75, 0.25,
	0.75, 0.5,
	//Left
	0, 0.25,
	0, 0.5,
	0.25, 0.5,
	0.25, 0.25,
	//Right
	0.5, 0.25,
	0.5, 0.5,
	0.75, 0.5,
	0.75, 0.25,
	//Up
	0.25, 0,
	0.25, 0.25,
	0.5, 0.25,
	0.5, 0,
	//Down
	0.25, 0.5,
	0.25, 0.75,
	0.5, 0.75,
	0.5, 0.5
};

extern float texcoordsCube4[] = {
	//Front
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	//Back
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	//Left
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	//Right
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	//Up
	0, 0,
	0, 1,
	1, 1,
	1, 0,
	//Down
	0, 0,
	0, 1,
	1, 1,
	1, 0,
};

extern float vertsCube24[] = {
	//Front
	-1.0,  0.5, 1.0,	// Vertex #7
	-1.0, -0.5, 1.0,	// Vertex #4
	1.0, -0.5, 1.0,		// Vertex #5
	1.0,  0.5, 1.0,		// Vertex #6

	//Back
	-1.0, -0.5, -1.0,	// Vertex #0
	-1.0,  0.5, -1.0,	// Vertex #3
	1.0,  0.5, -1.0,	// Vertex #2
	1.0, -0.5, -1.0,	// Vertex #1

	//Left	
	-1.0,  0.5, -1.0,	// Vertex #3
	-1.0, -0.5, -1.0,	// Vertex #0
	-1.0, -0.5, 1.0,	// Vertex #4
	-1.0,  0.5, 1.0,	// Vertex #7

	//Right
	1.0,  0.5, 1.0,		// Vertex #6
	1.0, -0.5, 1.0,		// Vertex #5
	1.0, -0.5, -1.0,	// Vertex #1
	1.0,  0.5, -1.0,	// Vertex #2

	//Up
	-1.0,  0.5, -1.0,	// Vertex #3
	-1.0,  0.5, 1.0,	// Vertex #7
	1.0,  0.5, 1.0,		// Vertex #6
	1.0,  0.5, -1.0,	// Vertex #2

	//Down
	-1.0, -0.5, 1.0,	// Vertex #4
	-1.0, -0.5, -1.0,	// Vertex #0
	1.0, -0.5, -1.0,	// Vertex #1
	1.0, -0.5, 1.0,		// Vertex #5

};


Shape::Shape(GLuint texture)
{
	this->texture = texture;
}

Shape::~Shape()
{
}


void Shape::renderCube()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertsCube24);
	glNormalPointer(GL_FLOAT, 0, normsCube24);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoordsCube24); //4 for single texture, 24 for tMap

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawArrays(GL_QUADS, 0, 24);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::slabCreate(int slabNum)
{
	double x = -3;
	double y = 0.5;
	double z = 1;
	double scale = 2;
	
	for (int i = 0; i < slabNum; i++)
	{
		x = x + 2;
		//////////////////Front////////////////////
		//Verts
		slabVerts.push_back(x); slabVerts.push_back(y); slabVerts.push_back(z); 
		slabVerts.push_back(x); slabVerts.push_back(-y); slabVerts.push_back(z); 
		slabVerts.push_back(x+scale); slabVerts.push_back(-y); slabVerts.push_back(z); 
		slabVerts.push_back(x+scale); slabVerts.push_back(y); slabVerts.push_back(z); 
		//Norms
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(1);
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(1);
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(1);
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(1);
		//TexCoords
		slabTex.push_back(0); slabTex.push_back(0); 
		slabTex.push_back(0); slabTex.push_back(1); 
		slabTex.push_back(1); slabTex.push_back(1); 
		slabTex.push_back(1); slabTex.push_back(0); 

		///////////////////Back/////////////////////
		//Verts
		slabVerts.push_back(x + scale); slabVerts.push_back(y); slabVerts.push_back(-z); //2
		slabVerts.push_back(x + scale); slabVerts.push_back(-y); slabVerts.push_back(-z); //1
		slabVerts.push_back(x); slabVerts.push_back(-y); slabVerts.push_back(-z); //0
		slabVerts.push_back(x); slabVerts.push_back(y); slabVerts.push_back(-z); //3
		
		//Norms
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(-1);
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(-1);
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(-1);
		slabNorms.push_back(0); slabNorms.push_back(0); slabNorms.push_back(-1);
		//TexCoords
		slabTex.push_back(0); slabTex.push_back(0);
		slabTex.push_back(0); slabTex.push_back(1);
		slabTex.push_back(1); slabTex.push_back(1);
		slabTex.push_back(1); slabTex.push_back(0);
		
		/////////////////////Up/////////////////////
		//Verts
		slabVerts.push_back(x); slabVerts.push_back(y); slabVerts.push_back(-z);
		slabVerts.push_back(x); slabVerts.push_back(y); slabVerts.push_back(z);
		slabVerts.push_back(x + scale); slabVerts.push_back(y); slabVerts.push_back(z);
		slabVerts.push_back(x + scale); slabVerts.push_back(y); slabVerts.push_back(-z);
		//Norms
		slabNorms.push_back(0); slabNorms.push_back(1); slabNorms.push_back(0);
		slabNorms.push_back(0); slabNorms.push_back(1); slabNorms.push_back(0);
		slabNorms.push_back(0); slabNorms.push_back(1); slabNorms.push_back(0);
		slabNorms.push_back(0); slabNorms.push_back(1); slabNorms.push_back(0);
		//TexCoords
		slabTex.push_back(0); slabTex.push_back(0);
		slabTex.push_back(0); slabTex.push_back(1);
		slabTex.push_back(1); slabTex.push_back(1);
		slabTex.push_back(1); slabTex.push_back(0);

		////////////////////Down////////////////////
		//Verts
		slabVerts.push_back(x); slabVerts.push_back(-y); slabVerts.push_back(z);//4
		slabVerts.push_back(x); slabVerts.push_back(-y); slabVerts.push_back(-z);//0
		slabVerts.push_back(x + scale); slabVerts.push_back(-y); slabVerts.push_back(-z);//1
		slabVerts.push_back(x + scale); slabVerts.push_back(-y); slabVerts.push_back(z);//5
		//Norms
		slabNorms.push_back(0); slabNorms.push_back(-1); slabNorms.push_back(0);
		slabNorms.push_back(0); slabNorms.push_back(-1); slabNorms.push_back(0);
		slabNorms.push_back(0); slabNorms.push_back(-1); slabNorms.push_back(0);
		slabNorms.push_back(0); slabNorms.push_back(-1); slabNorms.push_back(0);
		//TexCoords
		slabTex.push_back(0); slabTex.push_back(0);
		slabTex.push_back(0); slabTex.push_back(1);
		slabTex.push_back(1); slabTex.push_back(1);
		slabTex.push_back(1); slabTex.push_back(0);
	}

	/////////////////////Left/////////////////////////
	//Verts
	slabVerts.push_back(-1); slabVerts.push_back(y); slabVerts.push_back(-z);
	slabVerts.push_back(-1); slabVerts.push_back(-y); slabVerts.push_back(-z);
	slabVerts.push_back(-1); slabVerts.push_back(-y); slabVerts.push_back(z);
	slabVerts.push_back(-1); slabVerts.push_back(y); slabVerts.push_back(z);
	//Norms
	slabNorms.push_back(-1); slabNorms.push_back(0); slabNorms.push_back(0);
	slabNorms.push_back(-1); slabNorms.push_back(0); slabNorms.push_back(0);
	slabNorms.push_back(-1); slabNorms.push_back(0); slabNorms.push_back(0);
	slabNorms.push_back(-1); slabNorms.push_back(0); slabNorms.push_back(0);
	//TexCoords
	slabTex.push_back(0); slabTex.push_back(0);
	slabTex.push_back(0); slabTex.push_back(1);
	slabTex.push_back(1); slabTex.push_back(1);
	slabTex.push_back(1); slabTex.push_back(0);

	/////////////////////////Right////////////////////
	//Verts
	slabVerts.push_back(slabNum * 2 - 1); slabVerts.push_back(y); slabVerts.push_back(z);
	slabVerts.push_back(slabNum * 2 - 1); slabVerts.push_back(-y); slabVerts.push_back(z);
	slabVerts.push_back(slabNum * 2 - 1); slabVerts.push_back(-y); slabVerts.push_back(-z);
	slabVerts.push_back(slabNum * 2 - 1); slabVerts.push_back(y); slabVerts.push_back(-z);
	//Norms
	slabNorms.push_back(1); slabNorms.push_back(0); slabNorms.push_back(0);
	slabNorms.push_back(1); slabNorms.push_back(0); slabNorms.push_back(0);
	slabNorms.push_back(1); slabNorms.push_back(0); slabNorms.push_back(0);
	slabNorms.push_back(1); slabNorms.push_back(0); slabNorms.push_back(0);
	//TexCoords
	slabTex.push_back(0); slabTex.push_back(0);
	slabTex.push_back(0); slabTex.push_back(1);
	slabTex.push_back(1); slabTex.push_back(1);
	slabTex.push_back(1); slabTex.push_back(0);
	
}

void Shape::slabRender()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, slabVerts.data());
	glNormalPointer(GL_FLOAT, 0, slabNorms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, slabTex.data()); 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawArrays(GL_QUADS, 0, slabVerts.size()/3);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::planeCreate(int Width, int Depth)
{
	double y = -0.5;
	double scale = 1;
	
	for (int x = 0; x < Width; x++)
	{
		for (int z = 0; z < Depth; z++)
		{
			//Verts
			planeVerts.push_back(x); planeVerts.push_back(y); planeVerts.push_back(z);
			planeVerts.push_back(x); planeVerts.push_back(y); planeVerts.push_back(z + scale);
			planeVerts.push_back(x + scale); planeVerts.push_back(y); planeVerts.push_back(z + scale);
			planeVerts.push_back(x + scale); planeVerts.push_back(y); planeVerts.push_back(z);
			//Norms
			planeNorms.push_back(0); planeNorms.push_back(1); planeNorms.push_back(0);
			planeNorms.push_back(0); planeNorms.push_back(1); planeNorms.push_back(0);
			planeNorms.push_back(0); planeNorms.push_back(1); planeNorms.push_back(0);
			planeNorms.push_back(0); planeNorms.push_back(1); planeNorms.push_back(0);
			//TexCoords
			planeTex.push_back(0); planeTex.push_back(0);
			planeTex.push_back(0); planeTex.push_back(1);
			planeTex.push_back(1); planeTex.push_back(1);
			planeTex.push_back(1); planeTex.push_back(0);
		}
	}
}

void Shape::planeRender()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, planeVerts.data());
	glNormalPointer(GL_FLOAT, 0, planeNorms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, planeTex.data()); //4 for single texture, 24 for tMap

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawArrays(GL_QUADS, 0, planeVerts.size() / 3);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::proceduralBoxCreate(int Width, int Height, int Depth)
{
	double scale = 1;

	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			for (int z = 0; z < Depth; z++)
			{
				//////////////////Front////////////////////
				//Verts
				boxVerts.push_back(x); boxVerts.push_back(y + scale); boxVerts.push_back(z + scale);
				boxVerts.push_back(x); boxVerts.push_back(y); boxVerts.push_back(z + scale);
				boxVerts.push_back(x + scale); boxVerts.push_back(y); boxVerts.push_back(z + scale);
				boxVerts.push_back(x + scale); boxVerts.push_back(y + scale); boxVerts.push_back(z + scale);
				//Norms
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(1);
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(1);
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(1);
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(1);
				//TexCoords
				boxTex.push_back(0); boxTex.push_back(0);
				boxTex.push_back(0); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(0);

				///////////////////Back/////////////////////
				//Verts
				boxVerts.push_back(x + scale); boxVerts.push_back(y + scale); boxVerts.push_back(z); //2
				boxVerts.push_back(x + scale); boxVerts.push_back(y); boxVerts.push_back(z); //1
				boxVerts.push_back(x); boxVerts.push_back(y); boxVerts.push_back(z); //0
				boxVerts.push_back(x); boxVerts.push_back(y + scale); boxVerts.push_back(z); //3

				//Norms
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(-1);
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(-1);
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(-1);
				boxNorms.push_back(0); boxNorms.push_back(0); boxNorms.push_back(-1);
				//TexCoords
				boxTex.push_back(0); boxTex.push_back(0);
				boxTex.push_back(0); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(0);

				/////////////////////Left/////////////////////////
				//Verts
				boxVerts.push_back(x); boxVerts.push_back(y + scale); boxVerts.push_back(z);
				boxVerts.push_back(x); boxVerts.push_back(y); boxVerts.push_back(z);
				boxVerts.push_back(x); boxVerts.push_back(y); boxVerts.push_back(z + scale);
				boxVerts.push_back(x); boxVerts.push_back(y + scale); boxVerts.push_back(z + scale);
				//Norms
				boxNorms.push_back(-1); boxNorms.push_back(0); boxNorms.push_back(0);
				boxNorms.push_back(-1); boxNorms.push_back(0); boxNorms.push_back(0);
				boxNorms.push_back(-1); boxNorms.push_back(0); boxNorms.push_back(0);
				boxNorms.push_back(-1); boxNorms.push_back(0); boxNorms.push_back(0);
				//TexCoords
				boxTex.push_back(0); boxTex.push_back(0);
				boxTex.push_back(0); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(0);

				/////////////////////////Right////////////////////
				//Verts
				boxVerts.push_back(x + scale); boxVerts.push_back(y + scale); boxVerts.push_back(z + scale);
				boxVerts.push_back(x + scale); boxVerts.push_back(y); boxVerts.push_back(z + scale);
				boxVerts.push_back(x + scale); boxVerts.push_back(y); boxVerts.push_back(z);
				boxVerts.push_back(x + scale); boxVerts.push_back(y + scale); boxVerts.push_back(z);
				//Norms
				boxNorms.push_back(1); boxNorms.push_back(0); boxNorms.push_back(0);
				boxNorms.push_back(1); boxNorms.push_back(0); boxNorms.push_back(0);
				boxNorms.push_back(1); boxNorms.push_back(0); boxNorms.push_back(0);
				boxNorms.push_back(1); boxNorms.push_back(0); boxNorms.push_back(0);
				//TexCoords
				boxTex.push_back(0); boxTex.push_back(0);
				boxTex.push_back(0); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(0);

				/////////////////////Up/////////////////////
				//Verts

				boxVerts.push_back(x); boxVerts.push_back(y + scale); boxVerts.push_back(z);
				boxVerts.push_back(x); boxVerts.push_back(y + scale); boxVerts.push_back(z + scale);
				boxVerts.push_back(x + scale); boxVerts.push_back(y + scale); boxVerts.push_back(z + scale);
				boxVerts.push_back(x + scale); boxVerts.push_back(y + scale); boxVerts.push_back(z);
				//Norms
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				//TexCoords
				boxTex.push_back(0); boxTex.push_back(0);
				boxTex.push_back(0); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(0);

				////////////////////Down////////////////////
				//Verts
				boxVerts.push_back(x); boxVerts.push_back(y); boxVerts.push_back(z + scale);//4
				boxVerts.push_back(x); boxVerts.push_back(y); boxVerts.push_back(z);//0
				boxVerts.push_back(x + scale); boxVerts.push_back(y); boxVerts.push_back(z);//1
				boxVerts.push_back(x + scale); boxVerts.push_back(y); boxVerts.push_back(z + scale);//5
				//Norms
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				boxNorms.push_back(0); boxNorms.push_back(1); boxNorms.push_back(0);
				//TexCoords
				boxTex.push_back(0); boxTex.push_back(0);
				boxTex.push_back(0); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(1);
				boxTex.push_back(1); boxTex.push_back(0);
			}

		}
	}
}

void Shape::proceduralBoxRender()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, boxVerts.data());
	glNormalPointer(GL_FLOAT, 0, boxNorms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, boxTex.data()); //4 for single texture, 24 for tMap

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDrawArrays(GL_QUADS, 0, boxVerts.size() / 3);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}