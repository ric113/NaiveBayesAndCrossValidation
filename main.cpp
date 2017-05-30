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

vector<vector<string> > foldedTrainingData[10];
vector<vector<string> > foldedTestingData[10];

int main(){
	
	parsingProcess("./dataset/car.data", "./dataset/car.names", dataTable, attrInfoTable, attributeAmount, contiAttributeIndex);
	cvProcess(dataTable, attrInfoTable, foldedTrainingData, foldedTestingData);

	return 0;
}