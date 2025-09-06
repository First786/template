#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

typedef long long ll;
typedef std::vector<std::pair<long long, long long>> vllll;
typedef std::vector<ll> vll;
typedef std::pair<ll, ll> pll;

class SegmentTree {
private:
	vllll A;	// (значение минимума, количество)
	vll val;
	vll asign;
	ll n;
	ll left(ll n) { return (n << 1); }
	ll right(ll n) { return (n << 1) + 1; }
	void build(ll p, ll l, ll r) {
		if (l == r) {
			A[p] = { val[l], 1 };
			return;
		}
		build(left(p), l, (l + r) / 2);
		build(right(p), (l + r) / 2 + 1, r);
		auto [v1, c1] = A[left(p)];
		auto [v2, c2] = A[right(p)];
		if (v1 > v2) { swap(v1, v2); swap(c1, c2); }
		if (v1 == v2) { A[p] = { v1, c1 + c2 }; }
		else { A[p] = { v1,c1 }; }
	}
	void plus(ll p, ll l, ll r, ll i, ll j, ll v) {
		if (i > r || l > j) return;
		if (l >= i && j >= r) {
			asign[p] += v;
			return;
		}
		plus(left(p), l, (l + r) / 2, i, j, v);
		plus(right(p), (l + r) / 2 + 1, r, i, j, v);
		if (A[left(p)].first + asign[left(p)] == A[right(p)].first + asign[right(p)]) {
			A[p] = { A[left(p)].first + asign[left(p)], A[left(p)].second + A[right(p)].second};
		}
		else if (A[left(p)].first + asign[left(p)] < A[right(p)].first + asign[right(p)]) {
			A[p] = { A[left(p)].first + asign[left(p)] , A[left(p)].second };
		}
		else {
			A[p] = { A[right(p)].first + asign[right(p)] , A[right(p)].second };
		}
	}
	pll cnt(ll p, ll l, ll r, ll i, ll j) {
		if (j < l || i > r) return { -1, -1 };
		if (l >= i && j >= r) { return { A[p].first + asign[p], A[p].second }; }
		asign[left(p)] += asign[p];
		asign[right(p)] += asign[p];
		asign[p] = 0;
		auto [v1, c1] = cnt(left(p), l, (l + r) / 2, i, j);
		auto [v2, c2] = cnt(right(p), (l + r) / 2 + 1,r, i, j);
		if (v1 == -1 && c1 == -1) { return { v2, c2 }; }
		if (v2 == -1 && c2 == -1) { return { v1, c1 }; }
		if (v1 == v2) { return { v1, c1 + c2 }; }
		else if (v1 > v2) { return { v2, c2 }; }
		else { return { v1,c1 }; }
	}
public:
	SegmentTree(vll a) {
		val = a;
		n = (int)a.size();
		A.resize(4 * n);
		asign.assign(4 * n, 0);
		build(1, 0, n - 1);
	}
	void plus(ll i, ll j, ll v) { // прибавить на отрезке [i, j] число v, индексация с 0
		plus(1, 0, n - 1, i, j, v);
	}
	pll cnt(ll i, ll j) {           // возвращает {минимальный элемент, количество минимальных элементов на отрезке}
		return cnt(1, 0, n - 1, i, j);
	}
};
