#include <iostream>
#include <fstream>
#include <string>

graphMST::graphMST():
vertexCount(0),
edgeCount(0),
title("")
{
  edges = NULL;
  mst = NULL;
}

graphMST::~graphMST()
{
  if(edges != NULL) {
     for(int i = 0; i < edgeCount; i++) {
       delete [] edges[i];
     }
  }

  if(msg != NULL) {
    for(int i = 0; i < vertexCount; i++) {
      delete [] mst[i];
    }
  }
}

bool graphMST::readEdges(const std::string fileName)
{
  std::ifstream inFile(fileName.c_str());
  if(!inFile.is_open())
    return false;
  //get title, vertex and edge count
  std::getline(inFile, title);
  inFile >> vertexCount >> edgeCount;

  if(vertexCount < minVertices) {
    std::cout << "readEdges: Error, invalid vertex count\n";
    return false;
  }
  if(edgeCount < minEdges) {
    std::cout << "readEdges: Error, invalid edge count\n";
    return false;
  }

  //create min spanning tree array
  mst = new int*[vertexCount];
  for(int i = 0; i < edgeCount; i++)
    mst[i] = new int[3];

  //create edge array
  edges = new int*[edgeCount];
  for(int i = 0; i < edgeCount; i++)
    edges[i] = new int[3];

  //loop through vertices and weights
  int home, to, weight;
  inFile >> home >> to >> weight;
  while(inFile) {

    inFile >> home >> to >> weight;
  }
}

int graphMST::getVertexCount() const
{
  return vertexCount;
}

int graphMST::getEdgeCount() const
{
  return edgeCount;
}

void graphMST::printMST() const
{

}

std::string graphMST::getTitle() const
{

}

void graphMST::printEdges() const
{

}

void graphMST::kruskals()
{

}
