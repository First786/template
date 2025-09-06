#include <vector>
#include <iostream>
#include <numeric>
#include <queue>
using namespace std;
//---------------------------------------------------------------------------------------------

class DSU {
private:
	vector<long long> path, rank;
	long long countSet;
public:
	DSU(int n) {
		path.resize(n); iota(path.begin(), path.end(), 0);
		rank.assign(n, 1);
		countSet = n;
	}
	long long findSet(long long a) {
		return (path[a] == a ? a : path[a] = findSet(path[a]));
	}
	long long isSameSet(long long a, long long b) {
		return findSet(a) == findSet(b);
	}
	void unionSet(long long a, long long b) {
		long long p1 = findSet(a), p2 = findSet(b);
		if (p1 == p2) return;
		if (rank[p1] > rank[p2]) std::swap(p1, p2);
		if (rank[p1] == rank[p2]) rank[p1]++;
		path[p2] = p1;
		countSet--;
	}
	bool isFull() {
		return countSet == 1;
	}
};

void kraskal(vector<vector<vector<long long>>>& graph) {
	DSU dsu(graph.size());
	priority_queue<vector<long long>, vector<vector<long long>>, greater<vector<long long>>> pq;
	for (int i = 0; i < (int)graph.size(); i++) {
		for (int j = 0; j < (int)graph[i].size(); j++) {
			pq.push({ graph[i][j][1], i, graph[i][j][0] });
		}
	}
	vector<vector<vector<long long>>> gr((int)graph.size()); // исходный остов
	while (!pq.empty()) {
		long long a = pq.top()[1];
		long long b = pq.top()[2];
		long long w = pq.top()[0];
		pq.pop();
		if (!dsu.isSameSet(a, b)) {
			dsu.unionSet(a, b);
			gr[a].push_back({ b, w });
			gr[b].push_back({ a, w });
		}
		if (dsu.isFull()) {
			break;
		}
	}
}
