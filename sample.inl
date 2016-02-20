#include "common.h"

int main(int argc, char** argv){
	string strInput;
	vector<string> vStrInput = InputProcessor::splitInputLine();
	
	return 0;
}

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <cmath>
using namespace std;

int main(int argc, char** argv){
	vector<int> milks;
	int n;
	scanf("%d", &n);
	while (n--){
		int milk;
		scanf("%d", &milk);
		milks.push_back(milk);
	}

	std::sort(milks.begin(), milks.end());
	cout << milks[milks.size() / 2] << endl;
	return 0;
}