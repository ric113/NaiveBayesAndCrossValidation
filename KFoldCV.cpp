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

void setFolds(map<string,int> &classAmountPerFold, string dataSetName)
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

			// if it's not dummy feild .
			if(currentClass != "initial"){

				for(int j = 0 ; j < currentIndexList.size() ; j ++){
					int dataIndex = currentIndexList[j];

					string line = dataTable[dataIndex][0];

					vector<string> instance;
					instance.push_back(dataTable[dataIndex][0]);

					for(int k = 1 ; k < dataTable[dataIndex].size() ; k ++){
						line += "," + dataTable[dataIndex][k];
						instance.push_back(dataTable[dataIndex][k]);
					}
					
					if( currentPickStartedIndex <= j && j < currentPickStartedIndex + currentPickAmount){ 	// Testing
						ofs_test << line << endl;
						foldedTestingData[i].push_back(instance);
					}
					else{	// Training
						ofs_train << line << endl;
						foldedTrainingData[i].push_back(instance);
					}
					
				}


			}
			
			it ++;
		}

		// ouput name file .
		string nameFile =  "./dataset/"+ dataSetName +".names";	
		ifstream ifs_name(nameFile);
		string ouputNamefile = OUTPUT_DIR + dataSetName + "_cv" + to_string(i+1) + ".names";
		ofstream ofs_name(ouputNamefile, ofstream::out);
		string line;

		while(getline(ifs_name, line))
		{
			ofs_name << line << endl;;
		}

		ifs_name.close();
		ofs_name.close();
		ofs_test.close();
		ofs_train.close();
	}

}

void calculateClassAmountPerFold(map<string,int> &classAmountPerFold,int dataSize)
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
}

void cvProcess(string dataSetName)
{
	map<string,int> classAmountPerFold ;	// 紀錄各個Class在每個fold要有的數量 .
	calculateClassAmountPerFold(classAmountPerFold,dataTable.size());
	setFolds(classAmountPerFold,dataSetName);
}	