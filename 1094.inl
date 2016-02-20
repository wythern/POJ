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

struct Node{
	Node(){
		inDegree = 0;
	}
	char id;
	//set<int> parent;
	int inDegree;
	vector<int> child;
};

struct Edge
{
	int in;
	int out;
};

int toposort(int n, vector<Edge>& edges, vector<int>& sortedNodes){
	stack<int> nodeStack;
	vector<int> visited(n, 0);
	int ret = 0;

	vector<Node> nodes(n, Node());
	for (size_t i = 0; i < edges.size(); i++)
	{
		Edge edge = edges[i];
		nodes[edge.in].id = edge.in + 'A';
		nodes[edge.out].id = edge.out + 'A';
		//nodes[edge.out].parent.insert(edge.in);
		nodes[edge.in].child.push_back(edge.out);
		nodes[edge.out].inDegree++;

		if (edge.in == edge.out){
			ret = 1;
			break;
		}
	}

	while (ret == 0 && sortedNodes.size() != nodes.size())
	{
		vector<int> candidates;
		for (size_t i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].inDegree == 0)
				candidates.push_back(i);
		}

		if (candidates.size() == 0){
			ret = 1;
			break;
		}else if (candidates.size() > 1){
			ret = 2;
			break;
		}

		sortedNodes.push_back(candidates[0]);
		//visited[candidates[0]] = 1;
		nodes[candidates[0]].inDegree = -1;
		vector<int>::iterator it = nodes[candidates[0]].child.begin();
		for (; it != nodes[candidates[0]].child.end(); it++)
		{
			nodes[*it].inDegree--;
		}
	}

	return ret;
}

int main(int argc, char** argv){
	while (1)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;

		vector<Edge> edges;
		vector<Node> nodes(n, Node());
		int err = -1;
		int cnt = 0;
		int minRelation = 0;
		vector<int> sortedArray;
		while (m--)
		{
			char buf[16];
			char X, Y;
			scanf("%s", buf);
			X = buf[0];
			Y = buf[2];
			Edge edge;
			edge.in = X - 'A';
			edge.out = Y - 'A';
			edges.push_back(edge);

			if (err == 0 || err == 1)
				continue;

			++cnt;
			sortedArray.clear();
			err = toposort(n, edges, sortedArray);

			if (err == 0){
				//Sorted sequence determined after xxx relations: yyy...y. 
				string sortStr;
				for (size_t i = 0; i < sortedArray.size(); i++)
				{
					sortStr += char(sortedArray[i] + 'A');
				}
				printf("Sorted sequence determined after %d relations: %s.\n", cnt, sortStr.c_str());
			} else if (err == 1){
				//Inconsistency found after xxx relations.
				printf("Inconsistency found after %d relations.\n", cnt);
			}
		}

		// Sorted sequence cannot be determined. 
		if (err == 2)
			printf("Sorted sequence cannot be determined.\n");
	}
	return 0;
}