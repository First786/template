#include <vector>
using namespace std;
//----------------------------------------------------------------------------

vector<vector<int>> node;
vector<vector<int>> dp;			// изначально сделать матрицу n на 2 из (-1)

int mvc(int u, bool flag)
{
	if (dp[u][flag] != -1) return dp[u][flag];
	int child = flag;
	for (auto v : node[u])
		if (flag)
			child += min(mvc(v, 1), mvc(v, 0));
		else 
			child += mvc(v, 1);
	return dp[u][flag] = child;
}

