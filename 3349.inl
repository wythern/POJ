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
#include <numeric>
#include <cmath>
using namespace std;

class SnowFlake{
public:
	SnowFlake(int arms[6]){
		memcpy(m_arms, arms, 6 * sizeof(int));
		m_hash = std::accumulate(m_arms, m_arms + 6, 0);
	}

	int getHashValue(){
		return m_hash;
	}

	bool operator < (const SnowFlake& rhs) const{
		for (size_t i = 0; i < 6; i++)
		{
			if (m_arms[i] == rhs.m_arms[i])
				continue;
			return m_arms[i] < rhs.m_arms[i];
		}

		return false;
	}

	bool operator == (const SnowFlake& rhs) const{
		//clock-wise
		for (int start = 0; start < 6; start++)
		{
			int i = start;
			for (; i - start < 6; i++)
			{
				if (m_arms[i - start] != rhs.m_arms[i % 6]){
					break;
				}
			}

			if (i - start == 6)
				return true;
		}

		//clock-wise
		for (int start = 0; start < 6; start++)
		{
			int i = 0;
			for (; i < 6; i++)
			{
				if (m_arms[i] != rhs.m_arms[(start - i + 6) % 6]){
					break;
				}
			}

			if (i == 6)
				return true;
		}

		return false;
	}

private:
	int m_arms[6];
	unsigned int m_hash;
};

class HashSnowFlakes{
public:
	HashSnowFlakes(){
		m_prime = 104659;
		m_table.resize(m_prime);
	}

	bool insert(SnowFlake& flake){
		vector<SnowFlake>& flakes = m_table[flake.getHashValue() % m_prime];
		if (flakes.empty()){
			flakes.push_back(flake);
			return true;
		} else{
			for (int i = 0; i < flakes.size(); i++)
			{
				if (flake == flakes[i])
					return false;
			}

			flakes.push_back(flake);
			return true;
		}
	}

private:
	int m_prime;
	vector<vector<SnowFlake>> m_table;
};

int main(int argc, char** argv){
	vector<int> milks;
	int n;
	scanf("%d", &n);
	//set<SnowFlake> flakes;
	map<int, set<int>> armToFlake[6];
	int flakeId = 0;
	bool bPrint = false;
	HashSnowFlakes flakes;
	while (n--){
		int arm[6];
		for (int i = 0; i < 6; ++i){
			scanf("%d", &arm[i]);
		}
		if (bPrint)
			continue;

		SnowFlake flake(arm);
		if (!flakes.insert(flake)){
			bPrint = true;
			cout << "Twin snowflakes found." << endl;
		}
	}

	if (!bPrint)
		cout << "No two snowflakes are alike." << endl;
	return 0;
}