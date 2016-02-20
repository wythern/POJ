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

#define MAXRPT 26
int n;
vector<int> repeaters[MAXRPT];
int visited[MAXRPT];

int bfsColoring(int id){
	stack<int> idStack;
	idStack.push(id);
	visited[id] = 1;

	int channels = 1;
	while (!idStack.empty())
	{
		int curr = idStack.top();
		idStack.pop();

		for (size_t i = 0; i < repeaters[curr].size(); i++)
		{
			if (visited[repeaters[curr][i]] == 0){
				// new find node
				for (int color = 1; color < MAXRPT; color++)
				{
					if (color != visited[curr]){
						visited[repeaters[curr][i]] = color;
						channels = std::max(color, channels);
						break;
					}
				}
				idStack.push(repeaters[curr][i]);
			} else{
				if (visited[repeaters[curr][i]] == visited[curr]){
					// handle conflict;
					int colorMask = 0;
					for (size_t k = 0; k < repeaters[repeaters[curr][i]].size(); k++)
					{
						if (visited[repeaters[repeaters[curr][i]][k]] != 0)
							colorMask |= 1 << (visited[repeaters[repeaters[curr][i]][k]] - 1);
					}

					for (int k = 0; k < 32; k++)
					{
						if (!(colorMask & (1 << k))){
							visited[repeaters[curr][i]] = k + 1;
							channels = std::max(k + 1, channels);
							break;
						}
					}
				}
			}
		}
	}

	return channels;
}

int calculateChannels(){
	int channels = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (visited[i] == 0)
			channels = std::max(channels, bfsColoring(i));
	}

	return channels;
}

int main(){
	while (true)
	{
		scanf("%d", &n);
		if (n == 0)
			break;

		for (size_t i = 0; i < n; i++)
		{
			visited[i] = 0;
			repeaters[i].clear();
		}

		int t = n;
		while (t--)
		{
			char buf[32];
			scanf("%s", buf);

			int curId = buf[0] - 'A';
			for (size_t i = 2; i < strlen(buf); i++)
			{
				repeaters[curId].push_back(*(buf + i) - 'A');
			}
		}

		int ans = calculateChannels();
		if (ans == 1)
			printf("%d channel needed.\n", ans);
		else
			printf("%d channels needed.\n", ans);
	}
	return 0;
}