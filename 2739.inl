#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define BUF_LEN 10000

vector<int> primeNumbers(int n){
	char nums[BUF_LEN];
	vector<int> vPrimes;
	memset(nums, 0, BUF_LEN);
	for (size_t i = 2; i <= n; i++)
	{
		if (nums[i] == 0){
			vPrimes.push_back(i);
			for (size_t j = 1; i * j < BUF_LEN; j++)
			{
				nums[i*j] = 1;
			}
		}
	}

	return vPrimes;
}

void consecutivePrimeSum(int n, vector<int>& vPrimes, int pos, vector<int>& subPrimes, vector<vector<int>>& vSubPrimes){
	if (n < 0 || pos >= vPrimes.size())
		return;

	if (n == 0){
		if (!subPrimes.empty())
			vSubPrimes.push_back(subPrimes);
		return;
	}

	subPrimes.push_back(vPrimes[pos]);
	consecutivePrimeSum(n - vPrimes[pos], vPrimes, pos + 1, subPrimes, vSubPrimes);
	subPrimes.pop_back();
}

int main(int argc, char** argv){
	int n = 0;
	vector<int> vPrimes = primeNumbers(10000);
	do{
		fscanf_s(stdin, "%d", &n);
		if (n == 0)
			break;
		vector<int> subPrimes;
		vector<vector<int>> vSubPrimes;

		for (size_t i = 0; i < vPrimes.size(); i++)
		{
			consecutivePrimeSum(n, vPrimes, i, subPrimes, vSubPrimes);
		}
		cout << vSubPrimes.size() << endl;
	} while (n > 0);
	return 0;
}