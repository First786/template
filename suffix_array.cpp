#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------------------------

class SuffixArray
{
private:
	string T;
	int n;
	vector<int> RA, tempRA, SA, tempSA, c;
	vector<int> LCP, PLCP;

	void countingSort(int k)				// сортировка подсчётом O(n) (сортируем по RA[SA[i]+k])
	{
		int maxi = max(300, n);				// максимальное значение в диапазоне 
		c.assign(c.size(), 0);				// выделяем место для подсчёта
		for (int i = 0; i < n; i++) c[i + k < n ? RA[i + k] : 0]++;							// считаем количество значений 
		for (int i = 0, suma = 0; i < maxi; i++) { int t = c[i]; c[i] = suma; suma += t; }	// ставим указатедб на место, с которого начинается позиция каждого ранга
		for (int i = 0; i < n; i++) tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];	// посчитали, теперь заполняем
		for (int i = 0; i < n; i++) SA[i] = tempSA[i];		// переписываем полученные результаты
	}
	void build()											// строим суффиксный массив O(nlog(n))
	{
		c.resize(max(300, n));
		for (int i = 0; i < n; i++) { SA[i] = i; RA[i] = T[i]; } // заполняем начальные места и начальные ранги
		for (int k = 1; k < n; k <<= 1)								// сортируем пары (RA[SA[i]], RA[SA[i]+k])
		{
			countingSort(k);								// сначала по паре RA[SA[i]+k] сортируем
			countingSort(0);								// затем по паре RA[SA[i]] 
			int r = 0;
			tempRA[SA[0]] = r;								// на первом месте всегда символ $(самый наименьший)
			for (int i = 1; i < n; i++) tempRA[SA[i]] =		// каждый новый RA[SA[i-1]] <= RA[SA[i]], если равны, то и ранги у них равны
				(RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
			for (int i = 0; i < n; i++) RA[i] = tempRA[i];	// записываем новые ранги
		}
	}
public:
	SuffixArray(string s)
	{
		T = s + "$";										// приписываем в конец лексикографически маленький символ
		n = T.size();										
		RA.resize(max(300, n));
		SA.resize(max(300, n));
		tempRA = RA;
		tempSA = SA;
		LCP.resize(n); PLCP.resize(n);						// выделяем место под наибольший общий префикс
		build();											// строим суффиксный массив
	}
	pair<int, int> stringMatching(string p)					// ищем суффиксы, которые начинаются с "p". O(mlog(n)) (бинарный поиск)
	{
		int lo = 0, hi = n - 1, mid = lo;
		while (lo < hi)										// ищем нижнюю границу вхождения "p" бинарным поиском
		{
			mid = (lo + hi) / 2;
			if (T.compare(SA[mid], p.size(), p) >= 0) hi = mid;
			else lo = mid + 1;
		}
		if (T.compare(SA[lo], p.size(), p) != 0) return {-1,-1};
		pair<int, int> ans{ lo,-1 };
		lo = 0; hi = n - 1;
		while (lo < hi)										// ищем верхнюю границу вхождения "p" бинарным поиском
		{
			mid = (lo + hi) / 2;
			if (T.compare(SA[mid], p.size(), p) > 0) hi = mid;
			else lo = mid + 1;
		}
		if (T.compare(SA[hi], p.size(), p) != 0) hi--;
		ans.second = hi;

		return ans;
	}
	void computeLCP()
	{
		vector<int> phi(n,-1); for (int i = 1;i < n; i++) phi[SA[i]] = SA[i - 1];
		for (int i = 0, L = 0; i < n; i++)
		{
			if (phi[i] == -1) { PLCP[i] = 0; continue; }
			while (T[i + L] == T[phi[i] + L]) L++;
			PLCP[i] = L;
			L = max(L - 1, 0);
		}
		for (int i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
	}
};
