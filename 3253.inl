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

int main(int argc, char** argv){
	int n;
	while (scanf("%d", &n) == 1)   {

		priority_queue<int, vector<int>, greater<int>> queue;
		int board = 0;
		while (n--)
		{
			int f;
			scanf("%d", &f);
			queue.push(f);
		}

		long long charge = 0;
		while (queue.size() > 1)
		{
			int a = queue.top();
			queue.pop();
			int b = queue.top();
			queue.pop();
			queue.push(a + b);
			charge += a + b;
		}

		cout << charge << endl;
	}
	return 0;
}

