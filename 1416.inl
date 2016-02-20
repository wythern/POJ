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

int tgt, num;
int dfs(int rem, int sum, int cutNum, stack<int>& cuts, int& status, int& ansSum, stack<int>& ansCuts){
	if (sum > tgt){
		return 0;
	}

	if ((rem + sum <= tgt && cutNum != 0) || (rem + sum <= tgt && cutNum == 0)){
		if (sum + rem > ansSum){
			ansSum = sum + rem;
			ansCuts = cuts;
			ansCuts.push(rem);
			status = 1;
		} else if (sum + rem == ansSum){
			status = 2;
		}
	}

	int cutDigit = 10;
	while (rem > 0 && cutDigit < rem)
	{
		int cutRem = rem % cutDigit;
		cuts.push(cutRem);
		dfs(rem/cutDigit, sum + cutRem, cutNum + 1, cuts, status, ansSum, ansCuts);
		cuts.pop();
		cutDigit *= 10;
	}

	return ansSum != 0;
}

int possibleCut(int& ansSum, stack<int>& cuts){
	stack<int> attemptCuts;
	int status;
	dfs(num, 0, 0, attemptCuts, status, ansSum, cuts);
	return status;
}

int main(){
	while (true)
	{
		scanf("%d %d", &tgt, &num);
		if (tgt == 0 || num == 0){
			break;
		}

		int ans = 0;
		stack<int> cuts;
		int ret = possibleCut(ans, cuts);
		if (ret == 1){
			cout << ans;
			while (!cuts.empty())
			{
				cout << " " << cuts.top();
				cuts.pop();
			}
			cout << endl;
		} else if (ret == 2)
			cout << "rejected" << endl;
		else
			cout << "error" << endl;
	}
	return 0;
}