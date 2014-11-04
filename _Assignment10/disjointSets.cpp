#include <iostream>
#include "disjointSets.h"

disjointSets::disjointSets(int param)
{
  if(param < 10)
    param = 10;
  setSize = param;
}

disjointSets::~disjointSets()
{
  if(links != NULL)
    delete [] links;
  if(ranks != NULL)
    delete [] ranks;
}

int disjointSets::entries() const
{

}

bool disjointSets::isEmpty() const
{

}

void disjointSets::printSets() const
{

}

int disjointSets::setUnion(int, int)
{

}

int disjointSets::setFind(int p)
{
  
}
