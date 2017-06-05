#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>

#include "naiveBayesian.h"
#include "parser.h"			// usage of 'isConti() func.'

#define FOLD_NUM 10

using namespace std;

void DEBUG_showPropTable(vector<map<string, map<string, double> > > &conditionalProbabilityTable,
						map<string, double> &classProbabilityTable)
{
	cout << "conditionalProbabilityTable" << endl;

	for(int i = 0 ; i < conditionalProbabilityTable.size(); i ++ ){
		cout << "Attr " << i + 1 << endl;
		map<string, map<string, double> >::iterator it = conditionalProbabilityTable[i].begin();
		while(it != conditionalProbabilityTable[i].end()){
			cout << it->first << " --- ";
			 map<string, double>::iterator itt = (it->second).begin();
			 double sum = 0;
			 while(itt != (it->second).end()){
			 	cout << itt->first << ",";
			 	cout << itt->second << " ";
			 	sum += itt->second;
			 	itt ++;
			 }
			 cout << sum << endl;
			 cout << endl;
			it ++;
		}
	}

	cout << "classProbabilityTable" << endl;

	map<string, double>::iterator ittt = classProbabilityTable.begin();
	while(ittt != classProbabilityTable.end()){
		cout << ittt->second << endl;
		ittt ++;
	}


}

void collectContiAttrValue(vector<vector<string> > &trainingDataSet, 
							int attrAmount,
							map<int,vector<double> > &contiAttrValues)
{
	for(int i = 0 ; i < attrAmount ; i ++){			// traverse attr .
		if(isContiAttr(i)){
			vector<double> values;
			for(int j = 0 ; j < trainingDataSet.size() ; j ++){ // traverse data .
				values.push_back(stod(trainingDataSet[j][i]));
			}
			contiAttrValues[i] = values;
		}
	}
}

// Param 1 : 該attr的index , Param 2 : 該attr的value .
string getContiSegment(int index, string value ,map<int,vector<double> > &contiAttrCutPoints)
{
	vector<double> cutPoints = contiAttrCutPoints[index];
	double firstCutpoint = cutPoints[0];
	double secondCutpoint = cutPoints[1];
	double thirdCutpoint = cutPoints[2];
	double targetValue = stod(value);

	if(targetValue < firstCutpoint)
		return "A";
	else if( firstCutpoint <= targetValue && targetValue < secondCutpoint)
		return "B";
	else if(  secondCutpoint <= targetValue && targetValue < thirdCutpoint)
		return "C";
	else
		return "D";

}

void setContiAttrCutPoint(map<int,vector<double> > &contiAttrValues,
							map<int,vector<double> > &contiAttrCutPoints)
{
	for(int i = 0 ; i < contiAttributeIndex.size() ; i ++){
		vector<double> values = contiAttrValues[contiAttributeIndex[i]];

		double max = *max_element(values.begin(), values.end());
		double min = *min_element(values.begin(), values.end());

		double secondCutpoint = (max + min) / 2.0;
		double firstCutpoint = (min + secondCutpoint) / 2.0;
		double thirdCutpoint = (max + secondCutpoint) / 2.0;

		vector<double> cutPoints;
		cutPoints.push_back(firstCutpoint);
		cutPoints.push_back(secondCutpoint);
		cutPoints.push_back(thirdCutpoint);

		contiAttrCutPoints[contiAttributeIndex[i]] = cutPoints;
		values.clear();
		
	}
}

void calculateClassesSize(map<string, int> &classSizeTable,
							vector<string> &classes,
							vector<vector<string> > &trainingDataSet)
{
	// init .
	for(int i = 0 ; i < classes.size() ; i ++){
		classSizeTable[classes[i]] = 0;
	}

	for(int i = 0 ; i < trainingDataSet.size() ; i ++){
		string currentClass = trainingDataSet[i][trainingDataSet[i].size()-1];
		classSizeTable[currentClass] ++;
	}

}

void calculateProbailities(vector<map<string, map<string, double> > > &conditionalProbabilityTable,
							vector<vector<string> > &trainingDataSet,
							map<string, double> &classProbabilityTable,
							map<string, int> &classSizeTable,
							vector<string> &classes,
							map<int,vector<double> > &contiAttrCutPoints,
							int attrAmount)
{
	int totalDataSize = trainingDataSet.size();

	// conditionalProbabilityTable
	for(int i = 0 ; i < totalDataSize; i ++){

		string currentDataClass = trainingDataSet[i][trainingDataSet[i].size()-1];
		// cout << currentDataClass << endl;
		for(int j = 0 ; j < trainingDataSet[i].size() - 1 ; j ++){
			string currentAttrValue = trainingDataSet[i][j];
			// if i is not conti attr .
			if(!isContiAttr(j)){
				conditionalProbabilityTable[j][currentDataClass][currentAttrValue] += 1.0;
			} else{
				// if is conti
				string segment = getContiSegment(j, currentAttrValue, contiAttrCutPoints);
				conditionalProbabilityTable[j][currentDataClass][segment] += 1.0;
			}	
		}
	}

	for(int i = 0 ; i < attrAmount  ; i ++){
		map<string, map<string, double> >::iterator it = conditionalProbabilityTable[i].begin();
		while(it != conditionalProbabilityTable[i].end()){

			map<string, double>::iterator it2 = (it->second).begin();
			while( it2 != (it->second).end()){
				it2->second = (it2->second + 1.0)/ (double)(classSizeTable[it->first] + (it->second).size());
				it2 ++;
			}

			it++;
		}
	}

	// classProbabilityTable
	for(int i = 0 ; i < classes.size() ; i ++){
		string currentClass = classes[i];
		classProbabilityTable[currentClass] = (double)classSizeTable[currentClass] / totalDataSize;
	}

}

void initProbabilityTables(vector<string> &classes,
							vector<map<string, map<string, double> > > &conditionalProbabilityTable,
							int attrAmount)
{
	for(int i = 0 ; i < attrAmount  ; i ++){	// traver all attr , create per lookup table .
		
		map<string, map<string, double> > table;
		for(int j = 0 ; j < classes.size() ; j ++){
			if(!isContiAttr(i)){
				for(int k = 0 ; k < attrValueTable[i].size() ; k ++){
					table[classes[j]][attrValueTable[i][k]] = 0.0;
				}
			} else {
				// conti : 切4個區段 .
				table[classes[j]]["A"] = 0.0;
				table[classes[j]]["B"] = 0.0;
				table[classes[j]]["C"] = 0.0;
				table[classes[j]]["D"] = 0.0;
				
			}
		}
		conditionalProbabilityTable.push_back(table);
	}


}

void NBProcess()
{

	int attrAmount = attrValueTable.size() - 1; 	// 扣掉Class attr .
	vector<string> classes = attrValueTable[attrValueTable.size()-1];
	vector<double> accuracies;

	for(int i = 0 ; i < FOLD_NUM ; i ++){
		// class -> map<attr value, prob> ;
		vector<map<string, map<string, double> > > conditionalProbabilityTable;
		map<string, int> classSizeTable;
		map<string, double> classProbabilityTable;
		map<int,vector<double> > contiAttrValues;
		map<int,vector<double> > contiAttrCutPoints;	// 2d array , 對應到contiAttributeIndex的index .

		// traing
		vector<vector<string> > trainingDataSet = foldedTrainingData[i];
		calculateClassesSize(classSizeTable,classes,trainingDataSet);
		initProbabilityTables(classes,conditionalProbabilityTable,attrAmount);
		collectContiAttrValue(trainingDataSet,attrAmount,contiAttrValues);
		
		/*
		map<int,vector<double> >::iterator it = contiAttrValues.begin();
		while(it != contiAttrValues.end()){
			cout << it->first <<  endl;
			for(int j = 0 ; j < it->second.size() ; j ++)
				cout << it->second[j] << ", ";
			cout << endl;
			it ++;
		}
		*/

		setContiAttrCutPoint(contiAttrValues,contiAttrCutPoints);

		/*
		map<int,vector<double> >::iterator it = contiAttrCutPoints.begin();
		while(it != contiAttrCutPoints.end()){
			cout << it->first <<  endl;
			for(int j = 0 ; j < it->second.size() ; j ++)
				cout << it->second[j] << ", ";
			cout << endl;
			it ++;
		}
		*/
	
		calculateProbailities(conditionalProbabilityTable,trainingDataSet,classProbabilityTable,classSizeTable,classes,contiAttrCutPoints,attrAmount);
		
		// testing
		vector<vector<string> > testingDataSet = foldedTestingData[i];
		int accAmount = 0 ;
		for(int i = 0 ; i < testingDataSet.size() ; i ++){		// traves per data .
			double maxProb = -1.0;
			int maxIndex = -1 ;
			for(int j = 0 ; j < classes.size() ; j ++){			// cal. per predicted class prob .
				double p = 1.0 ;
				for(int k = 0 ; k < attrAmount ; k ++){			// mul. all P(attr|c) value .
					if(!isContiAttr(k))
						p *= conditionalProbabilityTable[k][classes[j]][testingDataSet[i][k]];
					else{
						// if conti.
						string segment = getContiSegment(k, testingDataSet[i][k], contiAttrCutPoints);
						p *= conditionalProbabilityTable[k][classes[j]][segment];
					}
				}
				if(p > maxProb){
					maxProb = p;
					maxIndex = j;		// max Class index .
				}
			}

			if(classes[maxIndex] == testingDataSet[i][testingDataSet[i].size()-1])
				accAmount ++;
		}

		accuracies.push_back((double)accAmount / (double)testingDataSet.size());

		conditionalProbabilityTable.clear();
		classProbabilityTable.clear();
		
	}

	// Show out result .
	double sum = 0 ;
	for(int i = 0 ; i < FOLD_NUM ; i ++){
		cout << "Fold " << i + 1 << endl;
		cout << "accuracy = " << accuracies[i] << endl; 
		sum += accuracies[i];
	}
	
	cout << "-----" << endl;
	cout << "Avg. : " << sum / FOLD_NUM << endl;
}
