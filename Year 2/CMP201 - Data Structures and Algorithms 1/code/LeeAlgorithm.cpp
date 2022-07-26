#include "LeeAlgorithm.h"


void LeeAlgorithm::setMap(vector2D map)
{
	this->map = map;
}

//Function to check if the next cell is accessible 
bool LeeAlgorithm::isOpen(int row, int column)
{
	//if row and collumn are between 0 and the size of the map and has not been visited 
	//it returns true as the cell is accesible
	if ((row >= 0) && (row < size) && (column >= 0) && (column < size)
		&& map[row][column] && !visited2D[row][column])
	{
		return true;
	}
	else //cell is outside the map, is blocked off or has been visited before
	{
		return false;
	}
}

void LeeAlgorithm::displayData(int min)
{
	//make display data function
	if (min != INT_MAX)
	{
		cout << "The shortest path from source to destination "
			"has length " << min << endl;
	}
	else
	{
		cout << "Destination can't be reached from given source" << endl;
	}
}

void LeeAlgorithm::leeAlgorithm(int startX, int startY, int endX, int endY)
{
	
	for (int j = 0; j < size; j++)
	{
		vector<bool> temp;
		for (int i = 0; i < size; i++)
		{
			temp.push_back(false);
			
		}
		visited2D.push_back(temp);
	}
	


	//memset(visited, false, sizeof visited);//function included in c++ library sets the whole array to false 


	//creating a vertex queue will be used to store the diff vertexes
	queue<Vertex> vertexQ;

	visited2D[startX][startY] = true;//sets the starting cell as visited
	vertexQ.push({ startX, startY, 0 });//adds the starting vertex onto the queue

	int min = INT_MAX; //sets variable to max which will be used to calculate the path distance

	while (!vertexQ.empty())//runs until the queue created is empty
	{
		Vertex node = vertexQ.front();//creates new vertex node and assigns it the front of queues data
		vertexQ.pop();//removes the data just assigned to the new vertex node

		//current X and Y will be used to represent the coordinates of the cell being used and looked at
		//distance represents the minimun distance from the cell being used and the source
		int currentX = node.x, currentY = node.y, distance = node.distance;

		// if destination is found, update min_dist and stop
		//if the current cell being looked at is the end destination it updates the minimum distance
		if (currentX == endX && currentY == endY)
		{
			min = distance;
			break;
		}

		for (int x = 0; x < 4; x++)
		{
			if (isOpen(currentX + row[x], currentY + column[x]))
			{
				visited2D[currentX + row[x]][currentY + column[x]] = true;//updates the visited array to assign the next cell as visited
				vertexQ.push({ currentX + row[x], currentY + column[x], distance + 1 });//adds the next cell to the queue
			}
		}
	}

	displayData(min);

	for (int i = 0; i < size; i++)//loops for the size of the graph
	{
		visited2D.clear();
	}
}

void LeeAlgorithm::runLee(int repeat, int targetX, int targetY)
{
	for (int i = 0; i < repeat; i++)
	{
		// Start timing
		the_clock::time_point start = the_clock::now();
		leeAlgorithm(0, 0, targetX, targetY);
		// Stop timing
		the_clock::time_point end = the_clock::now();

		// Compute the difference between the two times in milliseconds
		auto time_taken = duration_cast<milliseconds>(end - start).count();
		timeSum += time_taken;
		//print out time taken
		cout << "It took " << time_taken << " ms.\n";

		times.push_back(time_taken);
		sort(times.begin(),times.end());

	}

	cout << "Time Median:" << times[repeat/2] << endl;
	cout << "Time Mean:" << (timeSum/repeat) << endl;
	cout << "Time Sum:" << timeSum << endl;

}



