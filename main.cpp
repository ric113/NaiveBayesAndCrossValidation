#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "parser.h"
#include "KFoldCV.h"
#include "naiveBayesian.h"

using namespace std;

// Global Variables .
int attributeAmount ; // include Class .
vector<vector<string> > dataTable;
vector<vector<string> > attrValueTable;
vector<map<string, vector<int> > > attrInfoTable;
vector<int> contiAttributeIndex;

vector<vector<string> > foldedTrainingData[10];	// data's index .
vector<vector<string> > foldedTestingData[10];	// data's index .

const string dataSetName = "winequality";

int main(){
	
	parsingProcess("./dataset/"+ dataSetName +".data", "./dataset/"+ dataSetName +".names", dataTable, attrInfoTable, attributeAmount, contiAttributeIndex, attrValueTable);
	// cout << "Yo" << endl;
	cvProcess(dataTable, attrInfoTable, foldedTrainingData, foldedTestingData, dataSetName);
	// cout << "Yo" << endl;
	NBProcess(foldedTrainingData, 
		foldedTestingData, 
		attrValueTable, 
		contiAttributeIndex);
	return 0;
}