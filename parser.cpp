#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;


void DEBUG_showDataTable(vector< map<string, string> > &dataTable, vector<string> &attrTable){
	for(int i = 0 ; i < dataTable.size() ; i ++){
		for(int j = 0 ; j < attrTable.size() ; j ++){
			cout << dataTable[i][attrTable[j]] << " ";
		}
		cout << endl;
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

void setAttrInfo(string nameFile, vector<string> &attrTable, vector<vector<string> > &attrValueTable)
{
	ifstream fs(nameFile);

	string line;
	vector<string> classes;
	int lineCount = 0 ;

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
			// split by ':' .
			vector<string> tokens;
			splitWithDelim(line,":",tokens);

			// attr name .
			attrTable.push_back(tokens[0]);

			// split value's tokens by space .
			vector<string> valueTokens;
			valueTokens = splitWithSpace(tokens[1]);

			for(int i = 0 ; i < valueTokens.size() ; i ++)
				valueTokens[i] = valueTokens[i].substr(0,valueTokens[i].size()-1);

			attrValueTable.push_back(valueTokens);

		}

	}

	// push Class to be last attr .
	attrTable.push_back("Class");
	attrValueTable.push_back(classes);

	fs.close();
}

void setDataTable(string dataFile,vector<string> &attrTable,vector< map<string, string> > &dataTable)
{
	ifstream fs(dataFile);

	string line;

	while(getline(fs, line))
	{
		vector<string> tokens ;
		splitWithDelim(line,",",tokens);

		map<string, string> instance;
		for(int i = 0 ; i < tokens.size() ; i ++)
			instance[attrTable[i]] = tokens[i];
		
		dataTable.push_back(instance);
	}

	fs.close();

}

void parsingProcess(string dataFile,string nameFile,vector< map<string, string> > &dataTable, map<string ,map<string, vector<int> > > &attrInfoTable)
{
	vector<string> attrTable;
	vector<vector<string> > attrValueTable;
	setAttrInfo(nameFile,attrTable,attrValueTable);

	// for(int i = 0 ; i < attrTable.size() ; i ++){
	//	cout << attrTable[i] << " : "<< endl;
	//	for(int j = 0 ; j < attrValueTable[i].size() ; j ++)
	//		cout << attrValueTable[i][j] << endl;
	// }
	
	setDataTable(dataFile, attrTable, dataTable);
	// DEBUG_showDataTable(dataTable,attrTable);
}




