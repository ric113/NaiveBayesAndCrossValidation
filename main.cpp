#include <iostream>
#include <fstream>
#include <map>
#include <vector>


#include "parser.h"
#include "KFoldCV.h"
#include "naiveBayesian.h"

using namespace std;

// Global Variables .
int attributeAmount ;	// 包含Class這個欄位 . 
vector<vector<string> > dataTable;	// A 2-D table .
vector<vector<string> > attrValueTable;		// 依照Column順序, 紀錄各Attri. 有的value .
map<string, vector<int> > classInformation;
vector<int> contiAttributeIndex;	// 紀錄Conti. attri. 在第幾Column .

vector<vector<string> > foldedTrainingData[10];
vector<vector<string> > foldedTestingData[10];

int main(int argc, const char **argv){
	
	if(argc != 2){
		cout << "Usage : ./main [dataset name without extension] " << endl;
		return 0;
	}

	string dataSetName = argv[1];

	parsingProcess(dataSetName);
	cvProcess(dataSetName);
	NBProcess();

	return 0;
	
}