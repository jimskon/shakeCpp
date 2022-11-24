/***************************************************************************
 * sslookupservercpp  -  Program to serve Shakespeare search results
 *
 * copyright : (C) 2009 by Jim Skon
 *
*
*
***************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "textindex.h"

using namespace std;


/* Server main line,create name MAP, wait for and serve requests */
int main() {
  list<int> result;
  list<int>::iterator it;
  int position;
  string fileName = "shakespeare.txt";
  string word, line;
  // create text index
  textindex index(fileName);

  ifstream textFile;
  // Open the text file
  textFile.open(fileName, ios::in);
  if (textFile.bad()) {
    cout << "File: " << fileName << " cannot be opened" << endl;
    exit (1);
  }

  while (1) {
    cout << "What to search for? ";
    cin >> word;
    result = index.indexSearch(word);
    int results = result.size();

    if (result.size() < 1) {
	     cout << "No Matches" << endl;
    } else {

	  // Give the match count
	  cout << "Matches: " << results << endl;
	  /* Traverse the list of references */
  	for (it = result.begin() ; it != result.end(); it++)
	  {
	    // Grab the postion of the reference out of the iterator
	    position = (*it);
	    // Seek that line in the file, and display it
	    textFile.seekg (position, ios::beg);
	    getline(textFile,line);
	    cout << line << endl;
	  }

    }
  }
}
