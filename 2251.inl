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
int L, R, C;
char maze[MAXL][MAXL][MAXL];
int visited[MAXL][MAXL][MAXL];

struct PositionTuple
{
	int l;
	int r;
	int c;
};

PositionTuple bePt[2];

int dfs(){
	list<PositionTuple> tupleStack;
	tupleStack.push_back(bePt[0]);
	visited[bePt[0].l][bePt[0].r][bePt[0].c] = 1;

	while (!tupleStack.empty())
	{
		PositionTuple pos = tupleStack.front();
		tupleStack.pop_front();

		if (0 == memcmp(&pos, &bePt[1], sizeof(pos)))
			return visited[pos.l][pos.r][pos.c] - 1;

		for (int l = -1; l <= 1; l++)
		{
			for (int r = -1; r <= 1; r++)
			{
				for (int c = -1; c <= 1; c++){
					if (abs(l) + abs(r) + abs(c) == 1 &&
						pos.l + l >= 0 && pos.l + l < L &&
						pos.r + r >= 0 && pos.r + r < R &&
						pos.c + c >= 0 && pos.c + c < C &&
						maze[pos.l + l][pos.r + r][pos.c + c] != '#' &&
						visited[pos.l + l][pos.r + r][pos.c + c] == 0){
						PositionTuple nextPos;
						nextPos.l = pos.l + l;
						nextPos.r = pos.r + r;
						nextPos.c = pos.c + c;
						visited[nextPos.l][nextPos.r][nextPos.c] = visited[pos.l][pos.r][pos.c] + 1;
						tupleStack.push_back(nextPos);
					}
				}
			}
		}
	}

	return 0;
}

int main(){
	while (true)
	{
		scanf("%d %d %d", &L, &R, &C);
		if (L == 0 || R == 0 || C == 0)
			break;

		memset(visited, 0, sizeof(visited));
		for (int l = 0; l < L; l++)
		{
			for (int r = 0; r < R; r++)
			{
				scanf("%s", maze[l][r]);
				for (int c = 0; c < C; c++)
				{
					if (maze[l][r][c] == 'S'){
						bePt[0].l = l;
						bePt[0].r = r;
						bePt[0].c = c;
					} else if (maze[l][r][c] == 'E'){
						bePt[1].l = l;
						bePt[1].r = r;
						bePt[1].c = c;
					}
				}
			}
		}

		int ans = dfs();
		if (ans > 0){
			printf("Escaped in %d minute(s).\n", ans);
		} else
			cout << "Trapped!" << endl;
	}
	return 0;
}