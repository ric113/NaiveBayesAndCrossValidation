#include <iostream>
#include <map>
#include <vector>

using namespace std;

void cvProcess(vector<vector<string> >&, vector<map<string, vector<int> > >&, vector<int>*, vector<int>*, string);
void calculateClassAmountPerFold(map<string,int>&, vector<map<string, vector<int> > >&, int);
void setFolds(vector<vector<string> >&, vector<map<string, vector<int> > >&, vector<int>*, vector<int>*, map<string,int>&, string);