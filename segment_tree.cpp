#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

class SegmentTree {
private:
	vector<int> tree, a;
	int left(int i) { return (i << 1); }
	int right(int i) { return (i << 1) + 1; }

	void build(int p, int l, int r)
	{
		if (l == r) { tree[p] = l; return; }
		build(left(p), l, (l + r) / 2);
		build(right(p), (l + r) / 2 + 1, r);
		int p1 = tree[left(p)], p2 = tree[right(p)];
		tree[p] = ((a[p1] <= a[p2]) ? p1 : p2);
	}
	int rmq(int p, int l, int r, int i, int j)
	{
		if (i > r || j < l) return -1;
		if (i <= l && r <= j) return tree[p];
		int p1 = rmq(left(p), l, (l + r) / 2, i, j), p2 = rmq(right(p), (l + r) / 2 + 1, r, i, j);
		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
		return ((a[p1] <= a[p2]) ? p1 : p2);
	}
	void change(int p, int l, int r, int i, int value)
	{
		if (i < l || i > r) return;
		if (l == r) {
			a[i] = value; return;
		}
		change(left(p), l, (l + r) / 2, i, value);
		change(right(p), (l + r) / 2 + 1, r, i, value);
		int p1 = tree[left(p)], p2 = tree[right(p)];
		tree[p] = ((a[p1] <= a[p2]) ? p1 : p2);
	}
public:
	SegmentTree(vector<int> A) {
		a = A;
		tree.resize(a.size() * 4);
		build(1, 0, A.size() - 1);
	}
	int rmq(int i, int j) {
		return rmq(1, 0, a.size() - 1, i, j);
	}
	void upd(int i, int value) {
		change(1, 0, a.size() - 1, i, value);
	}
};
