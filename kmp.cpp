#include <vector>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------------------------

vector<int> b;												// таблица возвратов
void kmpPreprocess(string p) {								// функция заполняющая таблицу, p - паттерн
	b.resize(p.size()); b[0] = -1;
	int i = 0, j = -1;
	while (i < p.size()) {
		while (j >= 0 && p[j] != p[i]) j = b[j];			// несовпадение, восстановить j
		j++; i++;
		b[i] = j;
	}
}

void kmpSearch(string s, string p) {							// поиск совпадений. s - строка, p - паттерн
	int i = 0, j = 0;
	while (i < s.size()) {
		while (j >= 0 && s[i] != p[j]) j = b[j];			// несовпадение, восстановить j
		i++; j++;
		if (j == p.size()) {
			// (i-j) это индекс совпадения(совершить действие)
			j = b[j];
		}
	}
}
