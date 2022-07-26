#pragma once
#include"Task.h"
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::complex;
using std::cout;
using std::endl;
using std::ofstream;
using std::vector;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_clock;

// The size of the image to generate.
const int WIDTH = 1920;
const int HEIGHT = 1200;

// The number of times to iterate before we assume that a point isn't in the
// Mandelbrot set.
const int MAX_ITERATIONS = 500;

// The image data.
typedef std::array <std::array < uint32_t, WIDTH>, HEIGHT> Array2D;
extern Array2D image;//made public so that it doesnt have to be passed through functions and can be accessed by the other classes

class Mandlebrot : public Task
{
public:
	Mandlebrot(double left, double right, double top, double bottom, int sliceNumY, int sliceNumX, int sliceAmountX, int sliceAmountY, int colourBack, int colourFront);
	void run();
	void compute_mandelbrot();

private:
	//takes in all the variables within the constructor parameter and saves them
	double left, right, top, bottom;
	int sliceNumX, sliceNumY, sliceAmountX, sliceAmountY;
	int colourBack, colourFront;
};

