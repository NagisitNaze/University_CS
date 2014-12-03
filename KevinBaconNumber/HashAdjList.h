#ifndef HASHADJLIST_H_
#define HASHADJLIST_H_

#include "HashList.h"
#include <string>

class HashedAdjacencyList {
    public:
        HashedAdjacencyList();
        ~HashedAdjacencyList();
    
        void addEdge(int,int);
        void addVertex(std::string);

        bool readDataFile(const std::string);
        bool initNewGraph();
        
        int getVertexCount();
        int freeGraph();
    private:
        HashList *d_actors;
        HashList *d_movies;

        int d_vertcount;
};

#endif
