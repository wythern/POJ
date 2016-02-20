#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
using namespace std;

struct Edge
{
	int len;
	int from;
	int to;

	bool operator < (const Edge& rhs) const{
		return len < rhs.len;
	}
};

class JointSet{
public:
	JointSet(int N){
		Links.resize(N);
		for (size_t i = 0; i < N; i++)
		{
			Links[i] = i;
		}
	}

	int Find(int id){
		while (id != Links[id])
		{
			id = Links[id];
		}
		return id;
	}

	void Union(int id1, int id2){
		while (Links[id2] != id1)
		{
			int id = Links[id2];
			Links[id2] = id1;
			id2 = Links[id];
		}
	}

private:
	vector<int> Links;
};

int main(int argc, char** argv){
	int T = 0;
	scanf("%d", &T);
	while (T--)
	{
		int k;
		scanf("%d", &k);
		vector<vector<int>> distMatrix;
		int N = k;
		while (k--){
			vector<int> dist;
			for (size_t i = 0; i < N; i++)
			{
				int d;
				scanf("%d", &d);
				dist.push_back(d);
			}
			//scanf("\n");
			distMatrix.push_back(dist);
		}

		vector<Edge> sortedDist;
		for (size_t i = 0; i < distMatrix.size(); i++)
		{
			for (size_t j = i + 1; j < distMatrix[i].size(); j++)
			{
				Edge edge;
				edge.from = i;
				edge.to = j;
				edge.len = distMatrix[i][j];
				sortedDist.push_back(edge);
			}
		}

		vector<int> visited(distMatrix.size(), -1);
		sort(sortedDist.begin(), sortedDist.end());
		int E = distMatrix.size() - 1;

#if 1
		// you can not insure the minimun sum here!!! actually it can, but need approve.
		// your problem is you can not prove its connectness, using joint set instead!!!
		JointSet jset(distMatrix.size());
		for (size_t i = 0; i < sortedDist.size(); i++)
		{
			Edge edge = sortedDist[i];
			
			if (jset.Find(edge.from) != jset.Find(edge.to)){
				jset.Union(edge.from, edge.to);
				--E;
				if (!E)
					cout << edge.len << endl;

			}
		}
#endif


	}
	return 0;
}