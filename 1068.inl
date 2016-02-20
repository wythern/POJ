#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<int> getWcode(vector<int>& pcode){
	string parenthsis;
	int  leftPbefore = 0;
	for (size_t i = 0; i < pcode.size(); i++)
	{
		for (size_t j = 0; j < pcode[i] - leftPbefore; j++)
		{
			parenthsis.push_back('(');
		}
		parenthsis.push_back(')');
		leftPbefore = pcode[i];
	}

	vector<int> wcode;
	vector<int> leftPidx;
	int lastPairLeft = 0;
	for (size_t i = 0; i < parenthsis.size(); i++)
	{
		if (parenthsis[i] == ')'){
			wcode.push_back(leftPidx.size() - lastPairLeft);
			leftPidx[lastPairLeft] = -1;
			while (lastPairLeft >= 0 && leftPidx[lastPairLeft] == -1)
			{
				lastPairLeft--;
			}
		} else{
			leftPidx.push_back(i);
			lastPairLeft = leftPidx.size() - 1;
		}
	}

	return wcode;
}

int main(int argc, char** argv){
	int n = 0;
	scanf("%d", &n);
	while (n--)
	{
		int k = 0;
		scanf("%d", &k);
		vector<int> pcode(k, 0);
		for(int i = 0; i < k; ++i){
			int l = 0;
			scanf("%d", &l);
			pcode[i] = l;
		}

		vector<int> wcode = getWcode(pcode);
		for (size_t i = 0; i < wcode.size(); i++)
		{
			cout << wcode[i] << ((i == wcode.size() - 1) ? "": " ");
		}
		cout << endl;
	}
	return 0;
}