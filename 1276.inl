#include <stdio.h>
#include <string>
#include <cstring>
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

//int n[12];
//int D[12];
int N;
int cash;
int drawCash;
int w[12];

struct MoneyType
{
	int n;
	int D;

	bool operator < (const MoneyType& rhs) const{
		return D >= rhs.D;
	}
};

MoneyType m[12];

int calculateWithdrawalCash(int k, int withdrawal){
	if (withdrawal > cash)
		return -1;

	if (k >= N){
		drawCash = max(drawCash, withdrawal);
		if (drawCash == cash)
			return 0;
		return 1;
	}

	int cnt = 0;
	while (cnt <= m[k].n){
		w[k] += cnt;
		int ret = calculateWithdrawalCash(k + 1, withdrawal + m[k].D * cnt);
		w[k] -= cnt;
		++cnt;
		if (0 > ret){
			break;
		}
		if (0 == ret)
			return 0;
	}

	return 1;
}

int main(){
	while (scanf("%d", &cash) != EOF)
	{
		scanf("%d", &N);
		//memset(n, 0, sizeof(n));
		//memset(D, 0, sizeof(D));
		for (size_t i = 0; i < N; i++)
		{
			scanf("%d", &m[i].n);
			scanf("%d", &m[i].D);
		}

		std::sort(m, m + N);

		drawCash = 0;
		int withdrawal = 0;
		memset(w, 0, sizeof(w));
		calculateWithdrawalCash(0, withdrawal);
		cout << drawCash << endl;
	}
	return 0;
}