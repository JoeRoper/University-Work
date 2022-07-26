#include "Scene.h"

// Scene constructor, initilises OpenGL
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	

	// Initialise scene variables
	//Camera
	camera = new Camera(in);
	camera->setPosition(30, 4, 10);
	camera->setRotation(0, 0, 0);
	//Skybox
	skybox = new SkyBox(13);
	skybox->setCamera(camera);
	//Model
	model = new Model();
	
	sceneMake();
}

void Scene::handleInput(float dt)
{
	// Handle user input

	//Camera
	camera->keyboardInput(dt);
	camera->mouseInput(dt, width, height);
	
	
	//Wireframe Mode
	if (input->isKeyDown('g'))
	{
		wireframe = !wireframe;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		input->setKeyUp('g');
	}
	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	//Doors Open & Close
	if (input->isKeyDown('f'))
	{
		doorShut = !doorShut;
		doorRotate1 = 270;
		doorRotate2 = 90;
		input->setKeyUp('f');
	}
	if (doorShut)
	{
		doorRotate1 = 0;
		doorRotate2 = 0;
	}

	//Lamp Lights
	if (input->isKeyDown('h'))
	{
		light.enableLight(0);
		light.enableLight(1);
		light.enableLight(2);
		light.enableLight(3);
		light.enableLight(5);
		light.enableLight(6);
		light.enableLight(7);
		
		lampLights = !lampLights;
		input->setKeyUp('h');
	}
	if (lampLights)
	{
		light.disableLight(0);
		light.disableLight(1);
		light.disableLight(2);
		light.disableLight(3);
		light.disableLight(5);
		light.disableLight(6);
		light.disableLight(7);
	}
}

void Scene::update(float dt)
{
	// Calculate FPS for output
	calculateFPS();

	//Class updates
	camera->update();
	skybox->update();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(camera->gluLookAtArray[0], camera->gluLookAtArray[1], camera->gluLookAtArray[2], camera->gluLookAtArray[3], camera->gluLookAtArray[4], camera->gluLookAtArray[5], camera->gluLookAtArray[6], camera->gluLookAtArray[7], camera->gluLookAtArray[8]);
	skybox->renderNew();
	// Render geometry/scene here -------------------------------------
	
	//////////////////Scene//////////////////////
	//Lights
	light.renderLight0();
	light.renderLight1();
	light.renderLight2();
	light.renderLight3();
	light.renderLight4();
	light.renderLight5();
	light.renderLight6();
	light.renderLight7();
	///////////////////////////
	
	slabsRender();
	cafeRender();
	bathroomRender();
	streetLampRender();
	tableSetRender();
	
	//render last for blending
	planesRender();
	doorRender();
	windowRender();
	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::sceneMake()
{
	slab1.slabCreate(10);

	plane1.planeCreate(10, 10);//small stone plane
	plane2.planeCreate(10, 10);//small grass plane
	plane3.planeCreate(20, 8);//cobble road
	plane4.planeCreate(28, 30);//large cobble plane
	plane5.planeCreate(18, 20);//large grass plane
	plane6.planeCreate(20, 12);//cafe wood floor
	plane7.planeCreate(8, 12);//cafe bathroom floor
	plane8.planeCreate(11, 4);//window

	//Building the walls
	sideWalls1.proceduralBoxCreate(1, 6, 12);
	sideWalls2.proceduralBoxCreate(1, 2, 7);
	sideWalls3.proceduralBoxCreate(1, 2, 2);
	sideWalls4.proceduralBoxCreate(1, 4, 12);

	sideLampWallsOff.proceduralBoxCreate(1, 1, 12);
	sideLampWallsOn.proceduralBoxCreate(1, 1, 12);
	sideWalls6.proceduralBoxCreate(1, 2, 12);

	backWalls1.proceduralBoxCreate(19, 6, 1);
	backLampWallsOff.proceduralBoxCreate(19, 1, 1);
	backLampWallsOn.proceduralBoxCreate(19, 1, 1);
	backWalls3.proceduralBoxCreate(19, 2, 1);

	frontWoodWalls1.proceduralBoxCreate(19, 3, 1);
	frontWoodWalls2.proceduralBoxCreate(6, 4, 1);
	frontWoodWalls3.proceduralBoxCreate(2, 2, 1);
	frontWoodWalls4.proceduralBoxCreate(11, 1, 1);
	frontWoodWalls5.proceduralBoxCreate(2, 6, 1);

	frontLampWallsOff.proceduralBoxCreate(19, 1, 1);
	frontLampWallsOn.proceduralBoxCreate(19, 1, 1);

	//Bathroom
	bathroomFrontBackWalls.proceduralBoxCreate(7, 6, 1);
	bathroomSideWall.proceduralBoxCreate(1, 6, 12);
	bathroomCeilingPlane.planeCreate(7, 12);
	bathroomCabinet.proceduralBoxCreate(1, 3, 3);
	bathroomCabinetBottom.proceduralBoxCreate(1, 1, 3);
	bathroomLampOn.proceduralBoxCreate(1,1,3);
	bathroomLampOff.proceduralBoxCreate(1,1,3);

	//streetlamp
	streetLampWood1.proceduralBoxCreate(1, 7, 1);
	streetLampWood2.proceduralBoxCreate(1, 1, 1);
	streetLampOff.proceduralBoxCreate(1, 1, 1);
	streetLampOn.proceduralBoxCreate(1, 1, 1);

	//table
	tableLeg.proceduralBoxCreate(1, 2, 1);
	tableTop.planeCreate(2, 2);
	tableTop.planeCreate(1, 1);

	//chair
	chairBase.proceduralBoxCreate(2,2,1);
	chairSeat.proceduralBoxCreate(2,1,1);

	//fence
	fenceBase.proceduralBoxCreate(1, 2, 1);
	fenceSide.proceduralBoxCreate(2, 1, 1);

	//lighttest
	lightTest.proceduralBoxCreate(1, 1, 1);
}

void Scene::slabsRender()
{
	glPushMatrix();
	glTranslatef(0, 0, 4);
	slab1.slabRender();
	glPushMatrix();
	glTranslatef(0,0,10);
	slab1.slabRender();
	glPopMatrix();
	glTranslatef(18, 0, 30);
	glRotatef(90,0,1,0);
	slab1.slabRender();
	glPopMatrix();
}

void Scene::planesRender()
{
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//Stone + small grass plane
	glPushMatrix();
	glTranslatef(-1, 0, -7);
	plane1.planeRender();
	glPushMatrix();
	glTranslatef(10, 0, 0);
	plane2.planeRender();
	glPopMatrix();
	glPopMatrix();

	//cobble road
	glPushMatrix();
	glTranslatef(-1, 0, 5);
	plane3.planeRender();
	glPopMatrix();

	//large cobble plane
	glPushMatrix();
	glTranslatef(19,0,5);
	plane4.planeRender();
	glPopMatrix();

	//large grass plane
	glPushMatrix();
	glTranslatef(-1, 0, 15);
	plane5.planeRender();
	glPopMatrix();

	//bathroom floor
	glPushMatrix();
	glTranslatef(39, 0, -7);
	plane7.planeRender();
	glPopMatrix();
	glPopMatrix();

	//cafe floors
	glPushMatrix();
	glTranslatef(19,0,-7);
	plane6.planeRender();
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	glTranslatef(0, 8, 0);
	plane6.planeRender();
	glPopMatrix();
	glPopMatrix();

}

void Scene::windowRender()
{
	//window
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glRotatef(90, 1, 0, 0);
	glTranslatef(26, 5, -4.5);
	plane8.planeRender();
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Scene::cafeSideWallLeftCreate()
{
	glPushMatrix();
	glTranslatef(19, -0.5, -7);
	sideWalls1.proceduralBoxRender();//main 1
	glPushMatrix();
	glTranslatef(0, 6, 0);
	if (lampLights)
	{
		sideLampWallsOff.proceduralBoxRender();//lamp
	}
	else if (!lampLights)
	{
		sideLampWallsOn.proceduralBoxRender();//lamp
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 7, 0);
	sideWalls6.proceduralBoxRender();//top
	glPopMatrix();
	glPopMatrix();
}

void Scene::cafeSideWallRightCreate()
{
	glPushMatrix();
	glTranslatef(38, -0.5, -7);
	sideWalls2.proceduralBoxRender();//main 1
	glPushMatrix();
	glTranslatef(0, 0, 9);
	sideWalls3.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 2, 0);
	sideWalls4.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 6, 0);
	if (lampLights)
	{
		sideLampWallsOff.proceduralBoxRender();//lamp
	}
	else if (!lampLights)
	{
		sideLampWallsOn.proceduralBoxRender();//lamp
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 7, 0);
	sideWalls6.proceduralBoxRender();//top
	glPopMatrix();
	glPopMatrix();
}

void Scene::cafeRender()
{
	cafeSideWallLeftCreate();
	cafeSideWallRightCreate();

	glPushMatrix();
	glTranslatef(20, -0.5, -7);
	glPushMatrix();
	backWalls1.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 6, 0);
	if (lampLights)
	{
		backLampWallsOff.proceduralBoxRender();//lamp
	}
	else if (!lampLights)
	{
		backLampWallsOn.proceduralBoxRender();//lamp
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 7, 0);
	backWalls3.proceduralBoxRender();
	glPopMatrix();
	glPopMatrix();


	//frontwall
	glPushMatrix();
	glTranslatef(20, -0.5, 4);
	glPushMatrix();
	glTranslatef(0, 6, 0);
	frontWoodWalls1.proceduralBoxRender();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	frontWoodWalls2.proceduralBoxRender();
	glPopMatrix();

	glPushMatrix();
	frontWoodWalls3.proceduralBoxRender();
	glPushMatrix();
	glTranslatef(4, 0, 0);
	frontWoodWalls3.proceduralBoxRender();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 0, 0);
	frontWoodWalls4.proceduralBoxRender();
	glPushMatrix();
	glTranslatef(0, 5, 0);
	frontWoodWalls4.proceduralBoxRender();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17, 0, 0);
	frontWoodWalls5.proceduralBoxRender();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6, 0);
	if (lampLights)
	{
		frontLampWallsOff.proceduralBoxRender();//lamp
	}
	else if (!lampLights)
	{
		frontLampWallsOn.proceduralBoxRender();//lamp
	}
	glPopMatrix();


	glPopMatrix();
}

void Scene::bathroomRender()
{
	glPushMatrix();
	glTranslatef(39, -0.5, -7);
	glPushMatrix();
	bathroomFrontBackWalls.proceduralBoxRender();
	glPushMatrix();
	glTranslatef(0, 0, 11);
	bathroomFrontBackWalls.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(7, 0, 0);
	bathroomSideWall.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 6.5, 0);
	bathroomCeilingPlane.planeRender();
	glPopMatrix();
	glPopMatrix();
	glTranslatef(6, 0, 6);
	bathroomCabinet.proceduralBoxRender();
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	bathroomCabinetBottom.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 3, 0);
	if (lampLights)
	{
		bathroomLampOff.proceduralBoxRender();
	}
	else if (!lampLights)
	{
		bathroomLampOn.proceduralBoxRender();
	}
	glPopMatrix();
	glPopMatrix();

}

void Scene::streetLampCreate()
{
	glPushMatrix();
	glTranslatef(1.75, 0.5, 3.75);
	glPushMatrix();
	glScalef(0.5, 1, 0.5);
	glPushMatrix();
	streetLampWood1.proceduralBoxRender();//base
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 6, 3);
	streetLampWood2.proceduralBoxRender();//hang
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,7,0.5);
	glRotatef(90, 1, 0, 0);
	glScalef(0.5, 1, 0.5);
	streetLampWood2.proceduralBoxRender();//top
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, 5, 1.25);//lamp
	if (lampLights)
	{
		streetLampOff.proceduralBoxRender();
	}
	else if(!lampLights)
	{
		streetLampOn.proceduralBoxRender();
	}
	glPopMatrix();
	
	glPopMatrix();
}

void Scene::streetLampRender()
{
	glPushMatrix();
	streetLampCreate();
	glPushMatrix();
	glTranslatef(14, 0, 0);
	streetLampCreate();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-4, 0, -18);
	streetLampCreate();
	glPushMatrix();
	glTranslatef(-14, 0, 0);
	streetLampCreate();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Scene::tableCreate()
{
	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glPushMatrix();
	glScalef(0.5, 1, 0.5);
	tableLeg.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.75,2.51,-0.75);
	glPushMatrix();
	tableTop.planeRender();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Scene::chairCreate()
{
	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glPushMatrix();
	glScalef(1, 1, 0.5);
	chairBase.proceduralBoxRender();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,0.5);
	chairSeat.proceduralBoxRender();
	glPopMatrix();
	glPopMatrix();
}

void Scene::tableSetCreate()
{
	glPushMatrix();
	glPushMatrix();
	glTranslatef(45, 0, 1);
	glRotatef(270, 0, 1, 0);
	chairCreate();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42, 0, 1.75);
	tableCreate();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(39.5, 0, 3);
	glRotatef(90, 0, 1, 0);
	chairCreate();
	glPopMatrix();
	glPopMatrix();
}

void Scene::tableSetRender()
{
	int z = 0;
	for (int i = 0; i < 5; i++)
	{
		z += 6;
		glPushMatrix();
		glTranslatef(0, 0, z);
		tableSetCreate();
		glPushMatrix();
		glTranslatef(-8, 0, 0);
		tableSetCreate();
		glPopMatrix();
		glPopMatrix();
	}
}

void Scene::doorCreate()
{
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glScalef(0.5, 1, 0.1);
	doorBottom.renderCube();
	glPushMatrix();
	glTranslatef(0, 1, 0);
	doorTop.renderCube();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glPopMatrix();
}

void Scene::doorRender()
{
	
	//Cafe Doors
	glPushMatrix();
	glTranslatef(22, 0, 4.9);
	glRotatef(doorRotate1, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	doorCreate();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, 4.9);
	glRotatef(180, 0, 1, 0);
	glRotatef(doorRotate2, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	doorCreate();
	glPopMatrix();

	//bathroom doors
	glPushMatrix();
	glTranslatef(43, 0, -22);
	glRotatef(270, 0, 1, 0);
	glPushMatrix();
	glTranslatef(22, 0, 4.9);
	glRotatef(doorRotate1, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	doorCreate();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 0, 4.9);
	glRotatef(180, 0, 1, 0);
	glRotatef(doorRotate2, 0, 1, 0);
	glTranslatef(0.5, 0, 0);
	doorCreate();
	glPopMatrix();
	glPopMatrix();

}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);				// White Background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	input->setMousePos(width / 2, height / 2);//user created for mouse input with camera
	glutWarpPointer(width / 2, height / 2);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
