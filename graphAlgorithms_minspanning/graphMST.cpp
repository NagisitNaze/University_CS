#include <iostream>
#include <fstream>
#include <string>
#include "graphMST.h"
#include "disjointSets.h"

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

  //loop through and place edges into edges array
  int cnt=0;
  inFile >> home >> to >> weight;
  while(inFile) {
    inFile >> edges[cnt][0] >> edges[cnt][1] >> edges[cnt][2];
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
  std::cout << "Min spanning tree:\n";
  for(int i = 0; i < vertexCount; i++) {
    std::cout << mst[0] << "  " << mst[1] << "  " << mst[2] << std::endl;
  }
}

std::string graphMST::getTitle() const
{
  return title;
}

void graphMST::printEdges() const
{
  std::cout << "Edges:\n";
  for(int i = 0; i < edgeCount; i++) {
    std::cout << edges[0] << "  " << edges[1] << "  " << edges[2] << std::endl;
  }
}

void graphMST::kruskals()
{
  disjointSets mst_union(vertexCount);

  for(int i = 0; i < edgeCount-1; i++) {
    int u = edges[0];
    int v = edges[1];
    if(mst_union.setFind(u) != mst_union.setFind(v)){
      mst[i][0] = u;
      mst[i][1] = v;
      mst[i][2] = edges[3];
      mst_union.setUnion(u, v);
    }
  }
}

void graphMST::sort(int *arr[3], int left, int right)
{
  int i = left, j = right;
  int tmp, tmp1, tmp2;
  int pivot = arr[(left + right) / 2][2];

  // partition
  while( i <= j) {
    while( arr[i][2] < pivot)
      ++i;
    while( arr[j][2] > pivot)
      --j;
    if(i <= j) {
      tmp = arr[i][0];
      tmp1 = arr[i][1];
      tmp2 = arr[i][2];
      arr[i][0] = arr[j][0];
      arr[i][1] = arr[j][1];
      arr[i][2] = arr[j][2];
      arr[j][0] = tmp;
      arr[j][1] = tmp1;
      arr[j][2] = tmp2;
      i++; j--;
    }
  }

  if(left < j)
    quickSort(arr, left, j);
  if(i < right)
    quickSort(arr, i, right);
}
