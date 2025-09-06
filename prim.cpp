#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

void prima(vector<vector<vector<long long>>>& graph) {
	priority_queue<vector<long long>, vector<vector<long long>>, greater<vector<long long>>> pq;
	vector<bool> flag(graph.size());
	flag[0] = true;
	int countVertex = 1;
	for (int i = 0; i < graph[0].size(); i++) {
		pq.push({ graph[0][i][1], graph[0][i][0], i });
	}
	vector<vector<vector<long long>>> gr(graph.size());
	while (countVertex != graph.size()) {
		long long a = pq.top()[1];
		long long b = pq.top()[2];
		long long w = pq.top()[0];
		pq.pop();
		if (!flag[a]) {
			flag[a] = true;
			gr[a].push_back({ b, w });
			gr[b].push_back({ a, w });
			countVertex++;
			for (int i = 0; i < graph[a].size(); i++) {
				pq.push({ graph[a][i][1], graph[a][i][0], a});
			}
		}
	}
}
