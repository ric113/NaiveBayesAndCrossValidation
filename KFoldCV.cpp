#include <iostream>
#include <map>
#include <vector>
#include <math.h> 
#include <fstream>
#include <string>

#include "KFoldCV.h"

#define FOLD_NUM 10
#define OUTPUT_DIR "foldedDataSets/"

using namespace std;

void setFolds(vector<vector<string> > &dataTable,vector<map<string, vector<int> > > &attrInfoTable, vector<int>* foldedTrainingData, vector<int>* foldedTestingData,map<string,int> &classAmountPerFold, string dataSetName)
{
	int dataSize =  dataTable.size();
	int testDataSize = dataSize / FOLD_NUM ;

	map<string, vector<int> > classValueInfo = attrInfoTable[attrInfoTable.size()-1];

	for(int i = 0 ; i < FOLD_NUM ;i ++){
		string testFileName = OUTPUT_DIR + dataSetName + "_cv" + to_string(i+1) + ".test";
		string trainFileName = OUTPUT_DIR + dataSetName + "_cv" + to_string(i+1) + ".data";
		ofstream ofs_test(testFileName, ofstream::out);
		ofstream ofs_train(trainFileName, ofstream::out);

		map<string,int>::iterator it = classAmountPerFold.begin();

		while(it != classAmountPerFold.end()){

			string currentClass = it->first;
			int currentPickAmount = it->second;
			vector<int> currentIndexList = classValueInfo[currentClass];
			int currentPickStartedIndex = i * currentPickAmount;

			// dummy feild .
			if(currentClass != "initial"){

				for(int j = 0 ; j < currentIndexList.size() ; j ++){
					int dataIndex = currentIndexList[j];

					string line = dataTable[dataIndex][0];

					for(int k = 1 ; k < dataTable[dataIndex].size() ; k ++){
						line += "," + dataTable[dataIndex][k];
					}

					if( currentPickStartedIndex <= j && j < currentPickStartedIndex + currentPickAmount)
						ofs_test << line << endl;
					else
						ofs_train << line << endl;
					
				}


			}
			
			it ++;
		}

		ofs_test.close();
		ofs_train.close();
	}

}


void calculateClassAmountPerFold(map<string,int> &classAmountPerFold,vector<map<string, vector<int> > >  &attrInfoTable,int dataSize)
{

	int testDataSize = dataSize / FOLD_NUM ;

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

void cvProcess(vector<vector<string> > &dataTable, vector<map<string, vector<int> > > &attrInfoTable, vector<int>* foldedTrainingData, vector<int>* foldedTestingData, string dataSetName)
{
	map<string,int> classAmountPerFold ;
	calculateClassAmountPerFold(classAmountPerFold,attrInfoTable,dataTable.size());
	setFolds(dataTable,attrInfoTable,foldedTrainingData,foldedTestingData,classAmountPerFold,dataSetName);

}	