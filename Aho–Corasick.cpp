#include <vector>
#include <iostream>
#include <queue>
using namespace std;
//---------------------------------------------------------------------------------------------

class korasik {
public:
	struct Node {
		int to[26];
		int link;
		int output;
		vector<int> idx_terminate;

		Node() {
			for (int i = 0; i < 26; i++) to[i] = -1;
			link = 0;
			output = 0;
		}
	};

private:
	vector<Node> trie;
	int root;

	void build_automat_with_bfs() {
		queue<int> q;
		trie[root].link = root;

		// первый слой
		for (int c = 0; c < 26; c++) {
			int v = trie[root].to[c];
			if (v != -1) {
				trie[v].link = root;
				q.push(v);
			}
			else {
				trie[root].to[c] = root;
			}
		}

		// BFS
		while (!q.empty()) {
			int v = q.front();
			q.pop();

			int p = trie[v].link;
			trie[v].output = trie[p].idx_terminate.empty() ? trie[p].output : p;

			for (int c = 0; c < 26; c++) {
				int u = trie[v].to[c];
				if (u != -1) {
					trie[u].link = trie[p].to[c];
					q.push(u);
				}
				else {
					trie[v].to[c] = trie[p].to[c];
				}
			}
		}
	}

public:
	korasik(const vector<string>& array) {
		trie.reserve(1000000);
		trie.emplace_back();
		root = 0;

		for (int i = 0; i < (int)array.size(); i++) {
			int v = root;
			for (char ch : array[i]) {
				int c = ch - 'a';
				if (trie[v].to[c] == -1) {
					trie[v].to[c] = trie.size();
					trie.emplace_back();
				}
				v = trie[v].to[c];
			}
			trie[v].idx_terminate.push_back(i);
		}

		build_automat_with_bfs();
	}

	int get_root() const {
		return root;
	}

	int get_link(int v) const {
		return trie[v].link;
	}

	int get_go(int v, int c) const {
		return trie[v].to[c];
	}

	int get_output(int v) const {
		return trie[v].output;
	}

	const vector<int>& get_term(int v) const {
		return trie[v].idx_terminate;
	}
};
