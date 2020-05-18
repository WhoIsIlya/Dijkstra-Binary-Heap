#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

bool visite[1000000];
int dist[1000000];

int main() {
	int N = 0, M = 0, S = 0, T = 0;
	int** ary;
	int** data;
	ifstream file("input5.txt");
	if (!file) {
		cout << "Can't open file";
		return 0;
	}
	else {
		file >> N;
		file >> M;
		file >> S;
		S--;
		file >> T;
		T--;
		cout << "Params: N=" << N << ", M=" << M << ", S=" << S << ", T=" << T << "." << endl;

		int n = M - 1;
		vector<vector<int>>v(N, vector<int>(N, 0));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				v[i][j] = INT_MAX;
			}
		}

		for (int i = 0; i < M; i++) {
			int a, b, d;
			file >> a >> b >> d;
			v[a - 1][b - 1] = v[b - 1][a - 1] = d;
		}

		for (int i = 0; i < 1000000; i++) {
			visite[i] = false;
			dist[i] = INT_MAX;
		}

		dist[S] = 0;
		visite[S] = true;

		queue<int> q;
		q.push(S);
		cout << "Start" << endl;
		unsigned int start_time = clock();
		while (!q.empty()) {

			int vertex = q.front();
			q.pop();
			unsigned int start_time = clock();
			for (int j = 0; j < v[vertex].size(); j++) {
				//cout << "Vertex:" << vertex+1 << endl;
				//cout << "J: " << j+1 << endl;
				if (!visite[j] && v[vertex][j] != INT_MAX && v[vertex][j] + dist[vertex] < dist[j]) {

					//cout << "J +if: " << j+1 << endl;
					//cout << "v[vertex][j]" << v[vertex][j] << endl;
					//cout << "dist[vertex]" << dist[vertex] << endl;
					//cout << "dist[j]" << dist[j] << endl;
					int temp = dist[j];
					if (v[vertex][j] != INT_MAX)
						dist[j] = v[vertex][j] + dist[vertex];
					if (temp > dist[j])
						q.push(j);
					//cout << "new dist[j]" << dist[j] << endl << endl;
				}
			}
		}
		unsigned int end_time = clock(); // конечное время
		unsigned int search_time = end_time - start_time;
		cout << "runtime = " << search_time / 1000.0 << endl;
		cout << "Distance: " << dist[T] << ' ';
	}
		
																																						/*
																																						MATRIX OUTPUT
																																												
		cout << internal << setw(3) << "x" << " ";
		for (int i = 0; i < N; i++) {
			cout << internal << setw(3) << i+1 << " ";
		}
		cout << endl;
		
		for (int i = 0; i < N; i++) {
			cout << internal << setw(3) << i+1 << " ";
			for (int j = 0; j < N; j++) {
				if (v[i][j] != INT_MAX) {
					cout << internal << setw(3) << v[i][j] << " ";
				}
				else {
					cout << internal << setw(3) << "-" << " ";
				}
					
			}
			cout << endl;
		}
	}
	*/

	//-------------------------------------------------



	return 0;
}