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

#if 0
struct Square{
	int x;
	int y;
	vector<int> links;
};

vector<Square> chessMap;

void buildGraph(int p, int q){
	int vCnt = p*q;
	chessMap.resize(vCnt);
	for (size_t y = 0; y < p; y++)
	{
		for (size_t x = 0; x < q; x++)
		{
			chessMap[y*q + x].x = x;
			chessMap[y*q + x].y = y;

			for (int i = -2; i <= 2; i++)
			{
				for (int j = -2; j <= 2; j++)
				{
					if (abs(i) + abs(j) == 3){
						if (y + i >= 0 && y + i < p && x + j >= 0 && x + j < q){
							chessMap[y*q + x].links.push_back((y + i)*q + x + j);
						}
					}
				}
			}		
		}
	}
}

vector<int> visited;
vector<int> path;
bool dfs(vector<Square>& chessMap, int start){
	vector<int>& links = chessMap[start].links;
	for (size_t i = 0; i < links.size(); i++)
	{
		if (visited[links[i]] == 0){
			visited[links[i]] = 1;
			path.push_back(links[i]);
			if (dfs(chessMap, links[i])){
				return true;
			}
			path.pop_back();
			visited[links[i]] = 0;
		}
	}

	return path.size() == visited.size();
}

int main(int argc, char** argv){
	int n;
	scanf("%d", &n);
	int cnt = 0;
	while (n--)
	{
		int p, q;
		scanf("%d %d", &p, &q);
		chessMap.clear();
		buildGraph(p, q);
		visited = vector<int>(p*q, 0);
		path.clear();

		bool ret = false;
		for (int i = 0; i < chessMap.size(); i++)
		{
			visited[i] = 1;
			path.push_back(i);
			if (ret = dfs(chessMap, i))
				break;
			path.pop_back();
			visited[i] = 0;
		}

		cout << "Scenario #" << ++cnt << ":" << endl;
		if (!ret){
			cout << "impossible" << endl;
		} else{
			for (size_t i = 0; i < path.size(); i++)
			{
				cout << char(chessMap[path[i]].x + 'A') << chessMap[path[i]].y + 1;
			}
			cout << endl;
		}
		if (n)
			cout << endl;
	}
}

#else

#include <stdio.h>  
#include <string.h>  

const int dir[8][2] = { /// 字典序最小的走法顺序  
	{ -2, -1 }, { -2, 1 }, { -1, -2 }, { -1, 2 },
	{ 1, -2 }, { 1, 2 }, { 2, -1 }, { 2, 1 } };

struct Path{
	int x, y;
};
Path path[32 * 32 + 1];
bool mm[32][32];
int p, q;

bool dfs(int x, int y, int order)
{
	mm[x][y] = true;
	path[order].x = x;
	path[order].y = y;
	if (order == p*q)
		return true;

	int xt, yt;
	for (int i = 0; i < 8; i++){
		xt = x + dir[i][0];
		yt = y + dir[i][1];
		if (1 <= xt&&xt <= q && 1 <= yt&&yt <= p && !mm[xt][yt]){
			if (dfs(xt, yt, order + 1))
				return true;
		}
	}
	mm[x][y] = false; /// 回溯时忘记修复现场了，WA，~~~~(>_<)~~~~   
	return false;
}
int main()
{
	int t, cnt = 0;
	scanf("%d", &t);
	while (t--){
		scanf("%d %d", &p, &q);

		memset(mm, 0, sizeof(mm));

		printf("Scenario #%d:\n", ++cnt);
		if (!dfs(1, 1, 1)){
			printf("impossible\n");
		} else{
			for (int i = 1; i <= p*q; i++)
				printf("%c%d", (char)(path[i].x + 'A' - 1), path[i].y);
			printf("\n");
		}
		if (t)
			printf("\n");
	}
	return 0;
}

#endif