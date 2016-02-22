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
#include <queue>
#include <numeric>
#include <functional>
#include <cmath>
using namespace std;

int n;
int h[360][360];
int dpF[360][360];

int getMaxValueImpl(int l, int k){
	if (k < 0)
		return -1;
	if (k > l)
		return -1;

	if (l == 0 && k == 0)
		return h[0][0];

	if (dpF[l][k] != -1)
		return dpF[l][k];

	int dpV = h[l][k] + std::max(getMaxValueImpl(l - 1, k), getMaxValueImpl(l - 1, k - 1));

	dpF[l][k] = dpV;
	return dpV;
}

int getMaxValue(){
	int maxV = 0;
	for (size_t i = 0; i < n; i++)
	{
		maxV = std::max(maxV, getMaxValueImpl(n - 1, i));
	}
	return maxV;
}

int main(){
	while (scanf("%d", &n) != EOF)
	{
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j <= i; j++)
			{
				scanf("%d", &h[i][j]);
			}
		}

		memset(dpF, 0xFF, sizeof(dpF));
		cout << getMaxValue() << endl;
	}
	return 0;
}

