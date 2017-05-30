#include <iostream>
#include <map>
#include <vector>
#include <math.h> 

#include "KFoldCV.h"


void calculateClassAmountPerFold(map<string,int> &classAmountPerFold,vector<map<string, vector<int> > >  &attrInfoTable, int dataSize, int testDataSize)
{
	map<string, vector<int> > classValueInfo = attrInfoTable[attrInfoTable.size()-1];

	map<string, vector<int> >::iterator it = classValueInfo.begin();
	double ratio;

	while(it != classValueInfo.end()){
		vector<int> indices = it->second;
		ratio = (double)indices.size()/(double)dataSize;

		classAmountPerFold[it->first] = floor((int)(ratio * testDataSize));

		it ++;
	}

	/*
	cout << testDataSize << endl;
	map<string, int>::iterator itt = classAmountPerFold.begin();
	while(itt != classAmountPerFold.end()){
		cout << itt->first << " " << itt->second << endl;
		itt++;
	}
	*/
}

void cvProcess(vector<vector<string> > &dataTable, vector<map<string, vector<int> > > &attrInfoTable, vector<vector<string> >* foldedTrainingData, vector<vector<string> >* foldedTestingData)
{
	int dataSize =  dataTable.size();
	int testDataSize = dataSize / 10 ;

	map<string,int> classAmountPerFold ;
	calculateClassAmountPerFold(classAmountPerFold,attrInfoTable,dataSize,testDataSize);

}	