#include <vector>
#include <map>
#include <iostream>

using namespace std;

void NBProcess();

void initProbabilityTables(vector<string>&,
							vector<map<string, map<string, double> > >&,
							int);

void calculateProbailities(vector<map<string, map<string, double> > >&,
							vector<vector<string> >&,
							map<string, double> &,
							map<string, int>&,
							vector<string>&,
							map<int,vector<double> >&,
							int);

void calculateClassesSize(map<string, int>&,
							vector<string>&,
							vector<vector<string> >&);

void collectContiAttrValue(vector<vector<string> >&, 
							int,
							map<int,vector<double> >&);

void setContiAttrCutPoint(map<int,vector<double> >&,
							map<int,vector<double> >&);

string getContiSegment(int, 
						string ,
						map<int,vector<double> >&);



extern vector<vector<string> > attrValueTable;
extern vector<int> contiAttributeIndex;
extern vector<vector<string> > foldedTrainingData[10];	
extern vector<vector<string> > foldedTestingData[10];	