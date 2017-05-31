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
vector<map<string, vector<int> > > attrInfoTable;
vector<int> contiAttributeIndex;

vector<int> foldedTrainingData[10];	// data's index .
vector<int> foldedTestingData[10];	// data's index .

const string dataSetName = "car";

int main(){
	
	parsingProcess("./dataset/"+ dataSetName +".data", "./dataset/"+ dataSetName +".names", dataTable, attrInfoTable, attributeAmount, contiAttributeIndex);
	cvProcess(dataTable, attrInfoTable, foldedTrainingData, foldedTestingData, dataSetName);

	return 0;
}