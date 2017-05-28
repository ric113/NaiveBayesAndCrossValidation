#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

void parsingProcess(string, string, vector<map<string, string> >&, map<string ,map<string, vector<int> > >&);
void setDataTable(string, vector<string>&, vector<map<string, string> >&);
void setAttrInfo(string, vector<string>&, vector<vector<string> >&);
vector<string> splitWithSpace(const string&);
void splitWithDelim(const string&, string,vector<string>&);


// DEBUG usage .
void DEBUG_showDataTable(vector< map<string, string> >&, vector<string>&);