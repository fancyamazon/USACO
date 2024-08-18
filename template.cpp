using namespace std;
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <string>
#include <cmath>
#include <bitset>
#include <functional>
#include <utility>
#include <numeric>

/*
If the problem was enjoyable, put "Enjoyable" here

Working at: **NOT WORKING** (link)

Idea:
1.
2.
3.

Tricks/Bugs:
1.
2.
3. 

Difficulty: #/10

Time started: [start] 
Time ended: [end]
*/

bool debug = true; // if(debug) cout << "debug statement" << endl;

#define ll long long
#define fst first
#define snd second
#define db(x) if(debug) cout << (#x) << ": " << x << endl; // print `x` info
#define dbp(x, y) if(debug) cout << "{" << (#x) << ", " << (#y) << "}: {" << x << ", " << y << "};\n"; // print pair `x`,`y` info
#define dba(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) cout << arr[i] << " "; cout << "\n"; } // print array info
#define cm << ", " <<
#define sp << " " <<

struct {
    template<class T>
    operator T() {
        T x; std::cin >> x; return x;
    }
} in;

const int MAX_N = 1717; // maximum value N can take
const ll MOD = 998244353; // change if necessary

ll n, k, grid[MAX_N][MAX_N];

void solve() {
    cin >> n >> k;

    for(int i = 0; i < n; i++) {
        int t; cin >> t;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int TC = 1;
    // cin >> TC;
    while(TC--) {
      solve();
    }
}
