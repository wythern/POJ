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
char visited[41][41];
char maze[41][41];
int dist[41][41];

int LEFT_ROTATION_SEQUENCE[] = { 270, 0, 90, 180 };
int RIGHT_ROTATION_SEQUENCE[] = { 90, 0, 270, 180 };

pair<int, int> RotationClockwise(pair<int, int>& vec, int degree){
	switch (degree)
	{
	case 90:
		return pair<int, int>(vec.second, -vec.first);
	case 180:
		return pair<int, int>(-vec.first, -vec.second);
	case 270:
		return pair<int, int>(-vec.second, vec.first);
	default:
		break;
	}

	return vec;
}

int countLeftMoves(int w, int h, pair<int, int>& start){
	int step = 1;
	pair<int, int> currPos = start;
	pair<int, int> nextPos(0, 0);
	pair<int, int> faceDir(-1, 0);
	while (maze[currPos.first][currPos.second] != 'E')
	{
		for (size_t i = 0; i < 4; i++)
		{
			pair<int, int> posDiff = RotationClockwise(faceDir, LEFT_ROTATION_SEQUENCE[i]);
			if (currPos.first + posDiff.first >= 0 && currPos.first + posDiff.first < h && currPos.second + posDiff.second >= 0 && currPos.second + posDiff.second < w){
				if (maze[currPos.first + posDiff.first][currPos.second + posDiff.second] != '#'){
					nextPos.first = currPos.first + posDiff.first;
					nextPos.second = currPos.second + posDiff.second;
					faceDir = posDiff;
					break;
				}
			}
		}

		currPos = nextPos;
		++step;
	}

	return step;
}

int countRightMoves(int w, int h, pair<int, int>& start){
	int step = 1;
	pair<int, int> currPos = start;
	pair<int, int> nextPos(0, 0);
	pair<int, int> faceDir(-1, 0);
	while (maze[currPos.first][currPos.second] != 'E')
	{
		for (size_t i = 0; i < 4; i++)
		{
			pair<int, int> posDiff = RotationClockwise(faceDir, RIGHT_ROTATION_SEQUENCE[i]);
			if (currPos.first + posDiff.first >= 0 && currPos.first + posDiff.first < h && currPos.second + posDiff.second >= 0 && currPos.second + posDiff.second < w){
				if (maze[currPos.first + posDiff.first][currPos.second + posDiff.second] != '#'){
					nextPos.first = currPos.first + posDiff.first;
					nextPos.second = currPos.second + posDiff.second;
					faceDir = posDiff;
					break;
				}
			}
		}

		currPos = nextPos;
		++step;
	}

	return step;
}

int shortestPath(int w, int h, pair<int, int>& start){
	list<pair<int, int>> posStack;
	posStack.push_back(start);
	dist[start.first][start.second] = 1;

	while (!posStack.empty())
	{
		pair<int, int> pos = posStack.front();
		posStack.pop_front();
		visited[pos.first][pos.second] = 1;

		if (maze[pos.first][pos.second] == 'E')
			return dist[pos.first][pos.second];

		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (abs(i) + abs(j) == 1){
					if (pos.first + i >= 0 && pos.first + i < h && pos.second + j >= 0 && pos.second + j < w){
						if (visited[pos.first + i][pos.second + j] == 0 && maze[pos.first + i][pos.second + j] != '#'){
							dist[pos.first + i][pos.second + j] = dist[pos.first][pos.second] + 1;
							posStack.push_back(pair<int, int>(pos.first + i, pos.second + j));
						}
					}
				}
			}
		}
	}

	return -1;
}

pair<int, int> findEntry(int w, int h){
	for (size_t i = 0; i < w; i++)
	{
		if (maze[0][i] == 'S'){
			return pair<int, int>(0, i);
		}
		if (maze[h - 1][i] == 'S'){
			return pair<int, int>(h - 1, i);
		}
	}

	for (size_t i = 0; i < h; i++)
	{
		if (maze[i][0] == 'S'){
			return pair<int, int>(i, 0);
		}
		if (maze[i][w - 1] == 'S'){
			return pair<int, int>(i, w - 1);
		}
	}

	return pair<int, int>(-1, -1);
}

int main(int argc, char** argv){
	int n;
	scanf("%d", &n);
	while (n--)
	{
		int w, h;
		scanf("%d %d", &w, &h);
		for (size_t i = 0; i < h; i++)
		{
			scanf("%s", maze[i]);
		}

		pair<int, int> start = findEntry(w, h);
		int moveLeft = countLeftMoves(w, h, start);
		int moveRight = countRightMoves(w, h, start);
		memset(visited, 0, sizeof(visited));
		int moveFast = shortestPath(w, h, start);

		printf("%d %d %d\n", moveLeft, moveRight, moveFast);
	}
	return 0;
}