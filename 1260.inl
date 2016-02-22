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

int c;
int a[110];
int p[110];
int dp[110];

int calcSum(int s, int e, int* coef){
	int sum = 0;
	for (size_t i = s; i < e; i++)
	{
		if (coef[i] == 0)
			continue;
		sum += (coef[i] + 10) * p[i];
	}
	return sum;
}

int calculateLeastCostEx(int s, int e){
	int coef[110];
	int coefbak[110];
	for (int i = s; i < e; i++)
	{
		coef[i] = a[i];
	}
	memcpy(coefbak, coef, sizeof(coef));
	int cost = calcSum(s, e, coef);

	for (size_t k = 1; k < e - s; k++)
	{
		for (size_t i = s + k; i < e; i++)
		{
			int aa = 0;
			for (int j = i - k; j < i; j++)
			{
				aa += coef[j];
				coef[j] = 0;
			}

			coef[i] += aa;
			cost = std::min(cost, calcSum(s, e, coef));

			for (int j = i - k; j <= i; j++)
			{
				coef[j] = a[j];
			}
		}
	}

	return cost;
}

int calculateLeastCost(){
	dp[0] = (a[0] + 10)*p[0];
	for (int i = 1; i < c; i++)
	{
		int s = calculateLeastCostEx(0, i + 1);
		for (int j = 0; j < i; j++)
		{
			s = std::min(s, dp[j] + calculateLeastCostEx(j + 1, i + 1));
		}
		dp[i] = s;
	}

	return dp[c - 1];
}

int main(){
	int N;
	scanf("%d", &N);
	while (N--)
	{
		scanf("%d", &c);
		for (int i = 0; i < c; i++)
		{
			scanf("%d %d", a + i, p + i);
		}

		cout << calculateLeastCost() << endl;
	}

	return 0;
}