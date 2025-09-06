#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

vector<vector<int>> dp;								// таблица дп
int spacePenalty = -1;						// штраф за пробел
int mismatchPenalty = -1;					// штраф за несовпадение букв
int reward = 2;								// награда за совпадение

pair<string, string> recover(string a, string b) {
	string _a, _b;							// исходные строки
	int _i = a.size(), _j = b.size();
	while (_i > 0 && _j > 0)				// идём снизу вверх восстанавливаем слова
	{
		if (dp[_i - 1][_j - 1] + (a[_i - 1] == b[_j - 1] ? reward : mismatchPenalty) == dp[_i][_j])
		{
			_a += a[_i - 1]; _b += b[_j - 1]; _i--; _j--;				// если пришли с диагонали, то записываем буквы в обе строки
		}
		else if (dp[_i][_j - 1] + spacePenalty == dp[_i][_j])
		{
			_a += "_"; _b += b[_j - 1]; _j--;							// если пришли слева, то пробел в строку "a"
		}
		else if (dp[_i - 1][_j] + spacePenalty == dp[_i][_j])
		{
			_a += a[_i - 1]; _b += "_"; _i--;							// если пришли слева, то пробел в строку "b"
		}
	}
	while (_i > 0)							// если заполнили всё слово _b, дозаполняем слово _a
	{
		_b += "_"; _a += a[_i - 1]; _i--;
	}
	while (_j > 0)							// если заполнили всё слово _a, дозаполняем слово _b
	{
		_a += "_"; _b += b[_j - 1]; _j--;
	}
	reverse(_a.begin(), _a.end());			// переворачиваем слова, т к заполнили задом на перёд
	reverse(_b.begin(), _b.end());
	return { _a, _b };
}

pair<string, string> regulation(string a, string b)		// регулирует строки "a" и "b" по заданным "штрафным"
{
	dp.resize(a.size() + 1, vector<int>(b.size() + 1)); dp[0][0] = 0;
	for (int i = 1; i <= a.size(); i++) dp[i][0] = dp[i - 1][0] + spacePenalty;	// заполняем основные варианты
	for (int i = 1; i <= b.size(); i++) dp[0][i] = dp[0][i - 1] + spacePenalty;	// заполняем основные варианты

	for (int i = 1; i <= a.size(); i++)
		for (int j = 1; j <= b.size(); j++)
			dp[i][j] = max(dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? reward : mismatchPenalty),
				max(dp[i - 1][j], dp[i][j - 1]) + spacePenalty);					// восходящее дп, смотрим откуда прийти выгоднее
	//dp[a.size()][b.size()] - максимальная оценка
	return recover(a, b);			// возвращаем отрегулированные строки
}
