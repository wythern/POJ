#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <time.h>
#include <list>
#include <cmath>
using namespace std;

map<int, set<string>> commonSubString(string& strLhs, string& strRhs){
	//vector<vector<int>> matrix(strLhs.size() + 1, vector<int>(strRhs.size() + 1, 0));
	int w = strLhs.size();
	int h = strRhs.size();
	map<int, set<string>> commonStrs;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int m = i;
			int n = j;
			while (n < strLhs.size() && m < strRhs.size() && strLhs[n] == strRhs[m])
			{
				++m;
				++n;
			}
			string commonStr = strRhs.substr(i, m - i);
			if (!commonStr.empty())
				commonStrs[commonStr.size()].insert(commonStr);
		}
	}

	return commonStrs;
}

string longestSubstring(vector<string>& strings){
	if (strings.empty())
		return string();

	if (strings.size() <= 1)
		return strings[0];

	map<int, set<string>> comSubStrings = commonSubString(strings[0], strings[1]);
	if (comSubStrings.empty() || comSubStrings.rbegin()->first < 3)
		return string();

	vector<string> subStrings;
	map<int, set<string>>::reverse_iterator rIt = comSubStrings.rbegin();
	for (; rIt != comSubStrings.rend(); ++rIt){
		subStrings.insert(subStrings.end(), rIt->second.begin(), rIt->second.end());
	}

	int subStrIdx = 0;
	string longestSubStr = subStrings[subStrIdx];
	for (int i = 2; i < strings.size(); i++)
	{
		while (subStrIdx < subStrings.size()){
			longestSubStr = subStrings[subStrIdx];
			if (strings[i].find(longestSubStr) != string::npos){
				break;
			}
			++subStrIdx;
		}
	}

	return (subStrIdx < subStrings.size()) ? longestSubStr : string();
}

int main(int argc, char** argv){
	int n;
	scanf("%d", &n);
	char buf[64];
	while (n--)
	{
		int m;
		scanf("%d", &m);
		vector<string> DNAs;
		while (m--)
		{
			scanf("%s", buf);
			DNAs.push_back(string(buf));
		}

		string lcs = longestSubstring(DNAs);
		if (lcs.empty())
			cout << "no significant commonalities" << endl;
		else
			cout << lcs << endl;
	}
}