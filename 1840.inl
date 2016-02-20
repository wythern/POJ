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
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <numeric>
#include <cmath>
using namespace std;

class Equation{
	// a1x13+ a2x23+ a3x33+ a4x43+ a5x53=0 
public:
	Equation(int a[], int N){
		static bool m_bPowInited = false;
		for (size_t i = 0; i < N; i++)
		{
			m_a.push_back(a[i]);
		}

		if (!m_bPowInited){
			for (int i = -50; i <= 50; i++)
			{
				m_pow3x[i + 50] = i*i*i;
			}
			m_bPowInited = true;
		}
	}

	bool verify(int x[], int N){
		return calc(x, N) == 0;
	}

	int calc(int x[], int N){
		int sum = 0;
		for (int i = 0; i < N; ++i){
			sum += m_a[i] * m_pow3x[x[i] + 50];
		}
		return sum;
	}

private:
	vector<int> m_a;
	static int m_pow3x[101];
};

int Equation::m_pow3x[101];

int main(int argc, char** argv){
	int a[5];
	while (scanf("%d %d %d %d %d", a, a + 1, a + 2, a + 3, a + 4) != EOF)
	{
		int x[5];
		Equation equationlhs(a, 3);
		Equation equationRhs(a + 3, 2);
		int cnt = 0;
		unordered_set<int> results;
		unordered_map<int, int> resultsInfo;
		for (int x1 = -50; x1 <= 50; x1++)
		{
			if (x1 == 0) continue;
			for (int x2 = -50; x2 <= 50; x2++)
			{
				if (x2 == 0) continue;
				for (int x3 = -50; x3 <= 50; x3++)
				{
					if (x3 == 0) continue;
					x[0] = x1;
					x[1] = x2;
					x[2] = x3;

					resultsInfo[equationlhs.calc(x, 3)]++;
				}
			}
		}

		for (int x4 = -50; x4 <= 50; x4++)
		{
			if (x4 == 0) continue;
			for (int x5 = -50; x5 <= 50; x5++)
			{
				if (x5 == 0) continue;
				x[0] = x4;
				x[1] = x5;
				unordered_map<int, int>::iterator it;
				if ((it = resultsInfo.find(-equationRhs.calc(x, 2))) != resultsInfo.end()){
					cnt += it->second;
				}
			}
		}

		cout << cnt << endl;
	}
	return 0;
}
