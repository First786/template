#include <vector>
#include <numeric>
using namespace std;
//----------------------------------------------------------------------------

class DSU
{
private:
	vector<int> path;	// родитель вершины i
	vector<int> rank;	// верхняя оценка размера дерева
public:
	DSU(int n)	// генерируем массив path и rank
	{
		path.resize(n); iota(path.begin(), path.end(), 0);
		rank.resize(n, 1);
	}
	int findSet(int a)	// поиск родителя множества
	{
		return path[a] == a ? a : path[a] = findSet(path[a]);
	}
	bool isSameSet(int a, int b) { return findSet(a) == findSet(b); }	// проверка равны ли множества
	void unionSet(int a, int b)	// объединить два множества
	{
		int p1 = findSet(a), p2 = findSet(b); if (p1 == p2) return;
		if (rank[p1] < rank[p2]) std::swap(p1, p2);
		path[p2] = p1;
		if (rank[p1] == rank[p2]) rank[p1]++;
	}
};
