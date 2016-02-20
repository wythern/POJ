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

int Carray[20];
int Garray[20];

int calculateSum(int C, int Carray[], int ci, int cig, int G, int Garray[], int gc, int sum, int target){
	if (ci == C && gc == G && sum == target)
		return 1;
	if (ci >= C || gc > G)
		return 0;

	int cnt = 0;
	cnt += calculateSum(C, Carray, ci + 1, 0, G, Garray, gc, sum, target);

	int num = 0;
	for (int gii = 0; gii < G; gii++)
	{
		if (Garray[gii] < cig)
			continue;

		int t = Garray[gii];
		Garray[gii] = -1;
		cnt += calculateSum(C, Carray, ci, t, G, Garray, gc + 1, sum + t * Carray[ci], target);
		Garray[gii] = t;
	}

	return cnt;
}

int main(){
	int C, G;
	while (scanf("%d %d", &C, &G) != EOF)
	{
		for (int i = 0; i < C; i++)
		{
			scanf("%d", &Carray[i]);
		}
		for (int i = 0; i < G; i++)
		{
			scanf("%d", &Garray[i]);
		}

		cout << calculateSum(C, Carray, 0, 0, G, Garray, 0, 0, 0) << endl;
	}
	return 0;
}