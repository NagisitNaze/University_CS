//  Main program for testing

#include <iostream>
#include <string>
#include <cstdlib>

#include "trieTree.h"

using namespace std;

int main()
{

// *****************************************************************
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');

	cout << bars << endl << "CS 302 - Assignment #6" << endl;
	cout << endl;

// *****************************************************************
//  Test Trie

	trieTree	myTree0;
	string	words[10] = {"the", "a", "there", "answer", "any",
				"by", "bye", "their", "ball", "balloon" };
	int	len = 10;

	for (int i=0; i<len; i++)
		myTree0.insert(words[i]);

	for (int i=0; i<len; i++)
		if (!myTree0.search(words[i]))
		cout << "main: Error, word "" " << words[i]
			<< " "" is lost." << endl;

	cout << "Max Height: " << myTree0.height() << endl;
	cout << "Node Count: " << myTree0.countNodes() << endl;

	cout << "Tree: " << endl;
	myTree0.printTree();

// *****************************************************************

/*
	trieTree	myTree1;
	string		tmpStr, wrd;
	const		int	order = 4;
	string		letters[order][order] =
				{ "a", "s", "f", "s",
				"h", "w", "i", "t",
				"c", "t", "a", "a",
				"l", "r", "i", "n" };

	if (!myTree1.readDictionary("smallDictionary.txt")) {
		cout << "main: Read dictionary error." << endl;
		exit(1);
	}

	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
//			findWord(myTree1, letters, i, j, order, wrd);
			if (wrd != "")
				cout << "Word: " << wrd << endl;
		}
	}

	cout << "Max Height: " << myTree1.height() << endl;
	cout << "Node Count: " << myTree1.countNodes() << endl;

// *****************************************************************
//  All done.
*/
	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}
