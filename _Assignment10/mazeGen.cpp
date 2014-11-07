#include <iostream>
#include <fstream>
#include <cstdlib>
#include "mazeGen.h"
#include "disjointSets.h"

mazeGen::mazeGen(int t_rows, int t_cols):
  rows(t_rows),
  cols(t_cols)
{
  if(rows < 5)
    rows = 5;
  if(cols < 5)
    cols = 5;

  //the amount of walls needed
  int wallsCount = rows * (cols-1) + cols * (rows-1);
  arrSize = wallsCount;
  int horiz = rows * (cols-1);
  int vertz = cols * (rows-1);

  walls = new int*[wallsCount];
  for(int i = 0; i < wallsCount; i++){
    walls[i] = new int[2];
  }

  for(int r = 0; r < rows; r++){
    for(int c = 0; c < cols-1; c++){
      int s = r > 0 ? -1*r : 0;
      //std::cout << r*cols+c+s <<
      //  ": " << r*cols+c << " - " << r*cols+c+1 << std::endl;
      walls[r*cols+c+s][0] = r*cols+c;
      walls[r*cols+c+s][1] = r*cols+c+1;
    }
  }

  for(int c = 0; c < cols; c++){
    for(int r = 0; r < rows-1; r++){
      int s = c > 0 ? -1*c : 0;
      //std::cout << horiz+c*rows+r+s <<
      //  ": " << c*rows+r << " - " << c*rows+r+5 << std::endl;
      walls[horiz+c*rows+r+s][0] = c*rows+r;
      walls[horiz+c*rows+r+s][1] = c*rows+r+5;
    }
  }

  //std::cout << "WallCount: " << arrSize << std::endl;
  //for(int i = 0; i < wallsCount; i++)
    //std::cout << walls[i][0] << " - " << walls[i][1] << std::endl;
}

mazeGen::~mazeGen()
{
  for(int i = 0; i < rows; i++){
    if(walls[i] != NULL)
      delete [] walls[i];
  }
  if(walls != NULL)
    delete [] walls;
}

void mazeGen::getSize(int & t_rows, int & t_cols) const
{
  t_rows = rows;
  t_cols = cols;
}

void mazeGen::generate()
{
  randomize();
  disjointSets d(arrSize);
  for(int i = 0; i+1 < arrSize; i++){
    int s1 = d.setFind(walls[i][0]);
    int s2 = d.setFind(walls[i][1]);
    if(s1 != s2){
      d.setUnion(s1, s2);
      walls[i][0] = walls[i][1] = -1;
    }
  }
}

bool mazeGen::printMazeData(const std::string filename) const
{
  std::cout << "started";
  std::ofstream outFile(filename.c_str());
  outFile << "ROWS " << rows << " COLS " << cols << std::endl;
  for(int i = 0; i < arrSize; i++)
    outFile << "WALL " << walls[i][0] << " " << walls[i][1] << std::endl;
  outFile.close();
  std::cout << " ended";
}

void mazeGen::printMazeText() const
{

}

void mazeGen::randomize()
{
  for(int i = arrSize-1;i > 0;i--){
    int j = rand() % (i+1);

    int tmp = walls[i][0];
    int tmp2 = walls[i][1];

    walls[i][0] = walls[j][0];
    walls[i][1] = walls[j][1];

    walls[j][0] = tmp;
    walls[j][1] = tmp2;
  }

  for(int i = 0; i < arrSize; i++) {
    std::cout << walls[i][0] << " " << walls[i][1] << std::endl;
  }
}
