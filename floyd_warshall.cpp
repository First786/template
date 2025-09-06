#include <vector>
#include <numeric>
using namespace std;
//----------------------------------------------------------------------------

vector<vector<int>> node;	// матрица смежности(где нет ребра там INF)				
vector<vector<int>> ans;		// итоговая матрица

void Floyd() {
	ans = node;
	for (int k = 0; k < node.size(); k++)
		for (int i = 0; i < node.size(); i++)
			for (int j = 0; j < node.size(); j++)
				ans[i][j] = std::min(ans[i][j], ans[i][k] + ans[k][j]);
}
