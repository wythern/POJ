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

char matrix[10][10];
int visited[10];

int dfs(int n, int k, int cnt){
	if (k == 0)
		return 1;

	if (cnt >= n*n)
		return 0;

	while (cnt < n*n){
		int i = cnt / n;
		int j = cnt % n;
		if (matrix[i][j] == '#' && visited[j] == 0){
			visited[j] = 1;
			int ans = dfs(n, k - 1, cnt + (n - j));
			visited[j] = 0;
			ans += dfs(n, k, cnt + 1);
			return ans;
		}
		++cnt;
	}

	return 0;
}

int main(){
	while (true)
	{
		int n, k;
		scanf("%d %d", &n, &k);
		if (n == -1 || k == -1)
			break;

		memset(visited, 0x0, sizeof(visited));
		for (size_t i = 0; i < n; i++)
		{
			{
				scanf("%s", matrix[i]);
			}
		}

		cout << dfs(n, k, 0) << endl;
	}

	return 0;
}