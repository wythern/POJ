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

#define MAXN 200000
int visited[MAXN];
int N, K;

int dfs(){
	list<int> posStack;
	posStack.push_back(N);
	visited[N] = 1;

	while (!posStack.empty())
	{
		int n = posStack.front();
		posStack.pop_front();

		if (n == K)
			return visited[n] - 1;

		if (visited[n - 1] == 0){
			posStack.push_back(n - 1);
			visited[n - 1] = visited[n] + 1;
		}
		if (n + 1 < MAXN && visited[n + 1] == 0){
			visited[n + 1] = visited[n] + 1;
			posStack.push_back(n + 1);
		}
		if (((n << 1) < K + 2) && visited[n << 1] == 0){
			visited[n << 1] = visited[n] + 1;
			posStack.push_back(n << 1);
		}
	}

	return 0;
}

int main(){
	while (scanf("%d %d", &N, &K) != EOF)
	{
		cout << dfs() << endl;
	}

	return 0;
}