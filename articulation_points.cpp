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
	int branch = 0;
	for (long long v : graph[u]) {
		if (v == p) {
			continue;
		}
		if (used[v]) { // ребро цикла
			d[u] = std::min(d[u], h[v]);
		}
		else { // ребро дерева
			branch++;
			dfs(v, u);
			d[u] = std::min(d[u], d[v]);
		}
		if (h[u] <= d[v] && p != -1) { 
			// сюда попадаем, если вершина u - точка сочленения
		}
	}
	if (p == -1 && branch > 1) { //(вершина, от которой запустили dfs)
		// сюда попадаем, если вершина u - точка сочленения
	}
}
