#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

void parsingProcess(string);
void setAttrValueTable(string);
void initClassInfoTable();
void setDataAndAttrInfoTable(string);
void splitWithDelim(const string&, string,vector<string>&);
bool isContiAttr(int);
string& trim(std::string &s);


// DEBUG usage .
void DEBUG_showDataTable(vector<vector<string> >&, int);
void DEBUG_showAttrInfoTable(vector<map<string, vector<int> > >&);

extern string dataSetName;
extern int attributeAmount ; 
extern vector<vector<string> > dataTable;
extern vector<vector<string> > attrValueTable;
extern map<string, vector<int> > classInformation;
extern vector<map<string, vector<int> > > attrInfoTable;
extern vector<int> contiAttributeIndex;