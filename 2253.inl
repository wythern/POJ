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


struct Point{
	int x;
	int y;
};

struct Edge{
	Point ptFrom;
	Point ptTo;
};

int findNearestPt(vector<Point>& points, vector<float>& dist, vector<int>& visited){
	int idx = -1;
	float minDist = 100000.0f;
	for (size_t i = 0; i < points.size(); i++)
	{
		if (dist[i] != -1.0f && visited[i] == 0){
			if (dist[i] < minDist){
				minDist = dist[i];
				idx = i;
			}
		}
	}
	return idx;
}

float dijkstra(vector<Point>& points){
	vector<float> dist(points.size(), -1.0f);
	vector<int> visited(points.size(), 0);

	dist[0] = 0.0f;
	while (1){
		int ptIdx = findNearestPt(points, dist, visited);
		if (ptIdx == -1 || ptIdx == 1){
			return dist[1];
		}
		visited[ptIdx] = 1;

		for (size_t i = 0; i < points.size(); i++)
		{
			if (visited[i] == 0){
				if (dist[i] == -1.0f ||
					dist[i] > std::max(dist[ptIdx],
					(float)sqrt((float)(points[ptIdx].x - points[i].x)* (points[ptIdx].x - points[i].x) +
					(points[ptIdx].y - points[i].y) * (points[ptIdx].y - points[i].y))))
					dist[i] = std::max(dist[ptIdx],
					(float)sqrt((float)(points[ptIdx].x - points[i].x)* (points[ptIdx].x - points[i].x) +
					(points[ptIdx].y - points[i].y) * (points[ptIdx].y - points[i].y)));
			}
		}
	}

	return -1.0f;
}

int main(int argc, int argv){
	int K = 0;
	int N = 0;
	
	while (1){
		scanf("%d", &N);
		if (!N)
			break;

		vector<Point> points;
		while (N--)
		{
			Point pt;
			scanf("%d %d", &pt.x, &pt.y);
			points.push_back(pt);
		}

		cout << "Scenario #" << ++K << endl;
		//cout << "Frog Distance =" << dijkstra(points) << endl;
		printf("Frog Distance = %.3f\n", dijkstra(points));
		cout << endl;

		scanf("\n");
	}

	cout << endl;
	return 0;
}