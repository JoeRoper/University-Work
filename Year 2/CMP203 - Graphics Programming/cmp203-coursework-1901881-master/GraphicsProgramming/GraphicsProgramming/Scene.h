// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Input.h"
#include <stdio.h>
#include "math.h"
// Further includes should go here:
#include "SOIL.h"
#include <vector>

//My Own Includes
#include "Camera.h"
#include "SkyBox.h"
#include "Model.h"
#include "Texture.h"
#include "Light.h"

/*
remove imposter texture stuff
remove fence stuff
remove mirror stuff
*/

class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	void sceneMake();
	//Slabs
	void slabsRender();
	//Planes
	void planesRender();
	void windowRender();
	//cafe
	void cafeSideWallLeftCreate();
	void cafeSideWallRightCreate();
	void cafeRender();

	void bathroomRender();

	void streetLampCreate();
	void streetLampRender();

	void tableCreate();

	void chairCreate();

	void tableSetCreate();
	void tableSetRender();

	void doorCreate();
	void doorRender();

	// For access to user input.
	Input* input;

	//For access to created classes
	Camera* camera;
	SkyBox* skybox;
	Model* model;
	Texture texture;
	Light light;
	//Texture* texture;
	//Shape* shape;
	Shape lightTest = Shape(4);

	//slab
	Shape slab1 = Shape(4);

	//Planes
	Shape plane1 = Shape(6);
	Shape plane2 = Shape(7);
	Shape plane3 = Shape(5);
	Shape plane4 = Shape(5);
	Shape plane5 = Shape(7);
	Shape plane6 = Shape(11);
	Shape plane7 = Shape(8);
	Shape plane8 = Shape(12);

	//cafe
	Shape sideWalls1 = Shape(11);
	Shape sideWalls2 = Shape(11);
	Shape sideWalls3 = Shape(11);
	Shape sideWalls4 = Shape(11);
	Shape sideLampWallsOff = Shape(10);
	Shape sideLampWallsOn = Shape(9);
	Shape sideWalls6 = Shape(11);

	Shape backWalls1 = Shape(11);
	Shape backLampWallsOff = Shape(10);
	Shape backLampWallsOn = Shape(9);
	Shape backWalls3 = Shape(11);

	Shape frontWoodWalls1 = Shape(11);
	Shape frontWoodWalls2 = Shape(11);
	Shape frontWoodWalls3 = Shape(11);
	Shape frontWoodWalls4 = Shape(11);
	Shape frontWoodWalls5 = Shape(11);
	Shape frontLampWallsOff = Shape(10);
	Shape frontLampWallsOn = Shape(9);

	//Bathroom
	Shape bathroomFrontBackWalls = Shape(11);
	Shape bathroomSideWall = Shape(11);
	Shape bathroomCeilingPlane = Shape (11);
	Shape bathroomCabinet = Shape(11);
	Shape bathroomCabinetBottom = Shape(11);
	Shape bathroomLampOff = Shape(10);
	Shape bathroomLampOn = Shape(9);


	//Streetlamp
	Shape streetLampWood1 = Shape(11);
	Shape streetLampWood2 = Shape(11);
	Shape streetLampOff = Shape(10);
	Shape streetLampOn = Shape(9);

	//Table
	Shape tableLeg = Shape(11);
	Shape tableTop = Shape(11);
	Shape tableImposter = Shape(15);
	GLuint textureImposter;
	//Chair
	Shape chairBase = Shape(11);
	Shape chairSeat = Shape(11);
	//Fence
	Shape fenceBase = Shape(11);
	Shape fenceSide = Shape(11);

	Shape doorTop = Shape(14);
	Shape doorBottom = Shape(15);

	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	bool wireframe = true;

	//Door
	bool doorShut = true;
	float doorRotate1;
	float doorRotate2;

	//Lamp Lights
	bool lampLights = true;

	//lighting
	bool lighting = true;
};

#endif
