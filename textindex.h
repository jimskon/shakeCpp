  /*****************************************************************************/
  /*                                                                           */
  /*  Filename:     textindex.h                                             */
  /*  Author(s):    Jim Skon                                                   */
  /*  Last Update:  2/10/2013                                                  */
  /*                                                                           */
  /*                                                                           */
  /*****************************************************************************/
  using namespace std;

  class textindex {
  public:

    textindex(string filename);

    list<int> indexSearch(string);

  private:
    map<string, list<int> > index;

    string getNextWord(string&);

  };
