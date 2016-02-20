#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#define BUF_LEN 1000000
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

int main(int argc, char** argv){
	int n = 0;
	vector<int> setPrimes(primeNumbers(BUF_LEN));

	while (1)
	{
		int evenNum = 0;
		fscanf(stdin, "%d", &evenNum);
		if (evenNum < 6)
			break;

		bool bFound = false;
		for (vector<int>::iterator it = setPrimes.begin(); it != setPrimes.end(); it++)
		{
			if (find(setPrimes.begin(), setPrimes.end(), evenNum - *it) != setPrimes.end()){
				bFound = true;
				printf("%d = %d + %d\n", evenNum, *it, evenNum - *it);
				break;
			}
		}

		if (!bFound)
			cout << "Goldbach's conjecture is wrong." << endl;

	}

	return 0;
}