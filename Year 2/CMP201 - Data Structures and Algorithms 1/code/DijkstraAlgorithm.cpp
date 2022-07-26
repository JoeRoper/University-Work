#include "DijkstraAlgorithm.h"

void DijkstraAlgorithm::setMap(vector2D map)
{
	this->map = map;
}

//Function to find the shortest distance from the vertices not in the path to the last path vertice
int DijkstraAlgorithm::minDistance()
{
	// Initialize min value 
	int min = INT_MAX;//creates an integer set to a high number which will be used to calculate if the path distance is acceptable
	int min_index;//used to return the path distance

	for (int x = 0; x < size; x++)//loops for the number of vertices in the graph
	{
		if (pathSetArray[x] == false && distanceArray[x] <= min)//if the value is not in the path already and is less than the minimum it runs the code underneath
		{
			min = distanceArray[x];//sets the minimum distance to the new one
			min_index = x;//sets the path distance and returns it
			return min_index;
		}
	}
}


//Function that prints out the data to the console window
void DijkstraAlgorithm::displayData()
{
	cout << "Vertex:				Distance:" << endl;
	for (int x = 0; x < size; x++)
	{
		cout << "-" << x << "-" << "				" << distanceArray[x] << endl;
	}

}

void DijkstraAlgorithm::dijkstra(int vertexSource)
{
	

	for (int i = 0; i < size; i++)//loops for the size of the graph
	{
		//pathSet[i] = false;//sets the whole array too false as no vertices have been visited
		//distance[i] = INT_MAX;//sets the array to equal infinity which will be subbed out for the true distances

		pathSetArray.push_back(false);
		distanceArray.push_back(INT_MAX);
	}

	distanceArray[vertexSource] = 0;//sets the start point as 0


	for (int count = 0; count < size - 1; count++)
	{

		int vertex = minDistance();//picks the shortest distance vertex and places it in the integer variable

		pathSetArray[vertex] = true;//sets the vertex just passed as true in the path array

		for (int x = 0; x < size; x++)
		{
			//updates a new vertex to have a shortest distance value if it is not in the pathSet array and is lessthan the current shortest distance
			if (!pathSetArray[x] && map[vertex][x] && distanceArray[vertex] != INT_MAX
				&& distanceArray[vertex] + map[vertex][x] < distanceArray[x])
			{
				distanceArray[x] = distanceArray[vertex] + map[vertex][x];//new shortest distance is the last one plus the new one 
			}
		}
	}

	displayData();//prints the new data to the console window

	for (int i = 0; i < size; i++)//loops for the size of the graph and clears data
	{

		pathSetArray.clear();
		distanceArray.clear();
	}
}


void DijkstraAlgorithm::runDijkstra(int repeat)
{
	for (int i = 0; i < repeat; i++)
	{
		// Start timing
		the_clock::time_point start = the_clock::now();
		dijkstra(0);
		// Stop timing
		the_clock::time_point end = the_clock::now();

		// Compute the difference between the two times in milliseconds
		auto time_taken = duration_cast<milliseconds>(end - start).count();
		timeSum += time_taken;
		//print out time taken
		cout << "It took " << time_taken << " ms.\n";

		times.push_back(time_taken);
		sort(times.begin(), times.end());
	}

	cout << "Time Median:" << times[repeat/2] << endl;
	cout << "Time Mean:" << (timeSum / repeat) << endl;
	cout << "Time Sum:" << timeSum << endl;
}
