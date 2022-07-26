#pragma once
#include "Farm.h"
#include "Mandlebrot.h"
Array2D image;//saves the image calculated in the mandlebrot class to be used in the write file function
Farm f;//used to parralise the mandlebrot computation using the farm technique

class Project
{
public:
	void Setup();//allows the user to set the slice amounts for the image aswell as the colour
	void Run();
	void write_tga();
	int colourSwitch(int colour);//used to set the colour of the mandlebrot image based on the users specification
	void MandelBrot_Consumer();

private:
	int sliceAmountX, sliceAmountY;
	vector<thread> VectOfThreads;
	int colourBack, colourFront, counter;
	bool writeBool = false;
};

