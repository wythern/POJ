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

#define MAX_GENE_LEN 120
int n;
int genelen[2];
char geneCxt[2][MAX_GENE_LEN];

int geneTable[5][5] = {
	{ 5, -1, -2, -1, -3 },
	{ -1, 5, -3, -2, -4 },
	{ -2, -3, 5, -2, -2 },
	{ -1, -2, -2, 5, -1 },
	{ -3, -4, -2, -1, 0x70000000 },
};

int lookupTable(char gene1, char gene2){
	int row = 0;
	int col = 0;
	switch (gene1)
	{
	case 'A': row = 0; break;
	case 'C': row = 1; break;
	case 'G': row = 2; break;
	case 'T': row = 3; break;
	case '-': row = 4; break;
	default:
		break;
	}

	switch (gene2)
	{
	case 'A': col = 0; break;
	case 'C': col = 1; break;
	case 'G': col = 2; break;
	case 'T': col = 3; break;
	case '-': col = 4; break;
	default:
		break;
	}

	return geneTable[col][row];
}

int getMaxSimiliarity(){
	int dp[MAX_GENE_LEN][MAX_GENE_LEN];
	memset(dp, 0, sizeof(dp));

	for (size_t i = 0; i < 1; i++)
	{
		dp[i][0] = lookupTable(geneCxt[0][0], geneCxt[1][0]);
		for (size_t j = 1; j < genelen[1]; j++)
		{
			int s0 = dp[i][j - 1] + lookupTable(geneCxt[1][j], '-');
			int s1 = lookupTable(geneCxt[1][j], geneCxt[0][i]);
			for (size_t k = 0; k < j; k++)
			{
				s1 += lookupTable(geneCxt[1][k], '-');
			}
			dp[i][j] = std::max(s0, s1);
		}
	}

	for (size_t i = 1; i < genelen[0]; i++)
	{
		int s0 = dp[i - 1][0] + lookupTable(geneCxt[0][i], '-');
		int s1 = lookupTable(geneCxt[0][i], geneCxt[1][0]);
		for (size_t k = 0; k < i; k++)
		{
			s1 += lookupTable(geneCxt[0][k], '-');
		}
		dp[i][0] = std::max(s0, s1);
		for (size_t j = 1; j < genelen[1]; j++)
		{
			int s0 = dp[i - 1][j] + lookupTable(geneCxt[0][i], '-');
			int s2 = dp[i][j - 1] + lookupTable(geneCxt[1][j], '-');
			int s1 = dp[i - 1][j - 1] + lookupTable(geneCxt[1][j], geneCxt[0][i]);
			dp[i][j] = std::max(s0, std::max(s1, s2));
		}
	}

	return dp[genelen[0] - 1][genelen[1] - 1];
}

int main(){
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d %s", genelen, geneCxt[0]);
		scanf("%d %s", genelen + 1, geneCxt[1]);

		cout << getMaxSimiliarity() << endl;
	}
	return 0;
}