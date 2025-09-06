#include <vector>
#include <numeric>
#include <queue>
using namespace std;
//----------------------------------------------------------------------------

class FenvicTree {
private:
	vector<int> ft;
	int LSOne(int i) { return (i & (-i)); }	// получение самого младшего единичного бита
	int rsq(int b) {
		int sum = 0; for (;b; b -= LSOne(b)) sum += ft[b];
		return sum;
	}
public:
	FenvicTree(int n) { ft.resize(n + 1); }
	int rsq(int a, int b) {   // вернуть сумму на отрезке [a, b]
		return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
	}
	void adjust(int k, int v) { // индексация с 1.  Прибавить k-тому элементу значения v
		for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v;
	}
};
