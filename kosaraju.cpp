#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

vector<vector<int>> g, t; // g - основной граф, t - транспонированный граф
vector<int> order; // сортировка вершин по времени выхода из них
vector<bool> used; // была ли вершина посещена в первом dfs
vector<int> component; // номер компоненты i-той вершины
int cnt_components = 0; 

//сортировка вершин по времени выхода(в обратном порядке)
void dfs1(int v) {
	used[v] = true;
	for (auto u : g[v]) {
		if (!used[u]) {
			dfs1(u);
		}
	}
	order.push_back(v);
}

//маркировка компонент
void dfs2(int v) {
	component[v] = cnt_components;
	for (auto u : t[v]) {
		if (component[u] == 0) {
			dfs2(u);
		}
	}
}

void kosaraju() {
	used.assign(g.size(), false);
	component.assign(g.size(), 0);
	cnt_components = 0;

	t.assign(g.size(), vector<int>(0));
	for (int v = 0; v < g.size(); v++) {	//транспонирование графа
		for (int u : g[v]) {
			t[u].push_back(v);
		}
	}

	for (int i = 0; i < g.size(); i++) {  //сортировка 
		if (!used[i]) {
			dfs1(i);
		}
	}

	reverse(order.begin(), order.end());
	for (int v : order) {	//выделяем компоненты
		if (component[v] == 0) {
			cnt_components++;
			dfs2(v);
		}
	}
}
