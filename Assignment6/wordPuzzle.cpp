#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "avlTree.h"
#include "wordPuzzle.h"

wordPuzzle::wordPuzzle()
{
  title = "";
  order = 0;
  letters = NULL;
}

wordPuzzle::~wordPuzzle()
{
  if(letters != NULL) {
    for(int i = 0; i < sizeof(letters) / sizeof(std::string *); i++) {
        delete [] letters[i];
    }
    delete [] letters;
  }
}

bool wordPuzzle::readLetters(const std::string word)
{
  std::ifstream inFile(word.c_str());
  if(!inFile.is_open())
    return false;
  //get title and order
  std::getline(inFile, title);
  inFile >> order;
  //allocate letters
  letters = new std::string*[order];
  for(int i = 0; i < order; i++)
    letters[i] = new std::string[order];
  //read in letters to dynamic array
  for(int i = 0; i < order; i++) {
    for(int j = 0; j < order; j++) {
      inFile >> letters[i][j];
    }
  }
  inFile.close();
  return true;
}

bool wordPuzzle::readDictionary(const std::string word)
{
  std::ifstream inFile(word.c_str());
  if(!inFile.is_open())
    return false;
  //create temp string to read in dictionary
  std::string tempRead;
  while(inFile >> tempRead) {
    if(islower(tempRead[0]))
      insert(tempRead);
  }
  inFile.close();
  return true;
}

void wordPuzzle::findWords()
{
  for(int i = 0; i < order; i++)
    for(int j = 0; j < order; j++)
      findWords(i,j,"");
}

void wordPuzzle::showTitle() const
{
  std::cout << title << std::endl;
}

void wordPuzzle::showWordCount() const
{
  std::cout << "Word Count: " <<
    wordsFound.countNodes() << std::endl;
}

void wordPuzzle::showWords() const
{
  wordsFound.printTree(INORDER);
}

void wordPuzzle::printLetters() const
{
  //print top
  for(int i = 0; i < order * 3; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;
  //print rest
  for(int i = 0; i < order; i++) {
    for(int j = 0; j < order*4; j++) {
      if(j % 4 == 0)
        std::cout << "|";
      else if(i < 3){
        std::cout << " ";
      } else if(i == 3){
        std::cout << "_";
      }
    }
    std::cout << std::endl;
  }
  char a;
  std::cin >> a;
}

void wordPuzzle::findWords(int i, int j, std::string wrd)
{
  //check input i + j;
  if(i >= order || i < 0 || j >= order
     || j < 0)
     return;
  if(letters[i][j] == "-")
    return;

  wrd = wrd + letters[i][j];
  if(!isPrefix(wrd))
    return;
  if(search(wrd)) {
    std::stringstream ss;
    ss << std::left << std::setw(15)
       << wrd << "from: (" << i
       << "," << j << ")\n";
    wordsFound.insert(ss.str());
  }
  std::string tmpLter = letters[i][j];
  letters[i][j] = "-";
  //call findWords with all possible words around it
  findWords(i+1,j,wrd);
  findWords(i-1,j,wrd);
  findWords(i,j+1,wrd);
  findWords(i,j-1,wrd);
  findWords(i+1,j+1,wrd);
  findWords(i-1,j-1,wrd);
  findWords(i+1,j-1,wrd);
  findWords(i-1,j+1,wrd);
  letters[i][j] = tmpLter;

}
