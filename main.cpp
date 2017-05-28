#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "parser.h"

using namespace std;

// Global Variables .
vector< map<string, string> > dataTable;
map<string ,map<string, vector<int> > > attrInfoTable;

int main(){
	
	parsingProcess("./dataset/car.data", "./dataset/car.names", dataTable, attrInfoTable);
	return 0;
}