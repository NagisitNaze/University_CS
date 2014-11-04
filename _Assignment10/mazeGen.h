#ifndef MAZEGEN_H_
#define MAZEGEN_H_

#include <string>

class mazeGen
{
  public:
    mazeGen(int, int);
    ~mazeGen();
    void getSize(int &, int &) const;
    void generate();
    bool printMazeData(const std::string) const;
    void printMazeText() const;
    void randomize();
  private:
    int rows;
    int cols;
    int **walls;
};

#endif
