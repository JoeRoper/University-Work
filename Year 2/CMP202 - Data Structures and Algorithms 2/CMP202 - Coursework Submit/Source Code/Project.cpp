#include "Project.h"

void Project::Setup()
{
	cout << "How many times would you like to slice in the X direction?" << endl;
	cin >> sliceAmountX;
	cout << "How many times would you like to slice in the Y direction?" << endl;
	cin >> sliceAmountY;

	//if the input is 0 it sets it to 1 so that the mandlebrot can run
	if (sliceAmountX == 0) {
		sliceAmountX = 1;
	}
	if (sliceAmountY == 0) {
		sliceAmountY = 1;
	}

	cout << "What would you like the background colour to be" << endl;
	cout << "1 - White" << endl;
	cout << "2 - Black" << endl;
	cout << "3 - Red" << endl;
	cout << "4 - Green" << endl;
	cout << "5 - Blue" << endl;
	cout << "6 - Orange" << endl;
	cout << "7 - Yellow" << endl;
	cout << "8 - Purple" << endl;
	cin >> colourBack;

	colourBack = colourSwitch(colourBack);

	cout << "What would you like the foreground colour to be" << endl;
	cout << "1 - White" << endl;
	cout << "2 - Black" << endl;
	cout << "3 - Red" << endl;
	cout << "4 - Green" << endl;
	cout << "5 - Blue" << endl;
	cout << "6 - Orange" << endl;
	cout << "7 - Yellow" << endl;
	cout << "8 - Purple" << endl;
	cin >> colourFront;
	colourFront = colourSwitch(colourFront);
}

void Project::Run()
{
	Setup();

	// Start timing
	the_clock::time_point start = the_clock::now();

	//adds the mandlebrot task to the farm class based on the user input
	std::thread myThread(&Project::MandelBrot_Consumer,Project());
	for (int sliceNumY = 1; sliceNumY <= sliceAmountY; sliceNumY++)
	{
		for (int sliceNumX = 1; sliceNumX <= sliceAmountX; sliceNumX++)
		{
			f.add_task(new Mandlebrot(-2.0, 1.0, 1.125, -1.125, sliceNumX, sliceNumY, sliceAmountX, sliceAmountY, colourBack, colourFront));
		}
	}
	f.run();
	myThread.join();
	// Stop timing
	the_clock::time_point end = the_clock::now();

	// Compute the difference between the two times in milliseconds
	auto time_taken = duration_cast<milliseconds>(end - start).count();
	cout << "Computing the Mandelbrot set took " << time_taken << " ms." << endl;
}

void Project::write_tga()
{
	const char* filename = "MandlebrotImage.tga";
	ofstream outfile(filename, ofstream::binary);
	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // X origin
		0, 0, // Y origin
		WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
		HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char*)header, 18);
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t pixel[3] = {
				image[y][x] & 0xFF, // blue channel
				(image[y][x] >> 8) & 0xFF, // green channel
				(image[y][x] >> 16) & 0xFF, // red channel
			};
			outfile.write((const char*)pixel, 3);
		}
	}
	//makes sure that the whole image is wrote to the file 
	//by checking to see if the last pixel has been altered
	if (image[HEIGHT-1][WIDTH-1] != header[0])
	{
		writeBool = true;
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred at some point since we opened the file.
		cout << "Error writing to " << filename << endl;
		exit(1);
	}
}

void Project::MandelBrot_Consumer()
{
	//blocks the write file operation until the farm class has computed the mandlebrot
	int numcores = f.GetNumCores();
	std::unique_lock<std::mutex> lock(f.MandelMutex);
	while (f.GetThreadCounter() != numcores)
	{
		f.Mandel_Conditon.wait(lock);
	}
	while(!writeBool)
	{
		write_tga();
	}

}
int Project::colourSwitch(int colour)
{
	switch (colour) {
	case 1:
		return 0xFFFFFF;//white
		break;
	case 2:
		return 0x0000000;//black
		break;
	case 3:
		return 0xfc0303;//Red
		break;
	case 4:
		return 0x03fc20;//Green
		break;
	case 5:
		return 0x0328fc;//Blue
		break;
	case 6:
		return 0xfc6f03;//Orange
		break;
	case 7:
		return 0xe7fc03;//Yellow
		break;
	case 8:
		return 0x8c03fc;//Purple
		break;
	default:
		return 0x0000000;
	}
}

int main(int argc, char* argv[])
{
	Project projectObj;
	projectObj.Run();

	return 0;
}