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

#define MAXL 32
char visited[MAXL][MAXL];
int maze[MAXL][MAXL];
int dist[MAXL][MAXL];

int dir[][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };

int dfs(int x, int y, int w, int h){
	int step = 0;
	list<pair<int, int>> stackCood;
	stackCood.push_back(pair<int, int>(x, y));
	visited[y][x] = 1;
	while (!stackCood.empty())
	{
		pair<int, int> cood = stackCood.front();
		stackCood.pop_front();
		step++;
		if (step > 10)
			break;

		for (size_t i = 0; i < 4; i++)
		{
			int xx = cood.first;
			int yy = cood.second;
			int space = 0;
			while (yy + dir[i][0] >= 0 && yy + dir[i][0] < h &&  xx + dir[i][1] >= 0 && xx + dir[i][1] < w && maze[yy + dir[i][0]][xx + dir[i][1]] == 0)
			{
				yy += dir[i][0];
				xx += dir[i][1];
				space++;
			}

			if (yy + dir[i][0] >= 0 && yy + dir[i][0] < h &&  xx + dir[i][1] >= 0 && xx + dir[i][1] < w){
				if (maze[yy + dir[i][0]][xx + dir[i][1]] == 3)
					return visited[cood.second][cood.first];
				if (maze[yy + dir[i][0]][xx + dir[i][1]] == -1)
					continue;

				// maze[yy][xx] == 0 && next pos is 1(wall);
				//if (visited[yy][xx] == 0)
				if(space > 0)
				{
					maze[yy + dir[i][0]][xx + dir[i][1]] = 0;
					stackCood.push_back(pair<int, int>(xx, yy));
					visited[yy][xx] = visited[cood.second][cood.first] + 1;
				}
			}
		}
	}

	return -1;
}

int bfsImpl(int x, int y, int w, int h, int step, int limit){
	if (step >= limit)
		return -1;

	int ans = -1;
	for (size_t i = 0; i < 4; i++)
	{
		int xx = x;
		int yy = y;
		int space = 0;
		while (yy + dir[i][1] >= 0 && yy + dir[i][1] < h &&  xx + dir[i][0] >= 0 && xx + dir[i][0] < w && maze[yy + dir[i][1]][xx + dir[i][0]] == 0)
		{
			xx += dir[i][0];
			yy += dir[i][1];
			space++;
		}

		int ret = -1;
		if (yy + dir[i][1] >= 0 && yy + dir[i][1] < h &&  xx + dir[i][0] >= 0 && xx + dir[i][0] < w){
			if (maze[yy + dir[i][1]][xx + dir[i][0]] == 3)
				return step + 1;
			if (maze[yy + dir[i][1]][xx + dir[i][0]] == -1)
				continue;

			if (space > 0)
			{
				maze[yy + dir[i][1]][xx + dir[i][0]] = 0;
				ret = bfsImpl(xx, yy, w, h, step + 1, limit);
				if (ret > 0){
					limit = std::min(limit, ret);
					ans = limit;
				}
				maze[yy + dir[i][1]][xx + dir[i][0]] = 1;
			}
		}
	}

	return ans;
}

int bfs(int x, int y, int w, int h){
	bool ret = false;
	int step = 0;
	return bfsImpl(x, y, w, h, step, 10);
}

int main(){
	int w, h;
	while (true)
	{
		scanf("%d %d", &w, &h);
		if (w == 0 || h == 0)
			return 0;

		memset(maze, 0xFF, sizeof(maze));
		memset(visited, 0, sizeof(visited));
		int x, y;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				scanf("%d", &maze[i][j]);
				if (maze[i][j] == 2){
					y = i;
					x = j;
					maze[i][j] = 0;
				}
			}
		}

		int step = bfs(x, y, w, h);
		cout << step << endl;
	}

	return 0;
}