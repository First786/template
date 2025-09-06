#include <vector>
#include <numeric>
#include <queue>
using namespace std;
//----------------------------------------------------------------------------

vector<vector<int>> node, adj, potoc; // node - список смежности, adj - матрица смежности, potoc - сам поток
vector<int> p;							// p[i] --> вершина которая предшедствует вершине i при запуске bfs
int f, flow = 0;					// f - минимальный вес ребра, flow - величина потока
int start = 0, finish = 3;	// start - сток, finish - исток
void minflow(int s, int t) {
	while (t != s) {
		f = min(f, adj[p[t]][t]);  t = p[t];
	}
}
void bfs(int s, int t) {
	p.assign(p.size(), -1);	// массив предшедствующих вершин
	vector<bool> vis(node.size());	// массив посещённых вершин
	queue<int> q; q.push(s);	//стандартный bfs, который ищет путь от s->t
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (auto v : node[u]) {
			if (!vis[v] && adj[u][v] > 0) {
				vis[v] = 1;
				p[v] = u; q.push(v);	// для каждой вершины сохраняем её предка
				if (v == t) { f = 1e9; minflow(s, t); return; }	// если путь найден, то он кратчайший, ищём пропускную способность пути
			}
		}
	}
}
void goflow(int s, int t)
{
	while (t != s) {	// пропускаем поток
		adj[p[t]][t] -= f;	// уменьшаем пропускную способность прямого ребра
		adj[t][p[t]] += f;	// увеличиваем пропускную способность обратного ребра
		potoc[p[t]][t] += f; potoc[p[t]][t] = max(potoc[p[t]][t], 0);	// сохраняем сам поток
		potoc[t][p[t]] -= f; potoc[t][p[t]] = max(potoc[t][p[t]], 0);	// сохраняем сам поток
		t = p[t];	// делаем шаг назад по найденному пути
	}
}
void emond() {
	while (1) {
		f = 0;	// пока что наибольший пропускной путь имеет пропускну способность "0"
		bfs(start, finish);	// ищем путь от вершины "0" к вершине "1"

		//cout << f << "\n";
		if (f == 0) break;	// если найденный путь имеет пропускную способность 0, то поток максимальный
		flow += f;	// поток стал на "f" больше
		goflow(start, finish);	// пропускаем поток по найденому пути

	}
}
