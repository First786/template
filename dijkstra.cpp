#include <vector>
#include <iostream>
#include <queue>
using namespace std;

//---------------------------------------------------------------------------------------------
vector<vector<pair<int,int>>> node;					
vector<int> dist;
void dij(int start)
{
	priority_queue<pair<int, int> ,vector<pair<int, int>>, greater<pair<int, int>>> pq; // храним {раст.до верш.,верш.}
	pq.push({0, start});
	dist[start] = 0;
	while (!pq.empty())
	{
		auto vertex = pq.top(); pq.pop();
		int u = vertex.second; int w = vertex.first; 
		if (w > dist[u]) continue;   //одна вершина может быть добавлена неск. раз
		for (auto i : node[u])
		{
			int v = i.first; int d = i.second;
			if (dist[v] > d + dist[u])
			{
				dist[v] = d + dist[u];
				pq.push({dist[v], v});
			}
		}
	}
}

