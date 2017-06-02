#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

void parsingProcess(string, string, vector<vector<string> >&, vector<map<string, vector<int> > >&, int&, vector<int>&,vector<vector<string> >&);
void setDataAndAttrInfoTable(string, vector<string>&, vector<vector<string> >&, vector<map<string, vector<int> > > &, vector<int>&);
void setAttrInfo(string, vector<vector<string> >&, int&, vector<int>&);
vector<string> splitWithSpace(const string&);
void splitWithDelim(const string&, string,vector<string>&);
bool isContiAttr(int, vector<int>&);
void initAttrInfoTable(vector<map<string, vector<int> > >&, int);
string& trim(std::string &s);


// DEBUG usage .
void DEBUG_showDataTable(vector<vector<string> >&, int);
void DEBUG_showAttrInfoTable(vector<map<string, vector<int> > >&);