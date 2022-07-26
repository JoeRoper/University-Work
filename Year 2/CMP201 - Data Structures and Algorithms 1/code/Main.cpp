#include "DijkstraAlgorithm.h"
#include "LeeAlgorithm.h"
#include <array>

int main()
{
	
	//9by9
	std::vector<std::vector<int>> map1 =
	{
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1,},
		}
	};

	//10by10
	std::vector<std::vector<int>> map2 =
	{
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		}
	};

	//11by11
	std::vector<std::vector<int>> map3 =
	{
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		}
	};



	DijkstraAlgorithm dijkstra;
	LeeAlgorithm lee;
	
	//test(room1);
	
	dijkstra.setSize(9);
	dijkstra.setMap(map1);
	dijkstra.runDijkstra(5);

	dijkstra.setSize(10);
	dijkstra.setMap(map2);
	dijkstra.runDijkstra(5);

	dijkstra.setSize(11);
	dijkstra.setMap(map3);
	dijkstra.runDijkstra(5);
	
	
	
	lee.setSize(9);
	lee.setMap(map1);
	lee.runLee(5,8,8);
	
	lee.setSize(10);
	lee.setMap(map2);
	lee.runLee(5, 9, 9);

	lee.setSize(11);
	lee.setMap(map3);
	lee.runLee(5, 10, 10);
	

	return 0;
}