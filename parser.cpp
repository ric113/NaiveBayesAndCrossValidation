#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

#include "parser.h"


void DEBUG_showDataTable(vector<vector<string> > &dataTable, int attributeAmount){
	for(int i = 0 ; i < dataTable.size() ; i ++){
		for(int j = 0 ; j < attributeAmount ; j ++){
			cout << dataTable[i][j] << " ";
		}
		cout << endl;
	}
}

void DEBUG_showAttrInfoTable(vector<map<string, vector<int> > > &attrInfoTable){
	cout << "Yo" << endl;
	for(int i = 0 ; i < attrInfoTable.size() ; i ++){
		map<string, vector<int> >::iterator it = attrInfoTable[i].begin();
		while(it != attrInfoTable[i].end()){
			cout << it->first << endl;
			for(int j = 0 ; j < (it->second).size() ; j ++)
				cout << (it->second)[j] << " ";
			cout << endl;
			it ++;
		}
	}
}

void splitWithDelim(const string &s, string delim,vector<string> &tokens)
{

    char *src = strdup(s.c_str());
    char *ptr = strtok(src, delim.c_str()); // split source string with delimiter, and return the first sub-string to *ptr
    while (ptr != NULL) {
        tokens.push_back(string(ptr));
        ptr = strtok(NULL, delim.c_str()); // with the first argument of strtok() being NULL,it would continue on splitting the remaining source string from previous strtok
    }

}

vector<string> splitWithSpace(const string &source)
{
    stringstream ss(source);
    vector<string> vec( (istream_iterator<string>(ss)), istream_iterator<string>() );
    return vec;
}

bool isContiAttr(int index, vector<int> &contiAttributeIndex){
	for(int i = 0 ; i < contiAttributeIndex.size() ; i ++){
		if(index == contiAttributeIndex[i])
			return true;
	}

	return false;
}

void initAttrInfoTable(vector<map<string, vector<int> > > &attrInfoTable, int attributeAmount){
	map<string, vector<int> > temp;
	vector<int> t;
	t.push_back(-1);
	temp["initial"] = t;

	for(int i = 0 ; i < attributeAmount ; i ++){
		attrInfoTable.push_back(temp);
	}
}

void setAttrInfo(string nameFile, vector<vector<string> > &attrValueTable, int &attributeAmount, vector<int> &contiAttributeIndex)
{
	ifstream fs(nameFile);

	string line;
	vector<string> classes;
	int lineCount = 0 ;
	int tempAttrAmount = 0;
	

	while(getline(fs, line))
	{
		// cout << line << endl;
		
		if(lineCount == 0){
			// Class Attr. Line .
			vector<string> tokens = splitWithSpace(line);
			for(int i = 0 ; i < tokens.size() ; i ++){
				classes.push_back(tokens[i].substr(0,tokens[i].size()-1));
				// cout << classes[i] << endl;
			}

			lineCount ++;
		}
		else if(lineCount == 1){
			// blank Line .
			lineCount++;
		}
		else{
			tempAttrAmount ++ ;

			if(line.find("continuous") != std::string::npos)
				contiAttributeIndex.push_back(tempAttrAmount - 1);

			// split by ':' .
			vector<string> tokens;
			splitWithDelim(line,":",tokens);

			// split value's tokens by space .
			vector<string> valueTokens;
			valueTokens = splitWithSpace(tokens[1]);

			for(int i = 0 ; i < valueTokens.size() ; i ++)
				valueTokens[i] = valueTokens[i].substr(0,valueTokens[i].size()-1);

			attrValueTable.push_back(valueTokens);

		}

	}

	// push Class to be last attr .
	attrValueTable.push_back(classes);
	attributeAmount = tempAttrAmount + 1; // add 'Class' attribute .

	fs.close();
}

void setDataAndAttrInfoTable(string dataFile, vector<vector<string> > &dataTable, vector<map<string, vector<int> > > &attrInfoTable,vector<int> &contiAttributeIndex)
{
	ifstream fs(dataFile);

	string line;
	int count = 0;

	while(getline(fs, line))
	{
		vector<string> tokens ;
		splitWithDelim(line,",",tokens);

		vector<string> instance;
		for(int i = 0 ; i < tokens.size() ; i ++){
			instance.push_back(tokens[i]);
			
			if(!isContiAttr(i,contiAttributeIndex))
				attrInfoTable[i][tokens[i]].push_back(count);
		}
		
		dataTable.push_back(instance);
		count ++;
	}

	fs.close();

}

void parsingProcess(string dataFile,string nameFile,vector<vector<string> > &dataTable, vector<map<string, vector<int> > > &attrInfoTable, int &attributeAmount, vector<int> &contiAttributeIndex)
{
	vector<vector<string> > attrValueTable;
	setAttrInfo(nameFile,attrValueTable,attributeAmount, contiAttributeIndex);

	// for(int i = 0 ; i < attrTable.size() ; i ++){
	//	cout << attrTable[i] << " : "<< endl;
	//	for(int j = 0 ; j < attrValueTable[i].size() ; j ++)
	//		cout << attrValueTable[i][j] << endl;
	// }
	// 
	
	initAttrInfoTable(attrInfoTable, attributeAmount);
	setDataAndAttrInfoTable(dataFile, dataTable, attrInfoTable, contiAttributeIndex);
	// DEBUG_showDataTable(dataTable,attributeAmount);
	// DEBUG_showAttrInfoTable(attrInfoTable);
}




