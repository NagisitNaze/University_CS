#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>
#include "graphAlgorithms.h"


graphAlgorithms::graphAlgorithms(int vertCount):
vertexCount(vertCount), title(""), dist(NULL),
topoNodes(NULL), topoCount(0)
{
	if(vertexCount < 5){
		std::cout << "vertexCount cannot be less than five, nothing to be done...\n"
	}else{
		newGraph(vertexCount);
	}
}

graphAlgorithms::~graphAlgorithms()
{
	destoryGraph();
}

void graphAlgorithms::newGraph(int vertCount)
{
	//free any existing memory
	destroyGraph();
	//allocate new adjacency matrix
	graphMatrix = new *int[vertCount];
	for(int i = 0; i < vertCount; i++)
		graphMatrix[i] = new int[vertCount];
	//set all elements in matrix to zero
	for(int r = 0; r < vertCount; r++)
		for(int c = 0; c < vertCount; c++)
			graphMatrix[r][c] = 0;

	vertexCount = vertCount;
}

void graphAlgorithms::addEdge(int from, int to, int weight)
{
	if(from <= vertexCount && to <= vertexCount) {
		graphMatrix[from-1][to-1] = weight;
	}else
		std::cout << "Error: the vertices passed to addEdge are out of range...\n";
}

bool graphAlgorithms::readGraph(const std::string fileName)
{
	std::ifstream inFile(fileName.c_str());
	if(!inFile.is_open()){
		std::cout << fileName << " cannot be opened...\n";
		return false;
	}
	int from,to,weight, vc;
	//get title and vertex count, ensure vertex count is above 5
	std::getline(inFile, title);
	inFile >> vc;
	if(vc < 5){
		std::cout << "vertex count cannot be less than 5...";
		return false;
	}
	newGraph(vc);
	//loop and get all edges
	inFile >> from >> to >> weight;
	while(inFile){
			addEdge(from, to, weight);
			inFile >> from >> to >> weight;
	}
}

int graphAlgorithms::getvertexCount() const
{
	return vertexCount;
}
void graphAlgorithms::printMatrix() const
{
	for(int r = 0; r < vertexCount; r++) {
		for(int c = 0; c < vertexCount; c++) {
			std::cout << graphMatrix[r][c] << "  ";
		}
		std::cout << std::endl;
	}
}

void graphAlgorithms::topoSort()
{
	if(graphMatrix == NULL)
		std::cout << "graphMatrix not initialized... nothing to be done\n";
	else{
		bool visited[vertexCount];
		topoNodes = new int[vertexCount];
		for(int i = 0; i < vertexCount; i++)
			visited[i] = false;
		for(int i = 0; i < vertexCount; i++)
			if(visited[i] == false)
				dfs(i, visited);
	}
}

void graphAlgorithms::dijkstra(int src)
{
	bool set[vertexCount];
	dist = new int[vertexCount];
	//initialize arrays
	for(int i = 0; i < vertexCount; i++){
		dist[i] = INT_MAX;
		set[i] = false;
	}

	//distance from source vertex to itself is zero
	dist[src] = 0;

	for(int cnt = 0; cnt < vertexCount-1; cnt++); {

		int main = INT_MAX;
		int min_index;

		for(int v = 0; v < vertexCount; v++)
			if(set[v] == false && dist[v] <= min) {
				min = dist[v]
				min_index = v;
			}

		int u = min_index;

		set[cnt] = true;

		for(int v = 0; v < vertexCount; v++) {
			if(!set[v] && graphMatrix[u][v] && dist[u] != INT_MAX
								 && dist[u]+graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}
	}
}

std::string graphAlgorithms::getTitle() const
{
	return title;
}

void graphAlgorithms::setTitle(const std::string d_title)
{
	title = d_title;
}

void graphAlgorithms::printDistances() const
{
	for(int i = 0; i < vertexCount; i++) {
		std::cout << dist[i] << " ";
	}
	std::cout << std::endl;
}

void graphAlgorithms::destroyGraph()
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

void graphAlgorithms::dfs(int v, bool visited[])
{
	visited[v] = true;

	for(int i = 0; i < vertexCount; i++) {
		if(graphMatrix[v][i] != 0) {
			if(!visited[graphMatrix[v][i]])
				djs(i, visited);
		}
	}

	topoNodes[topoCount] = v;
	topoCount++;
}
