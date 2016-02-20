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
#include <cmath>
using namespace std;

bool isEncrypt(char* s, char* t){
	if (s[0] == '\0')
		return true;
	else if (t[0] == '\0')
		return false;

	if (s[0] == t[0]){
		return isEncrypt(s + 1, t + 1);
	} else{
		return isEncrypt(s, t + 1);
	}
}

int main(int argc, char** argv){
	char* s = new char[100001];
	char* t = new char[100001];

	while (scanf("%s %s", s, t) != EOF){
		if (s[0] == '\0')
			break;

		cout << (isEncrypt(s, t) ? "Yes" : "No") << endl;
	}

	delete[] s;
	delete[] t;

	return 0;
}