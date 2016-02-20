#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Exchange{
	int idxA;
	int idxB;
	float rAB;
	float cAB;
	float rBA;
	float cBA;
};

struct Link;

struct Node
{
	//vector<Link*> inLinks;
	vector<Link*> outLinks;

	int C;
	float V;
};

struct Edge
{
	int NodeIn;
	int NodeOut;

	float rInOut;
	float cInOut;
};

struct Link
{
	Node *from, *to;
	float rAB;
	float cAB;
};

vector<Node*> buildGraph(vector<Exchange>& exchangePlaces, int N){
	vector<Node*> vNodes;
	for (size_t i = 0; i < N; i++)
	{
		Node* pNode = new Node;
		pNode->C = i;
		vNodes.push_back(pNode);
	}

	for (size_t i = 0; i < exchangePlaces.size(); i++)
	{
		Link* pLink1 = new Link;
		pLink1->from = vNodes[exchangePlaces[i].idxA - 1];
		pLink1->to = vNodes[exchangePlaces[i].idxB - 1];
		pLink1->rAB = exchangePlaces[i].rAB;
		pLink1->cAB = exchangePlaces[i].cAB;
		vNodes[exchangePlaces[i].idxA - 1]->outLinks.push_back(pLink1);


		Link* pLink2 = new Link;
		pLink2->from = vNodes[exchangePlaces[i].idxB - 1];
		pLink2->to = vNodes[exchangePlaces[i].idxA - 1];
		pLink2->rAB = exchangePlaces[i].rBA;
		pLink2->cAB = exchangePlaces[i].cBA;
		vNodes[exchangePlaces[i].idxB - 1]->outLinks.push_back(pLink2);
	}

	return vNodes;
}

bool isProliftable(vector<Exchange>& exchangePlaces, int N, int S, float V){
	vector<Node*> vNode = buildGraph(exchangePlaces, N);

	// BFS;
	vNode[S - 1]->V = V;
	stack<Node*> stackNode;
	stackNode.push(vNode[S - 1]);
	map<Node*, float> concurrency;
	while (!stackNode.empty())
	{
		Node* pNode = stackNode.top();
		stackNode.pop();

		if (concurrency.find(pNode) != concurrency.end() && concurrency[pNode] >= pNode->V)
			continue;

		if (pNode->C == S - 1 && pNode->V > V)
			return true;

		concurrency[pNode] = pNode->V;

		for (size_t i = 0; i < pNode->outLinks.size(); i++)
		{
			Node* pNextNode = new Node;
			pNextNode = pNode->outLinks[i]->to;
			float cAB = pNode->outLinks[i]->cAB;
			float rAB = pNode->outLinks[i]->rAB;
			pNextNode->V = (pNode->V - cAB)*rAB;
			if (pNextNode->V > 0)
				stackNode.push(pNextNode);
		}
	}

	return false;
}

void doRestWeight(vector<Node>& vNode, Edge& edge){
	int u = edge.NodeIn;
	int v = edge.NodeOut;
	if (vNode[v].V < (vNode[u].V - edge.cInOut) * edge.rInOut)
		vNode[v].V = (vNode[u].V - edge.cInOut) * edge.rInOut;
}

bool positiveWeightLoop(vector<Node>& vNode, vector<Edge*>& vEdge, int S, float V){
	vNode[S - 1].V = V;
	for (size_t i = 0; i < vNode.size() - 1; i++)
	{
		for (size_t j = 0; j < vEdge.size(); j++)
		{
			if (vNode[vEdge[j]->NodeIn].V != 0){
				//float w = (vNode[vEdge[j]->NodeIn].V - vEdge[j]->cInOut) * vEdge[j]->rInOut;
				doRestWeight(vNode, *vEdge[j]);
			}
		}
	}

	for (size_t i = 0; i < vEdge.size(); i++)
	{
		float w = (vNode[vEdge[i]->NodeIn].V - vEdge[i]->cInOut) * vEdge[i]->rInOut;
		if (vNode[vEdge[i]->NodeOut].V < w){
			return true;
		}
	}

	return false;
}

#define USE_SCANF
int main(int argc, char** argv){
	int N = 3, M = 2, S = 1;
	float V = 20.0f;
#ifdef USE_SCANF
	scanf("%d %d %d %f", &N, &M, &S, &V);
#endif

	vector<Exchange> exchanges;
#ifndef USE_SCANF
	Exchange place1 = {1, 2, 1.0f, 1.0f, 1.0f, 0.0f};
	Exchange place2 = {2, 3, 1.1f, 1.0f, 1.1f, 1.0f};
	if (M >= 1) exchanges.push_back(place1);
	if (M >= 2) exchanges.push_back(place2);
#else
	while (M--){
		Exchange place;
		scanf("%d %d %f %f %f %f", &place.idxA, &place.idxB, &place.rAB, &place.cAB, &place.rBA, &place.cBA);
		exchanges.push_back(place);
	}
#endif
	vector<Node> vNode(N, Node());
	vector<Edge*> vEdge;

	for (size_t i = 0; i < N; i++)
	{
		vNode[i].C = i;
		vNode[i].V = 0;
	}
	
	for (size_t i = 0; i < exchanges.size(); i++)
	{
		Edge* pEdge = new Edge;
		pEdge->NodeIn = exchanges[i].idxA - 1; 
		pEdge->NodeOut = exchanges[i].idxB - 1;
		pEdge->cInOut = exchanges[i].cAB;
		pEdge->rInOut = exchanges[i].rAB;
		vEdge.push_back(pEdge);
	
		pEdge = new Edge;
		pEdge->NodeIn = exchanges[i].idxB - 1;
		pEdge->NodeOut = exchanges[i].idxA - 1;
		pEdge->cInOut = exchanges[i].cBA;
		pEdge->rInOut = exchanges[i].rBA;
		vEdge.push_back(pEdge);
	}

	//cout << (isProliftable(exchanges, N, S, V) ? "YES" : "NO") << endl; // Wrong implementation.
	cout << (positiveWeightLoop(vNode, vEdge, S, V) ? "YES" : "NO") << endl;
	return 0;
}