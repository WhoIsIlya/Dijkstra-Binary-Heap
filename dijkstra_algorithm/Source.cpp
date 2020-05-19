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
	std::vector<std::vector<int>>edges;
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
	std::string fileName = "input5.txt";
	Graph DijkstraGraph = ReadFile(fileName, DijkstraGraph);
	Distances Result = DijkstraForward(DijkstraGraph);
	std::cout << "Distance: " << Result.distances[DijkstraGraph.finishPoint] << std::endl;
	std::vector<int> shortestPath = DijkstraBackward(DijkstraGraph, Result);

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

		inputGraph.edges.resize(inputGraph.numberOfCities, std::vector<int>(inputGraph.numberOfCities, 0));

		for (int i = 0; i < inputGraph.numberOfCities; i++) {
			for (int j = 0; j < inputGraph.numberOfCities; j++) {
				inputGraph.edges[i][j] = INT_MAX;
			}
		}

		for (int i = 0; i < inputGraph.numberOfRoads; i++) {
			int edgeStartPoint, edgeEndPoint, edgeWeight;
			file >> edgeStartPoint >> edgeEndPoint >> edgeWeight;
			inputGraph.edges[edgeStartPoint - 1][edgeEndPoint - 1] = inputGraph.edges[edgeEndPoint - 1][edgeStartPoint - 1] = edgeWeight;
		}
		
	}
	return inputGraph;
}

Distances DijkstraForward(Graph inputGraph) {
	
	std::vector<Heap> BinaryHeap;

	Distances Result;
	Result.distances.resize(inputGraph.numberOfCities);
	Result.previous.resize(inputGraph.numberOfCities);
	std::vector<int> visite(inputGraph.numberOfCities);

	for (int i = 0; i < inputGraph.numberOfCities; i++) {
		Result.distances[i] = INT_MAX;
		visite[i] = false;
	}

	Result.distances[inputGraph.startPoint] = 0;
	visite[inputGraph.startPoint] = true;

	BinaryHeap.push_back(Heap(0, inputGraph.startPoint));

	std::make_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());

	std::cout << "Start" << std::endl;
	unsigned int start_time = clock();
	while (!BinaryHeap.empty() ) {

		std::pop_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());
		Heap temp = BinaryHeap.back();
		BinaryHeap.pop_back();

		std::pair<int, int> cur;
		cur.first = temp.getDist();
		cur.second = temp.getCity();

		for (int i = 0; i < (int)inputGraph.edges[cur.second].size(); ++i) {

			if (!visite[i] && inputGraph.edges[cur.second][i] != INT_MAX && inputGraph.edges[cur.second][i] + Result.distances[cur.second] < Result.distances[i]) {


				int temp = Result.distances[i];
				if (inputGraph.edges[cur.second][i] != INT_MAX) {
					Result.distances[i] = inputGraph.edges[cur.second][i] + Result.distances[cur.second];
					Result.previous[i] = cur.second;
				}				
				if (temp > Result.distances[i]) {
					BinaryHeap.emplace_back(Heap(Result.distances[i], i));
					std::push_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());
				}
			}
		}
	}
	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time;
	std::cout << "runtime = " << search_time / 1000.0 << std::endl;
	return Result;
}

std::vector<int> DijkstraBackward(Graph inputGraph, Distances Result) {
	
	std::vector<int> path;
	for (int v = inputGraph.finishPoint; v != inputGraph.startPoint; v = Result.previous[v])
		path.push_back(v);
	path.push_back(inputGraph.startPoint);

	reverse(path.begin(), path.end());
	std::cout << "Path: ";
	for (int i = 0; i < path.size(); i++)
		std::cout << path[i] + 1 << ' ';
	std::cout << std::endl;
	return path;
}