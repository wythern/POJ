#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int geoDistance(const pair<int, int>& p1, const pair<int, int>& p2){
	return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);
}

int calculateRadarNum(vector<pair<int, int>>& points, int d){
	int pos = 0;
	int distance = d*d;
	std::sort(points.begin(), points.end());
	vector<int> radarPos;
	while (pos < points.size())
	{		
		int nextPos = pos;
		while (nextPos < points.size() && geoDistance(pair<int, int>(points[nextPos].first, 0), points[pos]) <= distance)
		{
			nextPos++;
		}

		if (nextPos == pos)
			return -1;
		else
			radarPos.push_back(nextPos - 1);

		pos = nextPos - 1;
		while (nextPos < points.size() && geoDistance(pair<int, int>(points[pos].first, 0), points[nextPos]) <= distance)
		{
			nextPos++;
		}
		pos = nextPos;
	}

	return radarPos.empty() ? -1 : radarPos.size();
}

int main(int argc, char** argv){
	int caseNum = 1;
	while (1){
		int n = 0;
		int d = 0;
		scanf_s("%d %d", &n, &d);
		if (n == 0 && d == 0)
			break;

		vector<pair<int, int>> points;
		for (size_t i = 0; i < n; i++)
		{
			int x = 0;
			int y = 0;
			scanf_s("%d %d", &x, &y);
			points.push_back(pair<int, int>(x, y));
		}

		int numRadar = calculateRadarNum(points, d);
		printf("Case %d: %d\n", caseNum, numRadar);
		++caseNum;
		//scanf_s("");
	}
	return 0;
}
