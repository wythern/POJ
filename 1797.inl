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

#define MAXNUM 1024

int visited[MAXNUM];
int N;

struct Edge
{
	int from;
	int to;
	int cost;
};

struct Crossing
{
	int id;
	vector<int> edges;
};

int n, m;
vector<Crossing> graph;
vector<Edge> edges;
int dist[MAXNUM];

int findNearest(){
	int id = -1;
	int nearest = -1;
	for (size_t i = 0; i < n; i++)
	{
		if (dist[i] > nearest && visited[i] == 0){
			nearest = dist[i];
			id = i;
		}
	}
	return id;
}

int bfs(){
	dist[0] = 0;
	int nextId;
	while ((nextId = findNearest()) != -1)
	{
		if (nextId == n - 1)
			return dist[nextId];
		visited[nextId] = 1;

		Crossing pt = graph[nextId];
		for (size_t i = 0; i < pt.edges.size(); i++)
		{
			if (visited[edges[pt.edges[i]].to] == 0){
				int maxWeight = (edges[pt.edges[i]].from == 0) ? edges[pt.edges[i]].cost : std::min(dist[edges[pt.edges[i]].from], edges[pt.edges[i]].cost);
				dist[edges[pt.edges[i]].to] = std::max(dist[edges[pt.edges[i]].to], maxWeight);
			}
		}
	}

	return -1;
}

int main(){
	int caseNum = 1;
	scanf("%d", &N);
	while (N--)
	{
		scanf("%d %d", &n, &m);

		int c1, c2, c3;
		memset(visited, 0, sizeof(visited));
		memset(dist, 0xFF, sizeof(dist));
		edges.clear();
		graph = vector<Crossing>(n, Crossing());
		for (size_t i = 0; i < m; i++)
		{
			scanf("%d %d %d", &c1, &c2, &c3);
			Edge edge;
			edge.from = c1 - 1;
			edge.to = c2 - 1;
			edge.cost = c3;
			edges.push_back(edge);
			graph[edge.from].edges.push_back(edges.size() - 1);
			edge.from = c2 - 1;
			edge.to = c1 - 1;
			edge.cost = c3;
			edges.push_back(edge);
			graph[edge.from].edges.push_back(edges.size() - 1);
		}

		printf("Scenario #%d:\n", caseNum++);
		cout << bfs() << endl << endl;
	}

	return 0;
}