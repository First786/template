#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

struct TrieNode
{
	TrieNode** children;								// исходящие вершины {'a', 'b', 'c',...}
	int flag=0;											// flag = 0, здесь нету префикса, flag = 1, здесь есть префикс, flag = 2, здесь конец слова
	TrieNode() {										
		children = new TrieNode * [26]; for (int i = 0; i < 26; i++) children[i] = nullptr; // Выделяем память под ссылки на исходящие вершина (чтобы этого не делать, можно использовать вектор)
	}
	~TrieNode() {										// очистка памяти
		for (int i = 0; i < 26; i++) 
			if (children[i] != nullptr)
				delete children[i];
		delete[] children; 
	}
};
class Trie
{
private:
	int countWord = 0;									// количество добавленных слов
	struct TrieNode *root;								// корень префиксного дерева
	int countSuffix(TrieNode* root)						// дфс (считает сколько префиксов исходит из заданной вершины)
	{
		int count = 0;
		if (root->flag != 0) count++;					// если данная вершина сама префикс, +1 префикс
		for (int i = 0; i < 26; i++) { if (root->children[i]) count += countSuffix(root->children[i]); }	// стандартный обход
		return count;
	}
public:
	Trie()
	{
		root = new TrieNode();							// создаём корень
	}
	~Trie() { delete root; }							// чистим память
	void insert(string s)								// добавляем слово в дерево(и все его суффиксы) (O(s.size()^2))
	{
		for (int i = s.size()-1; i >= 0; i--)			// перебираем все суффиксы
		{
			TrieNode* temp = root;
			for (int j = i; j < s.size(); j++)
			{
				if (!temp->children[s[j] - 'a'])
					temp->children[s[j] - 'a'] = new TrieNode();
				temp = temp->children[s[j] - 'a'];		// копаем вглубь до нужного префикса
			}
			temp->flag = (i == 0)?2:1;					// если конец слова, то флаг 2, если суффикс, то флаг 1
		}
		countWord++;
	}
	bool find(string s)									// проверяем на наличие паттерна в слове O(s.size())					
	{
		TrieNode* temp = root;
		for (int i = 0; i < s.size(); i++)				// делаем стандартный обход
		{
			if (!temp->children[s[i]-'a'])				// если дальше дерева нет, то нету слова
				return false;
			temp = temp->children[s[i] - 'a'];
		}
		return temp->flag != 0;							// если flag != 0, то данное слово, содержится в дереве
	}
	int countSuffix(string s)							// считаем количество суффиксов, которые начинаются с "s", за O("размер дерева" ^ 2)
	{
		TrieNode* temp = root;
		for (int i = 0; i < s.size(); i++)
		{
			if (!temp->children[s[i] - 'a'])
				return false;
			temp = temp->children[s[i] - 'a'];
		}												// копаем до "s"
		return countSuffix(temp);						// делаем обход, считаем сколько суффиксов у данного поддерева
	}
};

