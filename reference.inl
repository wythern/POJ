#include <stdio.h>  
#include <string.h>  

int target, num;
char str[8];
bool rejected, error;
int ans[8], alen, bns[8], blen, asum, bsum;

void dfs(int x, int xlen)
{
	if (x == 0){
		blen = xlen;
		if (asum < bsum && bsum <= target){
			asum = bsum;
			alen = blen;
			rejected = false; /// û����ͬ��  
			error = false; /// �������µĽ�  
			for (int i = 0; i <= alen; i++)
				ans[i] = bns[i];
		} else if (asum == bsum && bsum <= target)
			rejected = true; /// ����ͬ�Ĵ�  
		return;
	}

	if (x + bsum < asum) /// �򵥵��Ż�  
		return;

	for (int dec = 10; dec <= x * 10; dec *= 10){ /// ���x*10����Ҫ��  
		bsum += x % dec;
		bns[xlen] = x % dec;
		dfs(x / dec, xlen + 1);
		bsum -= x % dec;
	}
	return;
}

int main()
{
	while (2 == scanf("%d %d", &target, &num) && target && num){
		rejected = false; /// ��ͬ���Ĵ�  
		error = true; /// û��һ����  

		bsum = 0;
		asum = 0;
		dfs(num, 0);

		if (rejected && !error){
			printf("rejected\n");
		} else if (error){
			printf("error\n");
		} else {
			printf("%d", asum);
			for (int i = alen - 1; i >= 0; i--)
				printf(" %d", ans[i]);
			printf("\n");
		}
	}
	return 0;
}