#include <vector>
#include <iostream>
#include <queue>
using namespace std;
//---------------------------------------------------------------------------------------------

vector<vector<long long>> graph;
vector<bool> used;
vector<int> h, d; // h - глубина данной вершины в дереве dfs, d - мин. глуб. достиж. верш.

void dfs(int u, int p = -1) {
	used[u] = true;
	d[u] = h[u] = (p == -1 ? 1 : h[p] + 1);
	for (long long v : graph[u]) {
		if (v == p) {
			continue;
		}
		if (used[v]) { // ребро цикла
			d[u] = std::min(d[u], h[v]);
		}
		else { // ребро дерева
			dfs(v, u);
			d[u] = std::min(d[u], d[v]);
		}
		if (h[u] < d[v]) { 
			// сюда попадаем, если ребро (u, v) - мост
			//cout << format("{} <-> {} - мост\n", u, v);
		}
	
    }
}