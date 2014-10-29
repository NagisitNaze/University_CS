#include <iostream>
#include <fstream>
#include "binaryHeap.h"

binaryHeap::binaryHeap(int size)
{
  if(size < 100 || size > 1000)
    size = 100;

  heapSize = size;
}

binaryHeap::~binaryHeap()
{
  if(jobHeap != NULL)
    delete [] jobHeap;
}

int binaryHeap::entries() const
{
  return count;
}

bool binaryHeap::readJobs(const std::string fileName)
{
  std::ifstream inFile(fileName.c_str());
}

void binaryHeap::insert(const std::string, const int)
{

}

bool binaryHeap::deleteMax(std::string &, int &)
{

}

bool binaryHeap::isEmpty() const
{

}

void binaryHeap::printJobHeap() const
{

}

void binaryHeap::reheapUp(int)
{

}

void binaryHeap::reheapDown(int)
{

}

void binaryHeap::buildHeap()
{
  jobHeap = new jobElement[size];
  for(int i = 0; i < size; i++)
    jobHeap[i] = NULL;
}

void binaryHeap::resize()
{
  //create temporary array
  jobElement oldEntries[heapSize];
  int j = 0;
  for(int i = 0; i < heapSize; i++) {
    if(jobHeap[i] != NULL){
      oldEntries[j] = jobHeap[i];
      j++;
    }
    oldEntries[i] = NULL;
  }

  //free memory
  delete [] jobHeap;

  //double size of heap
  heapSize = heapSize * 2;
  //create new table, set all elements inside to NULL
  jobHeap = new jobElement[heapSize];
  for(int i = 0; i < heapSize; i++)
    jobHeap[i] = NULL;
  count = 0;

  for(int i = 0; i < sizeof(oldEntries) / sizeof(oldEntries[0]); i++) {
    jobHeap[i] = oldEntries[i];
}
