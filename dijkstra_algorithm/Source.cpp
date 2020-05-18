#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <ctime>

using namespace std;

struct Graph {
public:
	int numberOfCities;
	int numberOfRoads;
	int startPoint;
	int finishPoint;
	vector<vector<int>>edges;
};

//bool visite[1000000];

void ReadFile(string file);


int main() {
	int N = 0, M = 0, S = 0, T = 0;
	ifstream file("input5.txt");
	if (!file) {
		cout << "Can't open file";
		return 0;
	}
	else {
		file >> N >> M >> S >> T;
		S--;
		T--;
		cout << "Params: N=" << N << ", M=" << M << ", S=" << S << ", T=" << T << "." << endl;

		vector<int> visite(1000000);
		vector<int> dist(1000000);
		for (int i = 0; i < 1000000; i++) {
			dist[i] = INT_MAX;
			visite[i] = false;
		}

		vector<vector<int>>edges(N, vector<int>(N, 0));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				edges[i][j] = INT_MAX;
			}
		}

		for (int i = 0; i < M; i++) {
			int a, b, d;
			file >> a >> b >> d;
			edges[a - 1][b - 1] = edges[b - 1][a - 1] = d;
		}

		for (int i = 0; i < 1000000; i++) {
			visite[i] = false;
			//dist[i] = INT_MAX;
		}

		dist[S] = 0;
		visite[S] = true;

		set<pair<int, int> > q;
		for (int i = 0; i < N; ++i)
		{
			q.insert(make_pair(dist[i], i));
		}


		cout << "Start" << endl;
		unsigned int start_time = clock();
		while (!q.empty()) {
			pair<int, int> cur = *q.begin();
			q.erase(q.begin());

			for (int i = 0; i < (int)edges[cur.second].size(); ++i) {
				
				if (!visite[i] && edges[cur.second][i] != INT_MAX && edges[cur.second][i] + dist[cur.second] < dist[i]) {
					
					q.erase(make_pair(dist[i], i));

					int temp = dist[i];
					if (edges[cur.second][i] != INT_MAX)
						dist[i] = edges[cur.second][i] + dist[cur.second];
					if (temp > dist[i]) {
						q.insert(make_pair(dist[i], i));
					}
				}
			}
		}
		unsigned int end_time = clock(); // конечное время
		unsigned int search_time = end_time - start_time;
		cout << "runtime = " << search_time / 1000.0 << endl;
		cout << "Distance: " << dist[T] << ' ';
	}
	return 0;
}

void ReadFile(string File) {

}