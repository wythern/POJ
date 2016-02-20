#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

struct Edge{
	int formThing;
	int toThing;
	int money;
	int thing;
	int valid;
};

struct Thing{
	int id;
	int lv;
	int valid;
	int sibling;
	int childOne;
	vector<Edge> edges;
};

class FuncComp{
public:
	const bool operator () (pair<int, int>& lhs, pair<int, int>& rhs){
		return lhs.first < rhs.first;
	}
};

//Try dijkstra, not done!
int lowestCost_Dijkstra(vector<Edge>& edges, vector<Thing>& things){
	//set<pair<int, int>> Q;
	//priority_queue<int> Q;
	vector<pair<int, int>> Q;
	Q.push_back(pair<int, int>(0, 0));
	int N = things.size();
	vector<int> d(N, INT_MAX);

	int cost = 0;
	while (!Q.empty())
	{
		int thing = Q.front().second;
		int cost = Q.front().first;
		Q.erase(Q.begin());
		if (thing == 1)
			return cost;

		for (size_t i = 0; i < things[thing].edges.size(); i++)
		{
			int u = thing;
			int v = things[thing].edges[i].toThing;
			int w = things[thing].edges[i].money;

			if (d[v] > d[u] + w){
				d[v] = d[u] + w;
				vector<pair<int, int>>::iterator it = Q.begin();
				for (; it != Q.end(); it++)
				{
					if (it->second == v && it->first > d[v]){
						it->first = d[v];
						break;
					}
				}
				if (it == Q.end())
					Q.push_back(pair<int, int>(d[v], v));

				std::sort(Q.begin(), Q.end(), FuncComp());
			}
		}
	}

	return -1;
}
//Bellman-ford
int lowestCost(vector<Edge>& edges, vector<Thing>& things){
	int N = things.size();
	vector<int> d(N, INT_MAX);

	d[0] = 0;
	for (size_t i = 0; i < N - 1; i++)
	{
		for (size_t j = 0; j < edges.size(); j++)
		{
			if (edges[j].valid){
				int u = edges[j].formThing;
				int v = edges[j].toThing;
				int w = edges[j].money;
				if (d[u] != INT_MAX && d[v] > d[u] + w)
					d[v] = d[u] + w;
			}
		}
	}

	return d[1];
}

int main(int arvc, char** argv){

	int M, N;
	scanf("%d %d", &M, &N);

	vector<Thing> things;
	Thing thing;
	thing.id = 0;
	thing.lv = -1;
	thing.valid = 1;
	thing.childOne = -1;
	thing.sibling = -1;
	things.push_back(thing);

	vector<Edge> edges;
	int n = 1;
	while (n <= N){
		int P, L, X;
		scanf("%d %d %d", &P, &L, &X);
		Thing thing;
		thing.id = n;
		thing.lv = L;
		thing.valid = 1;
		thing.sibling = -1;
		thing.childOne = -1;
		things.push_back(thing);
		Edge edge;
		edge.formThing = 0;
		edge.toThing = n;
		edge.money = P;
		edge.valid = 1;
		edge.thing = 0;
		edges.push_back(edge);
		while (X--)
		{
			int thing, money;
			scanf("%d %d", &thing, &money);
			Edge edge;
			edge.formThing = thing;
			edge.toThing = n;
			edge.money = money;
			edge.thing = thing;
			edge.valid = 1;
			edges.push_back(edge);
		}
		++n;
	}

	for (size_t i = 0; i < edges.size(); i++)
	{
		int kid = things[edges[i].formThing].childOne;
		if (kid == -1)
			things[edges[i].formThing].childOne = edges[i].toThing;
		else{
			while (things[kid].sibling != -1){
				kid = things[kid].sibling;
			}
			things[kid].sibling = edges[i].toThing;
		}
		things[edges[i].formThing].edges.push_back(edges[i]);
	}

	// remove unqualified edges then calc lowest cost.
	int cost = INT_MAX;
	for (size_t i = 0; i <= M; i++)
	{
		for (size_t j = 0; j < edges.size(); j++)
		{
			int minL = things[1].lv - i;
			int maxL = things[1].lv + M - i;
			
			if (things[edges[j].formThing].id != 0 && (things[edges[j].formThing].lv < minL || things[edges[j].formThing].lv > maxL)){
				edges[j].valid = 0;
				things[edges[j].formThing].valid = 0;
			}

			if (things[edges[j].formThing].id != 0 && (things[edges[j].toThing].lv < minL || things[edges[j].toThing].lv > maxL)){
				edges[j].valid = 0;
				things[edges[j].toThing].valid = 0;
			}
		}

		cost = min(cost, lowestCost_Dijkstra(edges, things));

		for (size_t j = 0; j < edges.size(); j++)
		{
			edges[j].valid = 1;
			things[edges[j].toThing].valid = 1;
			things[edges[j].formThing].valid = 1;
		}
	}

	cout << cost << endl;

	return 0;
}