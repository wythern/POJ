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


struct Stick{
	string end[2];
	int visited[2];
};

struct Node
{
	int color;
	vector<int> links;
};

class Trie{
public:
	Trie(){
		m_children = vector<Trie*>(26, NULL);
	}

	~Trie(){
#if 0
		for (size_t i = 0; i < m_children.size(); i++)
		{
			if (m_children[i] != NULL)
				delete m_children[i];
		}
		m_children.clear();
#endif
	}

	int Insert(const string& str){
		Trie* pNode = this;
		bool bInsert = false;
		for (size_t i = 0; i < str.size(); i++)
		{
			vector<Trie*>& children = pNode->m_children;
			if (children[str[i] - 'a'] == NULL){
				bInsert = true;
				children[str[i] - 'a'] = new Trie();
			}
			pNode = children[str[i] - 'a'];
		}
		if (bInsert || !pNode->m_complete)
			pNode->m_idx = m_sStrIdx++;
		
		pNode->m_complete = true;
		return pNode->m_idx;
	}

	int getStringCount(){
		return m_sStrIdx;
	}

private:
	static int m_sStrIdx;
	vector<Trie*> m_children;
	bool m_complete;
	int m_idx;
};

int Trie::m_sStrIdx = 0;

class JointSet{
public:
	JointSet(vector<Node>& nodes){
		m_groupIds.resize(nodes.size(), 0);
		for (size_t i = 0; i < m_groupIds.size(); i++)
		{
			m_groupIds[i] = i;
		}
		m_groupSizes.resize(nodes.size(), 1);
		m_groupNum = nodes.size();
	}

	void Union(int id1, int id2){
		int gId1 = find(id1);
		int gId2 = find(id2);

		if (gId1 != gId2){
			int newSize = m_groupSizes[gId1] + m_groupSizes[gId2];
			if (m_groupSizes[gId1] < m_groupSizes[gId2]){
				m_groupIds[gId1] = m_groupIds[gId2];
			} else{
				m_groupIds[gId2] = m_groupIds[gId1];
			}
			m_groupSizes[gId1] = newSize;
			m_groupSizes[gId2] = newSize;
			m_groupNum--;
		}
	}

	int find(int id){
		int gId = m_groupIds[id];
		while (gId != id)
		{
			id = gId;
			gId = m_groupIds[gId];
		}
		return gId;
	}

	int getSetCount(){
		return m_groupNum;
	}

private:
	vector<int> m_groupIds;
	vector<int> m_groupSizes;
	int         m_groupNum;
};

bool isConnected(vector<Node>& colorNodes){
	JointSet jset(colorNodes);

	vector<int> visited(colorNodes.size(), 0);
	stack<int> dfsStack;
	dfsStack.push(0);

	while (!dfsStack.empty())
	{
		int startId = dfsStack.top();
		Node& node = colorNodes[dfsStack.top()];
		visited[dfsStack.top()] = 1;
		dfsStack.pop();

		for (size_t i = 0; i < node.links.size(); i++)
		{
			if (visited[node.links[i]] == 0){
				dfsStack.push(node.links[i]);
			}
			jset.Union(startId, node.links[i]);
		}
	}
	
	return jset.getSetCount() == 1;
}

bool testEularPath(vector<Node>& colorNodes){
	// colorNode graph is a connected graph.
	if (!isConnected(colorNodes))
		return false;

	int degree = 0;
	for (size_t i = 0; i < colorNodes.size() && degree < 3; i++)
	{
		if (colorNodes[i].links.size() % 2){
			degree++;
		}
	}

	return (degree == 0) || (degree == 2);
}

#if 0
char *colorNames[] = { 
	"aliceblue",
	"antiquewhite",
	"aqua",
	"aquamarine",
	"azure",
	"beige",
	"bisque",
	"black",
	"blanchedalmond",
	"blue",
	"blueviolet",
	"brown",
	"burlywood",
	"cadetblue",
	"chartreuse",
	"chocolate",
	"coral",
	"cornflowerblue",
	"cornsilk",
	"crimson",
	"cyan",
	"darkblue",
	"darkcyan",
	"darkgoldenrod",
	"darkgray",
	"darkgrey",
	"darkgreen",
	"darkkhaki",
	"darkmagenta",
	"darkolivegreen",
	"darkorange",
	"darkorchid",
	"darkred",
	"darksalmon",
	"darkseagreen",
	"darkslateblue",
	"darkslategray",
	"darkslategrey",
	"darkturquoise",
	"darkviolet",
	"deeppink",
	"deepskyblue",
	"dimgray",
	"dimgrey",
	"dodgerblue",
	"firebrick",
	"floralwhite",
	"forestgreen",
	"fuchsia",
	"gainsboro",
	"ghostwhite",
	"gold",
	"goldenrod",
	"gray",
	"grey",
	"green",
	"greenyellow",
	"honeydew",
	"hotpink",
	"indianred",
	"indigo",
	"ivory",
	"khaki",
	"lavender",
	"lavenderblush",
	"lawngreen",
	"lemonchiffon",
	"lightblue",
	"lightcoral",
	"lightcyan",
	"lightgolden",
	"lightgray",
	"lightgrey",
	"lightgreen",
	"lightpink",
	"lightsalmon",
	"lightseagreen",
	"lightskyblue",
	"lightslategray",
	"lightslategrey",
	"lightsteelblue",
	"lightyellow",
	"lime",
	"limegreen",
	"linen",
	"magenta",
	"maroon",
	"mediumaquamarine",
	"mediumblue",
	"mediumorchid",
	"mediumpurple",
	"mediumseagreen",
	"mediumslateblue",
	"mediumspringgreen",
	"mediumturquoise",
	"mediumvioletred",
	"midnightblue",
	"mintcream",
	"mistyrose",
	"moccasin",
	"navajowhite",
	"navy",
	"oldlace",
	"olive",
	"olivedrab",
	"orange",
	"orangered",
	"orchid",
	"palegoldenrod",
	"palegreen",
	"paleturquoise",
	"palevioletred",
	"papayawhip",
	"peachpuff",
	"peru",
	"pink",
	"plum"
};

void generateTestCases(){
	time_t seed = time(NULL);
	srand((int)seed);

	FILE* fp = fopen("1.input", "w");
	int n = 200000;
	char buf[100];
	int colorNum = sizeof(colorNames) / sizeof(colorNames[0]);
	while (n--)
	{
		int colorA = rand() % (colorNum);
		int colorB = rand() % (colorNum);
		int pos = 0;
		sprintf(buf, "%s %s\n", colorNames[colorA], colorNames[colorB]);
		fwrite(buf, sizeof(char), strlen(buf), fp);
	}

	fclose(fp);
}
#endif

int main(int argc, char** argv){
	//generateTestCases();
	char str1[32];
	char str2[32];
	map<string, int> colorId;
	vector<Node> colors(4096, Node());
	int idx = 0;
	Trie trie;
	while (fscanf(stdin, "%s %s", str1, str2) != EOF)
	{
		int idx1 = trie.Insert(string(str1));
		int idx2 = trie.Insert(string(str2));

		if (colors.size() < trie.getStringCount()){
			colors.resize(trie.getStringCount()*1.5);
		}

		colors[idx1].color = idx1;
		colors[idx1].links.push_back(idx2);
		colors[idx2].color = idx2;
		colors[idx2].links.push_back(idx1);
	}

	colors.resize(trie.getStringCount());
	bool ret = testEularPath(colors);
	if (ret)
		cout << "Possible" << endl;
	else
		cout << "Impossible" << endl;
	return 0;
}