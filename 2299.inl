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
#include <cmath>
using namespace std;

vector<int> mergeArray(vector<int>& left, vector<int>& right, int& revCnt){
	vector<int> sorted(left.size() + right.size(), 0);
	int i = 0;
	int j = 0;
	int pos = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i] <= right[j]){
			sorted[pos++] = left[i];
			++i;
		} else{
			sorted[pos++] = right[j];
			++j;
			revCnt += left.size() - i;
		}
	}

	if (i == left.size()){
		sorted.insert(sorted.begin() + pos, right.begin() + j, right.end());
	} else if (j == right.size()){
		sorted.insert(sorted.begin() + pos, left.begin() + i, left.end());
	}

	return sorted;
}

void mergeSort(vector<int>& nums, int& revCnt){
	if (nums.size() <= 1){
		return;
	}

	int mid = nums.size() / 2;
	vector<int> leftHalf(nums.begin(), nums.begin() + mid);
	vector<int> rightHalf(nums.begin() + mid, nums.end());
	mergeSort(leftHalf, revCnt);
	mergeSort(rightHalf, revCnt);
	nums = mergeArray(leftHalf, rightHalf, revCnt);
}

int countReverseOrder(vector<int>& nums){
	int cnt = 0;
	mergeSort(nums, cnt);
	return cnt;
}

int test2299(int argc, char** argv){
	while (1){
		int n = 0;
		scanf("%d", &n);
		if (n == 0)
			break;

		vector<int> array(n, 0);
		int i = 0;
		while (n--)
		{
			int a;
			cin >> a;
			array[i++] = a;
		}
		
		cout << countReverseOrder(array) << endl;
	}

	return 0;
}


#include <cstdio>

#include <cstring>

#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 500010;

#define lowbit(i) ((i)&(-i))

struct pNode
{
	int v;
	int index;
	int r;
}node[maxn];

bool cmp1(pNode a, pNode b)
{
	return a.v<b.v;
}

bool cmp2(pNode a, pNode b)
{
	return a.index<b.index;
}

int tree[maxn];

void Update(int x, int c)
{
	for (int i = x; i<maxn; i += lowbit(i)) tree[i] += c;
}

int Getsum(int x)
{
	int sum = 0;
	for (int i = x; i >= 1; i -= lowbit(i)) sum += tree[i];
	return sum;
}

int main()
{
	int n;
	while (scanf("%d", &n), n)
	{
		memset(tree, 0, sizeof(tree));
		ll ans = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &node[i].v);
			node[i].index = i;
		}
		sort(node + 1, node + n + 1, cmp1);
		for (int i = 1; i <= n; i++) node[i].r = i;
		sort(node + 1, node + n + 1, cmp2);
		for (int i = 1; i <= n; i++)
		{
			Update(node[i].r, 1);
			ans += Getsum(n) - Getsum(node[i].r);
		}
		printf("%lld\n", ans);
	}
	return 0;
}