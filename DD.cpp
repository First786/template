#include <vector>
#include <iostream>
#include <queue>
using namespace std;
//---------------------------------------------------------------------------------------------

struct Node {
    int val, prior, size;
    bool rev;
    Node *l, *r;

    Node(int v) : val(v), prior(rand()), size(1), rev(false), l(nullptr), r(nullptr) {}
};

int getSize(Node* t) {
    return t ? t->size : 0;
}

void update(Node* t) {
    if (t) {
        t->size = getSize(t->l) + 1 + getSize(t->r);
    }
}

void push(Node* t) {
    if (t && t->rev) {
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = false;
    }
}

// Разделение на [0, k), [k, ...)
void split(Node* t, int k, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
    if (getSize(t->l) >= k) {
        split(t->l, k, l, t->l);
        r = t;
    } else {
        split(t->r, k - getSize(t->l) - 1, t->r, r);
        l = t;
    }
    update(t);
}

// Слияние двух деревьев
Node* merge(Node* l, Node* r) {
    push(l); push(r);
    if (!l || !r) return l ? l : r;
    if (l->prior > r->prior) {
        l->r = merge(l->r, r);
        update(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        update(r);
        return r;
    }
}

class Treap {
private:
    Node* root = nullptr;

public:
    void insert(int pos, int val) {
        Node *t1, *t2;
        split(root, pos, t1, t2);
        root = merge(merge(t1, new Node(val)), t2);
    }

    void erase(int pos) {
        Node *t1, *t2, *t3;
        split(root, pos, t1, t2);
        split(t2, 1, t2, t3);
        delete t2;
        root = merge(t1, t3);
    }

    void reverse(int l, int r) {
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->rev ^= 1;
        root = merge(t1, merge(t2, t3));
    }

    int get(int pos) {
        Node* t = root;
        while (t) {
            push(t);
            int lsz = getSize(t->l);
            if (pos < lsz)
                t = t->l;
            else if (pos == lsz)
                return t->val;
            else
                pos -= lsz + 1, t = t->r;
        }
        throw out_of_range("Index out of range");
    }

    void print() {
        print(root);
        cout << '\n';
    }

    void print(Node* t) {
        if (!t) return;
        push(t);
        print(t->l);
        cout << t->val << ' ';
        print(t->r);
    }
};