#include <vector>
#include <map>
#include <iostream>

using namespace std;

void NBProcess(vector<vector<string> >*, 
			   	vector<vector<string> >*, 
			   	vector<vector<string> >&, 
			   	vector<int>&);

void initProbabilityTables(vector<string>&,
							vector<vector<string> >&,
							vector<map<string, map<string, double> > >&,
							vector<int>&,
							int);

void calculateProbailities(vector<map<string, map<string, double> > >&,
							vector<vector<string> >&,
							map<string, double> &,
							map<string, int>&,
							vector<string>&,
							vector<vector<string> >&,
							vector<int>&,
							map<int,vector<double> >&,
							int);

void calculateClassesSize(map<string, int>&,
							vector<string>&,
							vector<vector<string> >&);

void setContiAttrCutPoint(vector<int>&,
							vector<vector<string> >&,
							map<int,vector<double> >&,
							map<int,vector<double> >&);

string getContiSegment(int, 
						string ,
						map<int,vector<double> >&);

vector<double> stringVecToDouble(vector<string>);