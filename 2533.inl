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
int h[1024];
int dpF[1024];

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

	return *std::max_element(dpF, dpF + n);
}


int main(){
	while (scanf("%d", &n) != EOF)
	{
		for (size_t i = 0; i < n; i++)
		{
			scanf("%d", h + i);
		}

		cout << getLCS() << endl;
	}
	return 0;
}
