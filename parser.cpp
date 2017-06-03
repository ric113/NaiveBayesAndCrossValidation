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

string& trim(std::string &s)   
{  
    if (s.empty())   
   		return s;  
    
    s.erase(0,s.find_first_not_of(" "));  
    s.erase(s.find_last_not_of(" ") + 1);  
    return s;  
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

bool isContiAttr(int index){
	for(int i = 0 ; i < contiAttributeIndex.size() ; i ++){
		if(index == contiAttributeIndex[i])
			return true;
	}

	return false;
}

void initAttrInfoTable(){
	// 在每個attrInfoTable元素中以一個dummy field來初始化 .
	map<string, vector<int> > temp;
	vector<int> t;
	t.push_back(-1);
	temp["initial"] = t;

	for(int i = 0 ; i < attributeAmount ; i ++){
		attrInfoTable.push_back(temp);
	}
}

void setAttrValueTable(string nameFile)
{
	ifstream fs(nameFile);

	string line;
	vector<string> classes;
	int lineCount = 0 ;
	int tempAttrAmount = 0;
	

	while(getline(fs, line))
	{
		
		// trim '.' .
		if (line[line.size()-1] == '.' || line[line.size()-1] == '\r')
			line = line.substr(0,line.size()-1);

		if(lineCount == 0){
			// Class Attr. Line .
			vector<string> tokens;
			splitWithDelim(line,",",tokens);
			for(int i = 0 ; i < tokens.size() ; i ++){
				classes.push_back( trim(tokens[i]) );
			}

			lineCount ++;
		}
		else if(lineCount == 1){
			// blank Line .
			lineCount++;
		}
		else{


			trim(line);
			if(line.size() == 0)
				break;

			tempAttrAmount ++ ;

			if(line.find("continuous") != std::string::npos)
				contiAttributeIndex.push_back(tempAttrAmount - 1);

			// split by ':' .
			vector<string> tokens;
			splitWithDelim(line,":",tokens);

			vector<string> valueTokens;
			splitWithDelim(tokens[1],",",valueTokens);

			for(int i = 0 ; i < valueTokens.size() ; i ++)
				valueTokens[i] = trim(valueTokens[i]);

			attrValueTable.push_back(valueTokens);

		}

	}

	// push Class to be last attr .
	attrValueTable.push_back(classes);
	attributeAmount = tempAttrAmount + 1; // add 'Class' attribute .

	fs.close();
}

void setDataAndAttrInfoTable(string dataFile)
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

			// remove \r in the back .
			if(i == tokens.size() - 1){
				if(tokens[i][tokens[i].size()-1] == '\r')
					tokens[i] = tokens[i].substr(0,tokens[i].size()-1);
			}

			instance.push_back(trim(tokens[i]));
			
			if(!isContiAttr(i))
				attrInfoTable[i][tokens[i]].push_back(count);
		}
		
		dataTable.push_back(instance);
		count ++;
	}

	fs.close();

}

void parsingProcess(string dataSetName)
{
	string dataFile = "./dataset/"+ dataSetName +".data";
	string nameFile =  "./dataset/"+ dataSetName +".names";	
	setAttrValueTable(nameFile);
	
	initAttrInfoTable();
	setDataAndAttrInfoTable(dataFile);

	//DEBUG_showDataTable(dataTable,attributeAmount);
	//DEBUG_showAttrInfoTable(attrInfoTable);
}




