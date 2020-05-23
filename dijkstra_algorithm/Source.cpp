/*
Разработчики: студенты группы ПСм-11 Свинчуков И.  и  Стародубцева А.
Среда выполнения: Visual Studio 2019
Инструкция запуска:
Чтобы собрать программу на Windows, нужно запустить Visual Studio, открыть директорию проекта и собрать проект,
 используя возможности IDE.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <ctime>

class Heap
{
	int Dist;
	int City;
public:
	Heap(int _Dist, int _y)
	{
		Dist = _Dist;
		City = _y;
	}
	int getDist() const { return Dist; }
	int getCity() const { return City; }
};

class myComparator
{
public:
	int operator() (const Heap& p1, const Heap& p2)
	{
		return p1.getDist() > p2.getDist();
	}
};

struct Graph {
public:
	int numberOfCities;
	int numberOfRoads;
	int startPoint;
	int finishPoint;
	std::vector<std::vector< std::pair<int, int>>> inputData;
};

struct Distances
{
	std::vector<int> distances;
	std::vector<int> previous;
};

Graph ReadFile(std::string fileName, Graph inputGraph);
Distances DijkstraForward(Graph inputGraph);
std::vector<int> DijkstraBackward(Graph inputGraph, Distances Result);

int main() {
	unsigned int start_time = clock();
	std::string fileName = "input.txt";
	Graph DijkstraGraph;
	DijkstraGraph = ReadFile(fileName, DijkstraGraph);
	Distances Result = DijkstraForward(DijkstraGraph);
	std::cout << Result.distances[DijkstraGraph.finishPoint] << std::endl;
	std::vector<int> shortestPath = DijkstraBackward(DijkstraGraph, Result);
	std::ofstream out;
	out.open("output.txt");
	if (out.is_open()) {
		out << Result.distances[DijkstraGraph.finishPoint] << std::endl;
	}
	for (int i = 0; i < shortestPath.size(); i++) {
		out << shortestPath[i] + 1 << ' ';
	}
	unsigned int end_time = clock();
	double search_time = end_time - start_time;
	std::cout << "runtime: " << search_time / 1000 << "s" << std::endl;
	std::getchar();
	return 0;
}

Graph ReadFile(std::string fileName, Graph inputGraph) {
	std::ifstream file(fileName);
	if (!file) {
		std::cout << "Can't open file";
	}
	else {
		
		file >> inputGraph.numberOfCities >> inputGraph.numberOfRoads >> inputGraph.startPoint >> inputGraph.finishPoint;
		inputGraph.startPoint--;
		inputGraph.finishPoint--;

		inputGraph.inputData.resize(inputGraph.numberOfCities);

		for (int i = 0; i < inputGraph.numberOfRoads; i++) {
			int edgeStartPoint, edgeEndPoint, edgeWeight;
			file >> edgeStartPoint >> edgeEndPoint >> edgeWeight;

			inputGraph.inputData[edgeStartPoint - 1].push_back(std::make_pair(edgeEndPoint - 1, edgeWeight));
			inputGraph.inputData[edgeEndPoint - 1].push_back(std::make_pair(edgeStartPoint - 1, edgeWeight));
		}
		
	}
	return inputGraph;
}

Distances DijkstraForward(Graph inputGraph) {
	
	std::vector<Heap> BinaryHeap;

	Distances Result;
	Result.distances.resize(inputGraph.numberOfCities);
	Result.previous.resize(inputGraph.numberOfCities);

	for (int i = 0; i < inputGraph.numberOfCities; i++) {
		Result.distances[i] = INT_MAX;
	}

	Result.distances[inputGraph.startPoint] = 0;

	BinaryHeap.push_back(Heap(0, inputGraph.startPoint));

	std::make_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());

	while (!BinaryHeap.empty() ) {

		std::pop_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());
		Heap temp = BinaryHeap.back();
		BinaryHeap.pop_back();
		

		std::pair<int, int> cur;
		cur.first = temp.getDist();
		cur.second = temp.getCity();

		if (cur.first > Result.distances[cur.second]){
			continue;
		}

		for (int i = 0; i < (int)inputGraph.inputData[cur.second].size(); ++i) {

			if (inputGraph.inputData[cur.second][i].second + Result.distances[cur.second] < Result.distances[inputGraph.inputData[cur.second][i].first]) {

				int temp = Result.distances[inputGraph.inputData[cur.second][i].first];

					Result.distances[inputGraph.inputData[cur.second][i].first] = inputGraph.inputData[cur.second][i].second + Result.distances[cur.second];
					Result.previous[inputGraph.inputData[cur.second][i].first] = cur.second;
						
				if (temp > Result.distances[inputGraph.inputData[cur.second][i].first]) {
					BinaryHeap.emplace_back(Heap(Result.distances[inputGraph.inputData[cur.second][i].first], inputGraph.inputData[cur.second][i].first));
					std::push_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());
				}
			}
		}
	}
	return Result;
}

std::vector<int> DijkstraBackward(Graph inputGraph, Distances Result) {
	
	std::vector<int> path;
	for (int v = inputGraph.finishPoint; v != inputGraph.startPoint; v = Result.previous[v])
		path.push_back(v);
	path.push_back(inputGraph.startPoint);

	reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i] + 1 << ' ';
	}
	std::cout << std::endl;
	return path;
}