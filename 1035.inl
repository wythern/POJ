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


class Trie{
public:
	Trie() : m_ch(0xFF)
		, m_complete(false)
	{}

	~Trie(){
		m_subTree.clear();
	}

	void addToTrie(string& str, int idx){
		return addToTrieImpl(str, 0, idx);
	}

	bool match(string& str) const{
		if (str.empty())
			return false;

		return matchImpl(str, 0);
	}

	bool matchImpl(string& str, int pos) const {
		if (pos == str.size())
			return m_complete;

		Trie node;
		node.m_ch = str[pos];
		set<Trie>::iterator it = m_subTree.find(node);
		if (it != m_subTree.end())
			return it->matchImpl(str, pos + 1);
		return false;
	}

	vector<int> specialMatch(string& str) const {
		// support '*' match any char & '~' skip one char
		vector<int> matched;
		string trieStr;
		specialMatchImpl(str, 0, matched);
		return matched;
	}

	void specialMatchImpl(string& str, int pos, vector<int>& matched) const{
		// support '*' match any char & '~' skip one char
		if (pos == str.size()){
			if (m_complete)
				matched.push_back(m_idx);
			return;
		}

		if (str[pos] == '~'){
			return specialMatchImpl(str, pos + 1, matched);
		}

		if (str[pos] == '*'){
			for (set<Trie>::iterator it = m_subTree.begin(); it != m_subTree.end(); it++)
			{
				(*it).specialMatchImpl(str, pos + 1, matched);
			}
			return;
		}

		Trie node;
		node.m_ch = str[pos];
		set<Trie>::iterator it = m_subTree.find(node);
		if (it != m_subTree.end())
			it->specialMatchImpl(str, pos + 1, matched);
	}

	bool operator < (const Trie& rhs) const{
		return m_ch < rhs.m_ch;
	}

private:
	void addToTrieImpl(string& str, int pos, int idx) const {
		if (pos == str.size()){
			m_complete = true;
			m_idx = idx;
			return;
		}

		Trie node;
		node.m_ch = str[pos];
		set<Trie>::iterator it = m_subTree.find(node);
		if (it != m_subTree.end()){

			it->addToTrieImpl(str, pos + 1, idx);
		}

		Trie* pTrie = new Trie();
		pTrie->m_ch = str[pos];
		pTrie->addToTrieImpl(str, pos + 1, idx);
		m_subTree.insert(*pTrie);
	}

private:
	char m_ch;
	mutable bool m_complete;
	mutable int  m_idx;
	mutable set<Trie> m_subTree;
};

int editDistance(string& strlhs, string& strrhs){
	//vector<vector<int>> matrix(strlhs.size(), vector<int>(strrhs.size(), 0));
	int matrix[51][51];
	int w = strrhs.size();
	int h = strlhs.size();
	matrix[h][w] = 0;
	for (int i = 0; i <= h; i++)
	{
		for (int j = 0; j <= w; j++)
		{
			if (i == 0){
				matrix[i][j] = j;
			} else if (j == 0){
				matrix[i][j] = i;
			} else{
				int up = matrix[i - 1][j];
				int left = matrix[i][j - 1];
				int diag = matrix[i - 1][j - 1];
				int delta = (strlhs[i - 1] != strrhs[j - 1]);
				int dist = std::min(up + 1, std::min(left + 1, diag + delta));
				matrix[i][j] = dist;
			}
		}
	}

	return matrix[h][w];
}

int test1035(){
	char buf[128];
	map<int, Trie> dictByLen;
	vector<string> orderStr;
	int order = 0;
	while (true)
	{
		scanf("%s", buf);
		if (buf[0] == '#'){
			break;
		}

		string word(buf);
		dictByLen[word.size()].addToTrie(word, order++);
		orderStr.push_back(word);
	}

	while (true)
	{
		scanf("%s", buf);
		if (buf[0] == '#'){
			break;
		}

		string word(buf);

		if (dictByLen[word.size()].match(word))
			printf("%s is correct\n", buf);
		else{
			// test delete
			string bakWord(word);
			set<int> matched;
			for (size_t i = 0; i < word.size(); i++)
			{
				word[i] = '~';
				vector<int> deleteMatched = dictByLen[word.size() - 1].specialMatch(word);
				matched.insert(deleteMatched.begin(), deleteMatched.end());
				word[i] = bakWord[i];
			}

			// test replace
			for (size_t i = 0; i < word.size(); i++)
			{
				word[i] = '*';
				vector<int> replaced = dictByLen[word.size()].specialMatch(word);
				matched.insert(replaced.begin(), replaced.end());
				word[i] = bakWord[i];
			}

			// test add
			for (size_t i = 0; i < word.size() + 1; i++)
			{
				string wordplus = word.substr(0, i) + '*' + word.substr(i);
				vector<int> added = dictByLen[wordplus.size()].specialMatch(wordplus);
				matched.insert(added.begin(), added.end());
			}

			string candidates;
			set<int>::iterator it = matched.begin();
			for (size_t i = 0; i < matched.size(); i++, it++)
			{
				candidates += string(" ") + orderStr[*it];
			}

			printf("%s:%s\n", word.c_str(), candidates.c_str());
		}
	}

	return 0;
}

int test1035_editdistance(){
	char buf[128];
	map<int, vector<int>> dictByLen;
	vector<string> dictNoOrder;
	set<string> dict;
	int order = 0;
	while (true)
	{
		scanf("%s", buf);
		if (buf[0] == '#'){
			break;
		}

		string word(buf);
		dictByLen[word.size()].push_back(order++);
		dictNoOrder.push_back(word);
		dict.insert(word);
	}

	while (true)
	{
		scanf("%s", buf);
		if (buf[0] == '#'){
			break;
		}

		string word(buf);

		if (dict.find(word) != dict.end())
			printf("%s is correct\n", buf);
		else{
			set<int> matched;
			// test delete
			for (size_t i = 0; i < dictByLen[word.size() - 1].size(); i++)
			{
				if (editDistance(word, dictNoOrder[dictByLen[word.size() - 1][i]]) == 1)
					matched.insert(dictByLen[word.size() - 1][i]);
			}

			// test replace
			for (size_t i = 0; i < dictByLen[word.size()].size(); i++)
			{
				if (editDistance(word, dictNoOrder[dictByLen[word.size()][i]]) == 1)
					matched.insert(dictByLen[word.size()][i]);
			}

			// test replace
			for (size_t i = 0; i < dictByLen[word.size() + 1].size(); i++)
			{
				if (editDistance(word, dictNoOrder[dictByLen[word.size() + 1][i]]) == 1)
					matched.insert(dictByLen[word.size() + 1][i]);
			}

			//std::sort(matched.begin(), matched.end());
			string candidates;
			set<int>::iterator it = matched.begin();
			for (size_t i = 0; i < matched.size(); i++)
			{
				candidates += string(" ") + dictNoOrder[*it++];
			}

			printf("%s:%s\n", word.c_str(), candidates.c_str());
		}
	}

	return 0;
}

int generateTestcases(){
	time_t seed = time(NULL);
	srand((int)seed);

	FILE* fp = fopen("1.input", "w");
	int n = 5000;
	char buf[100];
	set<string> dict;
	while (n--)
	{
		int w = rand() % 14 + 1;
		for (size_t i = 0; i < w; i++)
		{
			char ch = 'a' + rand() % 26;
			buf[i] = ch;
		}
		buf[w] = '\n';
		buf[w + 1] = '\0';
		if (dict.insert(string(buf)).second)
			fwrite(buf, sizeof(char), strlen(buf), fp);
	}

	buf[0] = '#';
	buf[1] = '\n';
	buf[2] = '\0';
	fwrite(buf, sizeof(char), strlen(buf), fp);

	n = 5000;
	dict.clear();
	while (n--)
	{
		int w = rand() % 14 + 1;
		for (size_t i = 0; i < w; i++)
		{
			char ch = 'a' + rand() % 26;
			buf[i] = ch;
		}
		buf[w] = '\n';
		buf[w + 1] = '\0';
		if (dict.insert(string(buf)).second)
			fwrite(buf, sizeof(char), strlen(buf), fp);
	}

	buf[0] = '#';
	buf[1] = '\n';
	buf[2] = '\0';
	fwrite(buf, sizeof(char), strlen(buf), fp);

	fclose(fp);
	return 0;
}


#define SIZE 11000  
char dic[SIZE][20];
int cnt;
void read_dic()//读取字典  
{
	cnt = 0;
	while (scanf("%s%*c", dic[cnt]))
	{
		if (dic[cnt][0] == '#')
			break;
		else
			cnt++;
	}
}
bool isCor(char *str)//是否正确   
{
	int i;
	for (i = 0; i<cnt; i++)
	if (strcmp(dic[i], str) == 0)return true;
	return false;
}
void Replace(char *str)//替换  
{
	printf("%s:", str);
	int i, j, k, arr[20], diff, isSort;
	int ls = strlen(str), ld;
	for (i = 0; i<cnt; i++)
	{
		ld = strlen(dic[i]);
		if (ls == ld)//如果长度相同   
		{
			diff = 0;
			for (j = 0; j<ld; j++)
			{
				if (str[j] != dic[i][j]) diff++;
			}
			if (diff == 1)printf(" %s", dic[i]);
		} else if (ls == ld + 1)//delete  
		{
			memset(arr, -1, sizeof(arr));
			for (j = 0; j<ld; j++)
			{
				for (k = j == 0 ? 0 : arr[j - 1] + 1; k<ls; k++)
				{
					if (str[k] == dic[i][j])
					{
						arr[j] = k;
						break;
					}
				}
			}
			isSort = 1;
			//检查arr是否有序  
			for (j = 0; j<ld - 1; j++)
			{
				if (arr[j + 1]<arr[j] || arr[j] == -1)
				{
					isSort = 0;
					break;
				}
			}
			if (arr[ld - 1] == -1)isSort = 0;
			if (isSort)printf(" %s", dic[i]);
		} else if (ls + 1 == ld)//add  
		{
			memset(arr, -1, sizeof(arr));
			for (j = 0; j<ls; j++)
			{
				for (k = j == 0 ? 0 : arr[j - 1] + 1; k<ld; k++)
				{
					if (str[j] == dic[i][k])
					{
						arr[j] = k;
						break;
					}
				}
			}
			isSort = 1;
			//检查arr是否有序  
			for (j = 0; j<ls - 1; j++)
			{
				if (arr[j + 1]<arr[j] || arr[j] == -1)
				{
					isSort = 0;
					break;
				}
			}
			if (arr[ls - 1] == -1)isSort = 0;
			if (isSort)printf(" %s", dic[i]);
		}
	}
}
int reference()
{
	//freopen("in.txt","r",stdin);  
	//freopen("out.txt","w",stdout);  
	read_dic();
	char str[20];
	while (scanf("%s%*c", str), str[0] != '#')
	{
		if (isCor(str))
			printf("%s is correct\n", str);
		else
		{
			Replace(str);
			printf("\n");
		}
	}
	return 0;
}

int main(int argc, int argv){
	//generateTestcases();
	//return reference();
	return test1035_editdistance();
}
