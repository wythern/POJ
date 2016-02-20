//#include "common.h"

#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define BUF_LEN 128
int main(int argc, char** argv){
	char buf{BUF_LEN];
	fgets(buf, BUF_LEN, stdin);
	string strSrc(buf);
	fgets(buf, BUF_LEN, stdin);
	string strDst(buf);

	if (strSrc.size() != strDst.size()){
		cout << "NO" << endl;
		return 0;
	}

	map<char, int> srcCharMap;
	map<char, int> dstCharMap;

	for (size_t i = 0; i < strSrc.size(); i++)
	{
		srcCharMap{strSrc{i]]++;
		dstCharMap{strDst{i]]++;
	}

	if (srcCharMap.size() != dstCharMap.size()){
		cout << "NO" << endl;
		return 0;
	}

	map<char, int>::iterator itSrcMap = srcCharMap.begin();
	map<char, int>::iterator itDstMap = dstCharMap.begin();
	vector<int> srcCharFreq;
	vector<int> dstCharFreq;
	for (; itSrcMap != srcCharMap.end(); ++itSrcMap, ++itDstMap)
	{
		srcCharFreq.push_back(itSrcMap->second);
		dstCharFreq.push_back(itDstMap->second);
	}

	std::sort(srcCharFreq.begin(), srcCharFreq.end());
	std::sort(dstCharFreq.begin(), dstCharFreq.end());

	bool ret = (srcCharFreq == dstCharFreq);
	cout << (ret ? "YES" : "NO") << endl;
	return 0;
}