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
	for (size_t k = 0; k < 4; k++)
	{
		int bitPos = 15 - (k * 4 + j);
		SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	}

	for (size_t k = 0; k < 4; k++)
	{
		int bitPos = 15 - (i * 4 + k);
		SET_BIT_VAL(node, bitPos, (BIT_VAL(node, bitPos) ^ 0x1));
	}
	return node;
}

bool enumStepsImpl(short startPlace, int opLevel, vector<pair<int, int>>& steps){
	if (opLevel == 16){
		if (startPlace == (short)0xFFFF)
			return true;
		return false;
	}

	if (enumStepsImpl(startPlace, opLevel + 1, steps))
		return true;

	int i = opLevel / 4;
	int j = opLevel % 4;
	short newPlace = flipPos(startPlace, i, j);
	steps.push_back(pair<int, int>(i, j));
	if (enumStepsImpl(newPlace, opLevel + 1, steps))
		return true;

	steps.pop_back();

	return false;
}

vector<pair<int, int>> enumSteps(short startPlace){
	vector<pair<int, int>> steps;
	enumStepsImpl(startPlace, 0, steps);
	return steps;
}

vector<pair<int, int>> enumStepsBFS(short startPlace){
	vector<pair<int, int>> steps;
	stack<short> nodeStack;
	nodeStack.push(startPlace);

	set<short> nodeVisited;
	stack<short> nodeSubStack;
	while (!nodeStack.empty())
	{
		short node = nodeStack.top();
		nodeStack.pop();

		if (node == (short)0xFFFF){
			return steps;
		}

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				short newNode = flipPos(node, i, j);
				if (nodeVisited.insert(newNode).second)
					nodeSubStack.push(newNode);
			}
		}

		if (nodeStack.empty()){
			swap(nodeStack, nodeSubStack);
		}
	}
	
	return steps;
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
			if (buf[i] == '-')
				SET_BIT(line, 3 - i);
		}

		startPos |= ((line & 0x0F) << (n << 2));
	}
#endif
	vector<pair<int, int>> steps = enumSteps(startPos);
	cout << steps.size() << endl;
	for (size_t i = 0; i < steps.size(); i++)
	{
		cout << steps[i].first + 1 << " " << steps[i].second + 1 << endl;
	}
	return 0;
}
