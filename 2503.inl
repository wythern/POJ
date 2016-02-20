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

class HashDictionary{
public:
	HashDictionary(){
		m_hashNum = 96581;
		m_storage.resize(m_hashNum);
		m_conflict = 0;
	}

	void insert(string& str, string& translation){
		m_storage[calcHashValue(str)].push_back(pair<string, string>(str, translation));
		/*
		if (m_storage[calcHashValue(str)].size() > 2){
			m_conflict++;
		}*/
	}

	string lookup(string& str){
		vector<pair<string, string>>& dict = m_storage[calcHashValue(str)];
		vector<pair<string, string>>::iterator it = dict.begin();
		while (it != dict.end()){
			if (it->first == str)
				return it->second;
			++it;
		} 

		return string("eh");
	}

	int getConflictCnt(){
		return m_conflict;
	}
private:
	int calcHashValue(string& str){
		long long v = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			v = (v + str[i]) * 26;
		}
		
		return v%m_hashNum;
	}

private:
	int m_hashNum;
	vector<vector<pair<string, string>>> m_storage;
	int m_conflict;
};

#include <time.h>
void generateTestCases(){
	time_t seed = time(NULL);
	srand((int)seed);

	FILE* fp = fopen("1.input", "w");
	int n = 100000;
	char buf[100];
	while (n--)
	{
		int strl = rand() % 10 + 1;
		int transl = rand() % 10 + 1;
		int pos = 0;
		for (; pos < strl; pos++)
		{
			buf[pos] = rand() % 26 + 'a';
		}
		buf[pos++] = ' ';
		for (int i = 0; i < transl; i++)
		{
			buf[pos + i] = rand() % 26 + 'a';
		}

		buf[pos + transl] = '\n';
		buf[pos + transl + 1] = '\0';
		fwrite(buf, sizeof(char), strlen(buf), fp);
	}

	buf[0] = '\n';
	buf[1] = '\0';
	fwrite(buf, sizeof(char), strlen(buf), fp);

	n = 100000;
	for (size_t i = 0; i < n; i++)
	{
		int strl = rand() % 10 + 1;
		for (size_t j = 0; j < strl; j++)
		{
			buf[j] = rand() % 26 + 'a';
		}
		buf[strl] = '\n';
		buf[strl + 1] = '\0';
		fwrite(buf, sizeof(char), strlen(buf), fp);
	}

	buf[0] = '\n';
	buf[1] = '\0';
	fwrite(buf, sizeof(char), strlen(buf), fp);
	fclose(fp);
}

int main(int argc, char** argv){
	//generateTestCases();
	char buf[64];
	char str1[16];
	char str2[16];
	HashDictionary hd;
	int ret = 2;
	//cout << "TimeStamp: " << clock() << endl;
	//FILE* fp = fopen("2.input", "r");
	while (fgets(buf, sizeof(buf), stdin))
	{
		if (buf[0] == '\n'){
			//cout << "TimeStamp: " << clock() << endl;
			ret = 1;
			continue;
		}

		if (ret == 2){
			sscanf(buf, "%s %s", str1, str2);
			string str(str2);
			string translation(str1);
			hd.insert(str, translation);
		} else if (ret == 1){
			sscanf(buf, "%s", str1);
			string foreign(str1);
			cout << hd.lookup(foreign) << endl;
		}
	}
	//cout << "conflict count: " << hd.getConflictCnt() << endl;
	//cout << "TimeStamp: " << clock() << endl;
	return 0;
}