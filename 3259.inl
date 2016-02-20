#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge{
	int inidx;
	int outIdx;
	int cost;
};

void DoRestTimeCost(Edge& edge, vector<int>& timecost){
	int u = edge.inidx;
	int v = edge.outIdx;
	int c = edge.cost;
	if (timecost[u] + c < timecost[v]){
		timecost[v] = timecost[u] + c;
	}
}

bool IsTimeTravellable(int N, vector<Edge>& edges){
	//for (size_t i = 0; i < N; i++)
	int i = 0;
	{
		bool bTravellable = false;
		vector<int> timeCost(N, INT_MAX);
		timeCost[i] = 0;
		for (size_t j = 0; j < N - 1; ++j){
			for (size_t k = 0; k < edges.size(); k++)
			{
				if (timeCost[edges[k].inidx] != INT_MAX){
					DoRestTimeCost(edges[k], timeCost);
				}
			}
		}

		for (size_t k = 0; k < edges.size(); k++)
		{
			int u = edges[k].inidx;
			int v = edges[k].outIdx;
			int c = edges[k].cost;
			if (timeCost[v] > timeCost[u] + c){
				bTravellable = true;
			}
		}

		if (!bTravellable)
			return false;
	}

	return true;;
}

int main(int argc, char** argv){
	int F;
	scanf("%d", &F);
	while (F--)
	{
		int N, M, W;
		scanf("%d %d %d", &N, &M, &W);

		vector<Edge> edges;
		for (size_t i = 0; i < M; i++)
		{
			Edge edge;
			scanf("%d %d %d", &edge.inidx, &edge.outIdx, &edge.cost);
			edge.inidx--;
			edge.outIdx--;
			
			Edge backEdge;
			backEdge.inidx = edge.outIdx;
			backEdge.outIdx = edge.inidx;
			backEdge.cost = edge.cost;
			edges.push_back(edge);
			edges.push_back(backEdge);
		}

		for (size_t i = 0; i < W; ++i){
			Edge edge;
			scanf("%d %d %d", &edge.inidx, &edge.outIdx, &edge.cost);
			edge.inidx--;
			edge.outIdx--;
			edge.cost = -edge.cost;
			edges.push_back(edge);
		}

		cout << (IsTimeTravellable(N, edges) ? "YES" : "NO") << endl;
	}

	return 0;
}
