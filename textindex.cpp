/*****************************************************************************/
/*                                                                           */
/*  Filename:     textindex.cpp                                             */
/*  Author(s):    Jim Skon                                                   */
/*  Last Update:  2/10/2013                                                  */
/*                                                                           */
/*  This CLASS creates an inverted list of tall the words in some text        */
/*  as a STL map structure that maps from words points into the file.        */
/*  The resulting structure can than be used to retrieve a complete list of  */
/*  All places in the file that contain a certain word.                      */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <map>
#include <utility>
#include <list>
#include <set>
#include <string>
#include "textindex.h"

using namespace std;

/*****************************************************************************/
/*                                                                           */
/*      Consructor - convert text into inverted list                                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
  textindex::textindex(string filename) {

  ifstream  infile;     /* input file descriptor */
  int position;         /* Location of line in the file */
  string text, line, word;

  int wordcount = 0;


  /* open text file */
  infile.open(filename, ios::in);
  if (!infile.is_open()) {
	cout << "Error - can't open input file: " << filename << endl;
	return;  /* error */
  }

  /* process text file */
  while (!infile.fail()) {
    /* Get the file position */
    position = infile.tellg();
    /* get the next line */
    getline(infile,line);

    /* Convert verse to lower case*/
    transform(line.begin(), line.end(), line.begin(), ::tolower);

	/* for each word in the verse, stem and put in map */
	while (line.length() > 1) {

	  word = getNextWord(line);

	  if (word.length() > 0 ) {
		    wordcount++;
		    index[word].push_back(position);
	  }
	}

  }
  cout << "Words: " << wordcount << " Unique: " << index.size() << endl;
  return;  /* success */
}

/*****************************************************************************/
/*                                                                           */
/*  Search - Returns refs for all verseswith word matching the input string  */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
list<int> textindex::indexSearch(string word) {

  map<string, list<int> >::iterator it;  // iterator for find
  list<int> blank; // return for no matches

  /* Convert search to all lower */
  transform(word.begin(), word.end(),word.begin(), ::tolower);
  /* return the refs */
  /* First use find, so as to NOT create a new entry */
  it = index.find(word);
  if (it == index.end()) {
    return(blank);
  } else {
    return (index[word]);
  }
}

/*****************************************************************************/
/*                                                                           */
/*      getNextWord(string&) given a string, return the next word, and     */
/*                remove this word from the current string                   */
/*                                                                           */
/*****************************************************************************/
string textindex::getNextWord(string& line) {

  string word="";
  long unsigned int pos;

  if (line.length() > 1)
	{
	  pos = line.find_first_of(".,; :?!""''()");
	  /* get next word */
	  if (pos != 0) {
		word = line.substr(0,pos);
        }
	  /* trim the line */
	  if (pos == string::npos) {
		pos = line.length()-1;
	  }
	  line = line.substr(pos+1, 2000);
	}
  return word;

}
