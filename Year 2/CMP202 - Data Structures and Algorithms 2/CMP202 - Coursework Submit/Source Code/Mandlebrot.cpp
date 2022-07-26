#include "Mandlebrot.h"

Mandlebrot::Mandlebrot(double left, double right, double top, double bottom, int sliceNumX, int sliceNumY, int sliceAmountX, int sliceAmountY, int colourBack, int colourFront)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->sliceNumX = sliceNumX;
	this->sliceNumY = sliceNumY;
	this->sliceAmountX = sliceAmountX;
	this->sliceAmountY = sliceAmountY;
	this->colourBack = colourBack;
	this->colourFront = colourFront;
}

void Mandlebrot::run()
{
	compute_mandelbrot();
}

void Mandlebrot::compute_mandelbrot()
{
	//calculates where it should compute the image in the x and y depending on the parameters set by the user
	size_t startX = ((WIDTH / sliceAmountX) * (sliceNumX -1));
	size_t endX = ((WIDTH / sliceAmountX) * (sliceNumX));

	size_t startY = ((HEIGHT / sliceAmountY) * (sliceNumY -1));
	size_t endY = ((HEIGHT / sliceAmountY) * (sliceNumY));

	//makes sure that the last slice calculates the whole image
	if (sliceNumX == sliceAmountX)
	{
		endX = WIDTH;
	}
	if (sliceNumY == sliceAmountY)
	{
		endY = HEIGHT;
	}

	for (size_t y = startY; y < endY; ++y)
	{
		for (size_t x = startX; x < endX; ++x)
		{
			// Work out the point in the complex plane that
			// corresponds to this pixel in the output image.
			complex<double> c(left + (x * (right - left) / WIDTH),
				top + (y * (bottom - top) / HEIGHT));

			// Start off z at (0, 0).
			complex<double> z(0.0, 0.0);

			// Iterate z = z^2 + c until z moves more than 2 units
			// away from (0, 0), or we've iterated too many times.
			int iterations = 0;
			while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
			{
				z = (z * z) + c;

				++iterations;
			}

			if (iterations == MAX_ITERATIONS)
			{		
				image[y][x] = colourFront; 
			}
			else
			{
				image[y][x] = colourBack; 
			}
		}
	}
}
