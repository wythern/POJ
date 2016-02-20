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
#include <numeric>
#include <cmath>
using namespace std;

struct Point
{
	int x;
	int y;
};

int getDistance(Point& pt1, Point& pt2){
	return (pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y);
}

struct Triangle
{
	Triangle(Point& pt1, Point& pt2, Point& pt3){
		pt[0] = pt1;
		pt[1] = pt2;
		pt[2] = pt3;

		line[0] = getDistance(pt[0], pt[1]);
		line[1] = getDistance(pt[1], pt[2]);
		line[2] = getDistance(pt[2], pt[0]);
		std::sort(line, line + 3);
	}

	bool isIsoscelesRightTriangle(){
		return (line[0] == line[1]) && (line[0] + line[1] == line[2]);
	}

	int getArea(){
		return line[0] * line[1];
	}

	Point pt[3];
	int   line[3];
};

bool isSquare(vector<Point>& polygon){
	Triangle triangle1(polygon[0], polygon[1], polygon[2]);
	Triangle triangle2(polygon[1], polygon[2], polygon[3]);
	Triangle triangle3(polygon[2], polygon[3], polygon[0]);

	return triangle1.isIsoscelesRightTriangle() && triangle2.isIsoscelesRightTriangle() && triangle3.isIsoscelesRightTriangle()
		&& (triangle1.getArea() == triangle2.getArea()) && (triangle1.getArea() == triangle3.getArea());
}

void countSqareImpl(vector<Point>& pts, int index, vector<Point>& polygon, int& cnt){
	if (polygon.size() == 4){
		if (isSquare(polygon)){
			++cnt;
			for (size_t i = 0; i < polygon.size(); i++)
			{
				Point& pt = polygon[i];
				cout << "[" << pt.x << ", " << pt.y << "], ";
			}
			cout << endl;
		}
		return;
	}

	if (index == pts.size())
		return;

	countSqareImpl(pts, index + 1, polygon, cnt);

	polygon.push_back(pts[index]);
	countSqareImpl(pts, index + 1, polygon, cnt);
	polygon.pop_back();
}

int countSquare(vector<Point>& pts){
	int cnt = 0;
	vector<Point> polygon;
	countSqareImpl(pts, 0, polygon, cnt);
	return cnt;
}

int main(int argc, char** argv){
	while (true)
	{
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;

		vector<Point> pts;
		while (n--)
		{
			Point pt;
			scanf("%d %d", &pt.x, &pt.y);
			pts.push_back(pt);
		}

		cout << countSquare(pts) << endl;
	}

	return 0;
}