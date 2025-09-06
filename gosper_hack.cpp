#include <vector>
#include <iostream>
#include <numeric>
#include <bitset>
using namespace std;
//----------------------------------------------------------------------------

void main(){
    int k = 3, V = 10;
    int set = (1 << k) - 1;
    int limit = (1 << V);
    while (set < limit) {
        // Do your stuff with current set
        //doStuff(set);

        // Gosper's hack:
        int c = set & -set;
        int r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
        cout << bitset<11>(set) << "\n";
    }
}