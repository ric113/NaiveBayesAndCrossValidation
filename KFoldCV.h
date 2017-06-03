#include <iostream>
#include <map>
#include <vector>

using namespace std;

void cvProcess(string);
// 計算各個Class在每個Flod所需要的個數 , Keep在一個map中 .
void calculateClassAmountPerFold(map<string,int>&, int);
void setFolds(map<string,int>&, string);

extern vector<vector<string> > dataTable;
extern vector<map<string, vector<int> > > attrInfoTable;
extern vector<vector<string> > foldedTrainingData[10];	
extern vector<vector<string> > foldedTestingData[10];	