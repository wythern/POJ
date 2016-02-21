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
float h[1024];
int dpF[1024];
int dpB[1024];


int getLCS(){
	for (int i = 0; i < n; i++)
	{
		dpF[i] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		int j = 0;
		while (j < i)
		{
			if (h[j] < h[i])
				dpF[i] = std::max(dpF[j] + 1, dpF[i]);
			++j;
		}
	}

	for (int i = 0; i < n; i++)
	{
		dpB[i] = 1;
	}
	dpB[n - 1] = 1;
	for (int i = n - 2; i >= 0; i--)
	{
		int j = n - 1;
		while (j > i)
		{
			if (h[j] < h[i])
				dpB[i] = std::max(dpB[j] + 1, dpB[i]);
			--j;
		}
	}

	int lcs = 0;
	for (size_t i = 0; i < n; i++)
	{
		lcs = std::max(lcs, dpF[i] + dpB[i] - 1);
		for (size_t j = i + 1; j < n; j++)
		{
			if (fabs(h[i] - h[j]) < 0.00001){
				lcs = std::max(lcs, dpF[i] + dpB[j]);
			}
		}
	}
	return lcs;
}

int main(){
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%f", h + i);
		}


		cout << n - getLCS() << endl;
	}
	return 0;
}