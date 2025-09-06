#include <vector>
#include <numeric>
using namespace std;
//----------------------------------------------------------------------------

vector<vector<pair<int, int>>> node;			// список смежности		
vector<int> dist;				// расстояния 
int V;					// количество вершин

void Bellman(int start) {
	dist[start] = 0;
	for (int i = 0; i < V - 1; i++)
		for (int j = 0; j < node.size(); j++)
			for (auto u : node[j])
				dist[u.first] = std::min(dist[u.first], dist[j] + u.second);
}

