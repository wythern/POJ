#include <stdio.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
using namespace std;

struct Person{
	int id;
	vector<int> contacts;
	vector<int> transcosts;
};

int getNearestPersonId(vector<Person>& persons, vector<int>& visited, vector<int>& transcost){
	int pId = -1;
	int minCost = INT_MAX;
	for (size_t i = 0; i < persons.size(); i++)
	{
		if (visited[i] == 0 && transcost[i] < minCost){
			pId = i;
			minCost = transcost[i];
		}
	}

	return pId;
}

int dijkstra(vector<Person>& persons, int kicker = 0){
	vector<int> visited(persons.size(), 0);
	vector<int> transcost(persons.size(), INT_MAX);
	transcost[kicker] = 0;
	while (1)
	{
		int personId = getNearestPersonId(persons, visited, transcost);
		if (personId == -1)
			break;

		visited[personId] = 1;
		for (size_t i = 0; i < persons[personId].contacts.size(); i++)
		{
			if (visited[persons[personId].contacts[i]] == 0){
				transcost[persons[personId].contacts[i]] = min(transcost[persons[personId].contacts[i]],
					transcost[personId] + persons[personId].transcosts[i]);
			}
		}
	}

	vector<int>::iterator itMaxCost = max_element(transcost.begin(), transcost.end());
	//int personId = distance(transcost.begin(), itMaxCost);

	return *itMaxCost;
}

int main(int argc, char** argv){
	while (1)
	{
		int N = 0;
		scanf("%d", &N);
		if (!N)
			break;

		vector<Person> persons;
		int id = 0;
		while (N--)
		{
			int M;
			scanf("%d", &M);
			Person person;
			person.id = id++;
			while (M--)
			{
				int P, T;
				scanf("%d %d", &P, &T);
				person.contacts.push_back(P - 1);
				person.transcosts.push_back(T);
			}

			persons.push_back(person);
		}

		int minKicker;
		int minTime = INT_MAX;
		for (size_t i = 0; i < persons.size(); i++)
		{
			int time = dijkstra(persons, i);
			if (minTime > time){
				minKicker = i + 1;
				minTime = time;
			}
		}

		if (minTime == INT_MAX)
			cout << "disjoint" << endl;
		else
			cout << minKicker << " " << minTime << endl;
	}

	return 0;
}
