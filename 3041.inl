#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <cmath>
using namespace std;

struct Node
{
	vector<int> toNodes;
};

struct Edge
{
	int from;
	int to;
};

vector<Edge> findAugPath(vector<Edge>& edges, int k,
						 vector<Node>& fromNodes, vector<Node>& toNodes, 
						 vector<pair<int, int>>& fromMatched, vector<pair<int, int>>& toMatched,
						 vector<int>& fromVisited, vector<int>& toVisited){
	Node curr = fromNodes[k];
	vector<Edge> augPath;
	for (size_t i = 0; i < curr.toNodes.size(); i++)
	{
		if (toVisited[curr.toNodes[i]] == 1)
			continue;

		if (toMatched[curr.toNodes[i]].second == -1){
			Edge edge;
			edge.from = k;
			edge.to = curr.toNodes[i];
			toVisited[edge.to] = 1;
			augPath.push_back(edge);
			break;
		} else{
			Edge edge;
			edge.from = k;
			edge.to = curr.toNodes[i];
			toVisited[edge.to] = 1;
			augPath.push_back(edge);
			edge.from = curr.toNodes[i];
			edge.to = toMatched[curr.toNodes[i]].second;
			if (fromVisited[edge.to] == 1)
				continue;

			fromVisited[edge.to] = 1;
			augPath.push_back(edge);
			vector<Edge> augSubPath = findAugPath(edges, edge.to, fromNodes, toNodes, fromMatched, toMatched, fromVisited, toVisited);
			if (!augSubPath.empty()){
				augPath.insert(augPath.end(), augSubPath.begin(), augSubPath.end());
				break;
			}
			fromVisited[edge.to] = 0;
			augPath.clear();
		}
	}

	return augPath;
}

int hungarianBiPartite(vector<Edge>& edges, vector<Node>& fromNodes, vector<Node>& toNodes, int N){
	vector<pair<int, int>> fromMatched(N, pair<int, int>(-1, -1));
	vector<pair<int, int>> toMatched(N, pair<int, int>(-1, -1));

	for (size_t k = 0; k < fromNodes.size(); k++)
	{
		Node curr = fromNodes[k];
		if (fromMatched[k].second != -1)
			continue;

		vector<int> fromVisited(N, 0);
		vector<int> toVisited(N, 0);
		fromVisited[k] = 1;
		vector<Edge> augPath = findAugPath(edges, k, fromNodes, toNodes, fromMatched, toMatched, fromVisited, toVisited);
		fromVisited[k] = 0;
		for (size_t i = 0; i < augPath.size(); i++)
		{
			if ((i + 1) % 2){
				Edge edge = augPath[i];
				fromMatched[edge.from] = pair<int, int>(edge.from, edge.to);
				toMatched[edge.to] = pair<int, int>(edge.to, edge.from);
			}
		}
	}

	for (size_t k = 0; k < toNodes.size(); k++)
	{
		Node curr = toNodes[k];
		if (toMatched[k].second != -1)
			continue;

		vector<int> fromVisited(N, 0);
		vector<int> toVisited(N, 0);
		fromVisited[k] = 1;
		vector<Edge> augPath = findAugPath(edges, k, toNodes, fromNodes, toMatched, fromMatched, fromVisited, toVisited);
		fromVisited[k] = 0;
		for (size_t i = 0; i < augPath.size(); i++)
		{
			if ((i + 1) % 2){
				Edge edge = augPath[i];
				toMatched[edge.from] = pair<int, int>(edge.from, edge.to);
				fromMatched[edge.to] = pair<int, int>(edge.to, edge.from);
			}
		}
	}

	int maxMatch = 0;
	for (size_t i = 0; i < fromMatched.size(); i++)
	{
		if (fromMatched[i].second != -1){
			maxMatch++;
			toMatched[fromMatched[i].second].second = -1;
			fromMatched[i].second = -1;
		}
	}
	for (size_t i = 0; i < toMatched.size(); i++)
	{
		if (toMatched[i].second != -1){
			maxMatch++;
			fromMatched[fromMatched[i].second].second = -1;
			toMatched[i].second = -1;
		}
	}

	return maxMatch;
}

int main(int argc, char** argv){
	int N, K;
	scanf("%d %d", &N, &K);
	vector<Edge> edges;
	vector<Node> fromNodes(N, Node());
	vector<Node> toNodes(N, Node());
	while (K--)
	{
		Edge edge;
		scanf("%d %d", &edge.from, &edge.to);
		edge.from--;
		edge.to--;
		edges.push_back(edge);
		fromNodes[edge.from].toNodes.push_back(edge.to);
		toNodes[edge.to].toNodes.push_back(edge.from);
		swap(edge.from, edge.to);
		edges.push_back(edge);
	}

	cout << hungarianBiPartite(edges, fromNodes, toNodes, N) << endl;

	return 0;
}