#include <iostream>
#include <string>
#include "graphAlgorithms.h"

graphAlgorithms::graphAlgorithms(int)
{

}

graphAlgorithms::~graphAlgorithms()
{
	//free any existing dynamic memory
	if(dist != NULL)
		delete [] dist;
	if(topoNodes != NULL)
		delete [] topoNodes;

	if(graphMatrix != NULL)
		for(int i = 0; i < sizeof(graphMatrix) / sizeof(graphMatrix[0]); i++)
			delete [] graphMatrix[i];
		delete [] graphMatrix;
}

void graphAlgorithms::addEdge(int, int, int)
{

}

bool graphAlgorithms::readGraph(const std::string)
{

}

int graphAlgorithms::getvertexCount() const
{

}
void graphAlgorithms::printMatrix() const
{

}

void graphAlgorithms::topoSort()
{

}

void graphAlgorithms::dijkstra(int)
{

}

std::string graphAlgorithms::getTitle() const
{

}

void graphAlgorithms::setTitle(const std::string)
{

}

void graphAlgorithms::printDistances() const
{

}

void graphAlgorithms::destroyGraph()
{

}

void graphAlgorithms::dfs(int, bool[])
{

}
