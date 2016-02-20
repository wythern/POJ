#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

#define SET_BIT_VAL(a, k, val) (a = ((a & ~(1 << k)) | (val << k)))
#define SET_BIT(a, k) (a |= (1<<k))
#define CLR_BIT(a, k) (a &= (0<<k))
#define BIT_VAL(a, k) ((a >> k) & 0x1)

short flipPos(short node, int i, int j){
	int bitPos = 15 - (i * 4 + j);
	SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	if (i > 0){
		bitPos = 15 - ((i - 1) * 4 + j);
		SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	}
	if (j > 0){
		bitPos = 15 - (i * 4 + j - 1);
		SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	}
	if (j < 3){
		bitPos = 15 - (i * 4 + j + 1);
		SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	}
	if (i < 3){
		bitPos = 15 - ((i + 1) * 4 + j);
		SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	}
	return node;
}

int bfs(short startNode){
	stack<short> nodeStack;
	set<short> visitedNode;

	stack<short> nodeStackSubLv;
	nodeStack.push(startNode);
	int lvCnt = 0;
	while (!nodeStack.empty())
	{
		short node = nodeStack.top();
		nodeStack.pop();

		if (node == (short)0 || node == (short)0xFFFF)
			return lvCnt;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++){
				short newNode = flipPos(node, i, j);
				if (visitedNode.insert(newNode).second)
					nodeStackSubLv.push(newNode);
			}
		}

		if (nodeStack.empty()){
			swap(nodeStack, nodeStackSubLv);
			lvCnt++;
		}
	}

	return -1;
}

int main(int argc, char** argv){
	int n = 4;
	short startPos = 0x0;
#if 1
	while (n--) {
		char buf[256];
		fscanf(stdin, "%s", buf);
		//fscanf(stdin, "%s", buf);
		//scanf_s("%s\n", &buf);

		char line = 0;
		for (size_t i = 0; i < 4; i++)
		{
			if (buf[i] == 'b')
				SET_BIT(line, 3 - i);
		}

		startPos |= ((line & 0x0F) << (n << 2));
	}
#endif
	int step = bfs(startPos);
	if (step == -1)
		cout << "Impossible" << endl;
	else
		cout << step << endl;
	return 0;
}
