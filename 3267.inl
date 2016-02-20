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
#include <queue>
#include <numeric>
#include <functional>
#include <cmath>
using namespace std;

struct Trie{
	Trie(){
		m_bEnd = false;
		memset(subNodes, 0, sizeof(subNodes));
	}

	void clear(){
		for (size_t i = 0; i < 26; i++)
		{
			if (subNodes[i] != NULL){
				subNodes[i]->clear();
				delete subNodes[i];
			}
			subNodes[i] = NULL;
		}

		m_bEnd = false;
	}

	void insert(char* pszWord){
		int idx = 0;
		Trie* pCurr = this;
		//Trie* pNext = NULL;
		while (pszWord[idx] != '\0'){
			Trie*& pNext = pCurr->subNodes[pszWord[idx] - 'a'];
			if (pNext == NULL){
				pNext = new Trie;
			}
			idx++;
			pCurr = pNext;
		}

		if (pCurr != NULL)
			pCurr->m_bEnd = true;
	}

	bool m_bEnd;
	Trie* subNodes[26];
};

Trie dict;
int W, L;
char message[320];
char word[32];
int dp[320][320];
int dpDict[320][320];

int removeToFitDict(int s, int e){
	if (s == e)
		return 0;

	if (dpDict[s][e] != -1)
		return dpDict[s][e];

	int minRemove = e - s;
	for (int idx = s; idx < e; ++idx){
		Trie* pCurr = &dict;

		int remove = 0;
		int pos = idx;
		while (pos < e)
		{
			Trie* pNext = pCurr->subNodes[message[pos] - 'a'];
			if (pNext == NULL){
				++remove;
				++pos;
				continue;
			}

			++pos;
			pCurr = pNext;
		}

		if (pCurr->m_bEnd && minRemove > remove + idx - s)
			minRemove = remove + idx - s;
	}

	dpDict[s][e] = minRemove;
	return minRemove;
}

int calcLeastRemove(int s, int e){
	if (s == e)
		return 0;

	if (dp[s][e] != -1)
		return dp[s][e];

	int remove = e - s;
	for (int i = s + 1; i <= e; i++)
	{
		remove = std::min(remove, removeToFitDict(s, i) + calcLeastRemove(i, e));
	}
	dp[s][e] = remove;
	return remove;
}

int main(){
	while (scanf("%d %d", &W, &L) != EOF)
	{
		memset(dp, 0xFF, sizeof(dp));
		memset(dpDict, 0xFF, sizeof(dpDict));
		dict.clear();
		scanf("%s", message);
		for (size_t i = 0; i < W; i++)
		{
			scanf("%s", word);
			dict.insert(word);
		}

		cout << calcLeastRemove(0, L) << endl;
	}
	return 0;
}