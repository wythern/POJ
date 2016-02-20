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

char scenario[41][11];

struct Node
{
	Node() : ch('o'){}
	int x;
	int y;
	char ch;
	vector<int> links;
};

vector<pair<int, int>> findAugPath(int k, vector<Node>& nodes, vector<int>& checked, vector<int>& matched){
	Node curr = nodes[k];
	vector<pair<int, int>> augPath;

	for (size_t i = 0; i < curr.links.size(); i++)
	{
		int subId = curr.links[i];
		Node next = nodes[subId];
		if (checked[subId] == 0){
			checked[subId] = 1;

			if (matched[subId] == -1)
			{
				augPath.push_back(pair<int, int>(k, subId));
				break;
			} else{
				vector<pair<int, int>> subPath = findAugPath(matched[subId], nodes, checked, matched);
				if (!subPath.empty()){
					augPath.push_back(pair<int, int>(k, subId));
					augPath.push_back(pair<int, int>(subId, matched[subId]));
					augPath.insert(augPath.end(), subPath.begin(), subPath.end());
					break;
				}
			}
		}
	}

	return augPath;
}

int minBiPartiteCoverage(vector<Node>& nodes, vector<int>& checked, vector<int>& matched){
	int minCoverage = 0;
	int nodeCnt = 0;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		checked = vector<int>(nodes.size(), 0);
		if (nodes[i].ch == '*'){
			if (matched[i] == -1){
				vector<pair<int, int>> augPath = findAugPath(i, nodes, checked, matched);
				for (size_t j = 0; j < augPath.size(); j++)
				{
					if ((j + 1) % 2){
						matched[augPath[j].first] = augPath[j].second;
						matched[augPath[j].second] = augPath[j].first;
					}
				}
			}
			nodeCnt++;
		}
	}

	for (size_t i = 0; i < matched.size(); i++)
	{
		if (matched[i] != -1)
			minCoverage++;
	}

	return nodeCnt - minCoverage / 2;
}

vector<Node> buildBiPartite(int w, int h, char scenario[][11]){
	vector<Node> nodes(w*h, Node());
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			if (scenario[i][j] == '*'){
				Node& node = nodes[i*w + j];
				node.ch = '*';
				node.x = j;
				node.y = i;
				if (i - 1 >= 0 && scenario[i - 1][j] == '*')
					node.links.push_back((i - 1)*w + j);
				if (j - 1 >= 0 && scenario[i][j - 1] == '*')
					node.links.push_back(i * w + (j - 1));
				if (i + 1 < h && scenario[i + 1][j] == '*')
					node.links.push_back((i + 1)* w + j);
				if (j + 1 < w && scenario[i][j + 1] == '*')
					node.links.push_back(i * w + (j + 1));
			}
		}
	}

	return nodes;
}

int minCoverage(int w, int h, char scenario[][11]){
	vector<Node> nodes;
	nodes = buildBiPartite(w, h, scenario);
	vector<int> checked(nodes.size(), 0);
	vector<int> matched(nodes.size(), -1);
	return minBiPartiteCoverage(nodes, checked, matched);
}

int test3020(int argc, char** argv){
	int n;
	scanf("%d", &n);
	while (n--){
		int h, w;
		scanf("%d %d", &h, &w);
		for (int i = 0; i < h; ++i)	{
			scanf("%s", scenario[i]);
		}

		cout << minCoverage(w, h, scenario) << endl;
	}
	return 0;
}

#include <time.h>
void generateTestCases(){
	time_t seed = time(NULL);
	srand((int)seed);

	FILE* fp = fopen("1.input", "w");
	int n = 100;
	char buf[100];
	sprintf(buf, "%d\n", n);
	fwrite(buf, sizeof(char), strlen(buf), fp);
	while (n--)
	{
		int w = rand() % 10 + 1;
		int h = rand() % 40 + 1;
		sprintf(buf, "%d %d\n", h, w);
		fwrite(buf, sizeof(char), strlen(buf), fp);
		for (size_t i = 0; i < h; i++)
		{
			for (size_t j = 0; j < w; j++)
			{
				if (rand() > RAND_MAX / 2){
					buf[j] = '*';
				} else{
					buf[j] = 'o';
				}
			}
			buf[w] = '\n';
			buf[w + 1] = '\0';
			fwrite(buf, sizeof(char), strlen(buf), fp);
		}
	}
	fclose(fp);
}


const int maxn = 40 * 10 + 10;
int matrix[45][15];

int g[maxn][maxn];
int linker[maxn];
int vis[maxn];
int uN, vN;


bool dfs(int u)
{
	for (int v = 1; v <= vN; v++)
	{
		if (!vis[v] && g[u][v])
		{
			vis[v] = 1;
			if (linker[v] == -1 || dfs(linker[v]))
			{
				linker[v] = u;
				return true;
			}
		}
	}
	return false;
}

int hungary()
{
	int sum = 0;
	memset(linker, -1, sizeof(linker));
	for (int u = 1; u <= uN; u++)
	{
		memset(vis, 0, sizeof(vis));
		if (dfs(u))
			sum++;
	}
	return sum;
}

int reference()
{
	int T;
	int row, col;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%*c", &row, &col);

		char c;
		int num = 0; //记录有多少个点  
		memset(matrix, 0, sizeof(matrix));
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= row; i++) //从 1 开始, matrix[][]周围加边  
		{
			for (int j = 1; j <= col; j++)
			{
				scanf("%c", &c);
				if (c == '*') matrix[i][j] = ++num;
			}
			getchar();
		}
		uN = vN = num;

		for (int i = 1; i <= row; i++) //建图  
		{
			for (int j = 1; j <= col; j++)
			{
				if (matrix[i][j])
				{
					if (matrix[i][j + 1])
						g[matrix[i][j]][matrix[i][j + 1]] = 1;
					if (matrix[i][j - 1])
						g[matrix[i][j]][matrix[i][j - 1]] = 1;
					if (matrix[i + 1][j])
						g[matrix[i][j]][matrix[i + 1][j]] = 1;
					if (matrix[i - 1][j])
						g[matrix[i][j]][matrix[i - 1][j]] = 1;
				}
			}
		}
		printf("%d\n", num - hungary() / 2); //最小路径覆盖数  
	}
	return 0;
}

int main(int argc, char** argv){
	test3020(0, NULL);
	//reference();
	return 0;
}
