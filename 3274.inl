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

int calcMaxBlancedRange(vector<vector<int>>& sum){
	int maxRange = -1;
	for (int i = 0; i < sum.size(); i++)
	{
		for (int j = i + 1; j < sum.size(); j++)
		{
			vector<int> featureSum(sum[i].size(), 0);
			int featureCnt = 0;
			int k = 0;
			for (; k < sum[i].size(); k++)
			{
				featureSum[k] = sum[j][k] - sum[i][k];
				if (k != 0 && featureCnt != featureSum[k])
					break;
				featureCnt = featureSum[k];
			}

			if (k == sum[i].size())
				maxRange = std::max(maxRange, j - i);
		}
	}

	return maxRange;
}

int main(int argc, char** argv){
	int n, k;
	scanf("%d %d", &n, &k);
	vector<vector<int>> sum(n + 1, vector<int>(k, 0));
	vector<int> featureSum(k, 0);

	int pos = 1;
	while (n--)
	{
		int feature;
		scanf("%d", &feature);
		for (size_t i = 0; i < k; i++)
		{
			if (feature & (1 << i))
				featureSum[k - 1 - i] += 1;
		}

		sum[pos] = featureSum;
		++pos;
	}

	cout << calcMaxBlancedRange(sum) << endl;
	return 0;
}