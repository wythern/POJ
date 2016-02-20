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

struct Truck{
	char code[8];
};

int typeDistance(Truck& tA, Truck& tB){
	int dist = 0;
	for (size_t i = 0; i < strlen(tA.code); i++)
	{
		if (tA.code[i] != tB.code[i])
			dist++;
	}
	return dist;
}

int nearestTruck(vector<Truck>& trucks, vector<int>& visited, vector<int>& dists){
	int minDist = INT_MAX;
	int truckId = -1;
	for (size_t i = 0; i < trucks.size(); i++)
	{
		if (visited[i] == 0){
			if (dists[i] < minDist){
				minDist = dists[i];
				truckId = i;
			}
		}
	}

	return truckId;
}

int minProductTree(vector<Truck>& trucks){
	vector<int> visited(trucks.size(), 0);
	vector<int> dists(trucks.size(), INT_MAX);
	vector<int> prevTruck(trucks.size(), -1);
	dists[0] = 0;

	int sumTree = 0;
	while (1)
	{
		int truckId = nearestTruck(trucks, visited, dists);
		if (truckId == -1)
			break;

		visited[truckId] = 1;
		if (prevTruck[truckId] != -1)
			sumTree += typeDistance(trucks[truckId], trucks[prevTruck[truckId]]);

		for (size_t i = 0; i < trucks.size(); i++)
		{
			if (visited[i] == 0){
				if (dists[i] > typeDistance(trucks[truckId], trucks[i])){
					dists[i] = typeDistance(trucks[truckId], trucks[i]);
					prevTruck[i] = truckId;
				}
			}
		}
	}

	return sumTree;
}


int main(int argc, char** argv){
	while (1){
		int N;
		scanf("%d/n", &N);
		if (!N)
			break;

		vector<Truck> trucks;
		while (N--){
			Truck truck;
			scanf("%8s", truck.code);
			trucks.push_back(truck);
		}

		cout << "The highest possible quality is 1/" << minProductTree(trucks) << "." << endl;
	}

	return 0;
}