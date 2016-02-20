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
#define MAXN 32

int unionset[MAXN];
int unionsize[MAXN];

int doFind(int a){
	while (a != unionset[a])
	{
		a = unionset[a];
	}
	return a;
}

void doUnion(int a, int b){
	int setIda = doFind(a);
	int setIdb = doFind(b);
	int newSize = unionsize[setIda] + unionsize[setIdb];
	if (unionsize[setIda] < unionsize[setIdb])
		std::swap(a, b);

	unionset[setIdb] = setIda;
	unionsize[setIda] = newSize;
}

int N;
struct Cost{
	int cost;
	int i;
	int j;

	bool operator < (const Cost& rhs) const{
		return cost > rhs.cost;
	}
};
Cost cost[MAXN][MAXN];
int visited[MAXN];
int main(){
	while (scanf("%d", &N) != EOF){
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				scanf("%d", &cost[i][j].cost);
				cost[i][j].i = i;
				cost[i][j].j = j;
			}
		}

		vector<Cost> costs;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = i + 1; j < N; j++)
			{
				costs.push_back(cost[i][j]);
			}
		}

		std::sort(costs.begin(), costs.end());
		for (int i = 0; i < MAXN; ++i){
			unionset[i] = i;
			unionsize[i] = 1;
			visited[i] = 0;
		}

		int ans = 0;
		for (size_t i = 0; i < costs.size(); i++)
		{
			if (visited[costs[i].i] == 0 || visited[costs[i].j] == 0){
				ans += costs[i].cost;
				doUnion(costs[i].i, costs[i].j);
				visited[costs[i].i] = 1;
				visited[costs[i].j] = 1;
				//cout << " Add " << costs[i].cost;
			} else if (doFind(costs[i].i) != doFind(costs[i].j)){
				ans += costs[i].cost;
				doUnion(costs[i].i, costs[i].j);
				//cout << " Add " << costs[i].cost;
			}
		}

		cout << ans << endl;
	}

	return 0;
}

#else

#include <stdio.h>  
#include <string.h>  

const bool A = true;
const bool B = false;

int c[32][32];
int n, ans;
bool setId[32];

void dfs(int depth, int sum)
{
	if (depth >= n){
		if (sum > ans){
			ans = sum;
		}
		return;
	}

	int t = 0;
	setId[depth] = A;
	for (int i = 0; i < depth; i++)
	if (setId[i] == B){
		t += c[depth][i];
	}
	dfs(depth + 1, sum + t);

	t = 0;
	setId[depth] = B;
	for (int i = 0; i < depth; i++)
	if (setId[i] == A){
		t += c[i][depth];
	}
	dfs(depth + 1, sum + t);

}

int main()
{
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &c[i][j]);
		ans = 0;
		setId[0] = A;
		dfs(1, 0);

		printf("%d\n", ans);
	}

	return 0;
}
#endif