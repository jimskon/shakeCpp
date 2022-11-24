//
//  shakeAPI.cc - a microservice demo program
//
// James Skon
// Kenyon College, 2022
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "httplib.h"
#include "textindex.h"
using namespace httplib;
using namespace std;

const int port = 5002;
const string path = "";

string fileName = "shakespeare.txt";
ifstream textFile;

textindex tindex(fileName);

int main(void) {
  Server svr;
  list<int>::iterator it;
  int position;
  string line;
  
  // Open the text file                                                       
  textFile.open(fileName, ios::in);
  if (textFile.bad()) {
    cout << "File: " << fileName << " cannot be opened" << endl;
    exit (1);
  }
  
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_header("Access-Control-Allow-Origin","*");
    res.set_content("shake/word", "text/plain");
  });
  
  svr.Get(R"(/shake/(.*))", [&](const Request& req, Response& res) {
    res.set_header("Access-Control-Allow-Origin","*");

    string word = req.matches[1];
    list<int> result = tindex.indexSearch(word);
    int matches = result.size();
    string results = "{\"results\":[";
    int c = 0;
    
    /* Traverse the list of references */
    for (it = result.begin() ; it != result.end(); it++)
      {
	// Grab the postion of the reference out of the iterator          
	position = (*it);
	// Seek that line in the file, and display it                     
	textFile.seekg (position, ios::beg);
	getline(textFile,line);
	results += "\""+line+"\"";
	c++;
	if (c < matches) {
	  results += ",";
	}
      }
    results += "]}";
    cout << results << endl;
    res.set_content(results, "text/json");
    res.status = 200;
  });
  
  cout << "Server listening on port " << port << endl;
  svr.listen("0.0.0.0", port);

}
