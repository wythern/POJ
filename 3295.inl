#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

// Build AST seems a wrong way!!!!
struct Node{
	Node(char t, char v) : type(t)
	, val(v)
	{}

	char type; // 0: operand, 1: operator, 2: value;
	union{
		char operand;
		char op;
		char val; // 0 or 1;
	};

	Node* pLeft;
	Node* pRight;
};

char nextToken(char* pBuf){
	static int pos = 0;
	if (pos < strlen(pBuf))
		return pBuf[pos++];
	
	return 0xFF;
}

bool isOperand(char ch){
	return ch >= 'p' && ch <= 't';
}

Node* buildAST(char* pBuf, int& pos){
	switch (pBuf[0])
	{
	case 'K':
		Node* pRoot = new Node(0, pBuf[pos]);
		++pos; // consume 1 char;
		if (isOperand(pBuf[pos]))
			pRoot->pLeft = new Node(1, pBuf[pos++]);
		else
			pRoot->pLeft = buildAST(pBuf, pos);

		if (isOperand(pBuf[pos]))
			pRoot->pRight = new Node(1, pBuf[pos++]);
		else
			pRoot->pRight = buildAST(pBuf, pos);
		break;
	case 'N':
		Node* pRoot = new Node(0, pBuf[pos]);
		if (isOperand(pBuf[pos]))
			pRoot->pRight = new Node(1, pBuf[pos++]);
		else
			pRoot->pRight = buildAST(pBuf, pos);
		break;
	default:
		break;
	}
}

bool traversalTestTree(Node* root){
	if (NULL == root)
		return true;

	switch (root->op)
	{
	case 'K':
		return traversalTestTree(root->pLeft) && traversalTestTree(root->pRight);
	default:
		break;
	}
}

bool verifyString(char* pBuf){
	Node* pRoot = buildAST(pBuf);
	return traversalTestTree(pRoot);
}


int main(int argc, char** argv){
	char buf[128];
	while (1)
	{
		scanf("%s", buf);
		if (buf[0] == '0')
			return 0;

		if (verifyString(buf))
			cout << "tautology" << endl;
		else
			cout << "not" << end;
	}

	return 0;
}