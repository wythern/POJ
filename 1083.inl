#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentOperation{
public:
	SegmentOperation(int i, int j) : m_point(i)
									, m_value(j)
	{}

	bool operator < (const SegmentOperation& rhs) const {
		return (m_point != rhs.m_point) ? m_point < rhs.m_point : m_value > rhs.m_value;
	}

	int m_point;
	int m_value;
};

int main(int argc, char** argv){

	int n = 0;
	fscanf_s(stdin, "%d", &n);
	while (n--)
	{
		int l = 0;
		int s = 0;
		int t = 0;
		vector<SegmentOperation> segmentOp;
		fscanf(stdin, "%d", &l);
		while (l--)
		{
			fscanf(stdin, "%d %d", &s, &t);
			if (s >= t) swap(s, t);
			segmentOp.push_back(SegmentOperation((s + 1) & ~1, 1));
			segmentOp.push_back(SegmentOperation((t + 1) & ~1, -1));
		}

		sort(segmentOp.begin(), segmentOp.end());

		int maxConflict = 0;
		int conflict = 0;
		for (vector<SegmentOperation>::iterator it = segmentOp.begin(); it != segmentOp.end(); it++)
		{
			conflict += (*it).m_value;
			maxConflict = max(maxConflict, conflict);
		}

		cout << maxConflict * 10 << endl;
	}

	return 0;
}
