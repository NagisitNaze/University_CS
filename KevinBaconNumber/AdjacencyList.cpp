#include <iostream>
#include <string>
#include "HashAdjList.h"

HashedAdjacencyList::HashedAdjacencyList():
d_vertcount(0)
{
    d_actors = NULL;
    d_movies = NULL;
}

HashedAdjacencyList::~HashedAdjacencyList()
{

}

void HashedAdjacencyList::addEdge(std::string from, std::string to)
{
    if((from <= d_vertcount && to <= d_vertcount) && 
        (from > 0 && to > 0)) {
        if(from == to)
            std::cout << "Error, from and to cannot be the same\n"
        else {
            int f1 = d_actors.find(from);
            int f2 = d_movies.find(from);
            if(f1 == -1 && f2 == -1) {
                std::cout << "Error vertex not found...\n";
            }else if(f1 > -1) {
                
            } 
        }
    }    
}

void HashedAdjacencyList::addActorVertex(std::string key)
{
    d_actors.insert(key);
}

void HashedAdjacencyList::addMovieVertex(std::string key)
{
    d_movies.insert(key);
}

bool HashedAdjacencyList::readDataFile(const std::string fileName)
{

}

int HashedAdjacencyList::getVertexCount()
{
    return d_vertcount;
}
