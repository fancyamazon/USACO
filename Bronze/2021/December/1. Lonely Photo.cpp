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
Working at: https://usaco.org/index.php?page=viewproblem2&cpid=1155

Idea:
1. chunk the Gs and Hs
2. casework on when it's lonely
case 1: GGGGHH....HH -> GGH, GGGH, GGGGH -> 4-1 = 3 
case 2: HH....HHGGGG -> HGG, HGGG, HGGGG -> 4-1 = 3
case 3: GGGGHGGGG -> 4x4 = 16 
3. make sure not out of bounds

Tricks/Bugs:
1. did the custom sample "1 GHHGHG" and was wondering why it wasn't working. lesson learned: copy paste in real sample first
2. needed to replace the final for() loop and its subcontents with SZ (condense.size()) instead of N (types.size())
3. <notWork += condense[i].second - 1> instead of <notWork += condense[i].second - 2> because GGH -> 1 possible, not 0
4. didn't read problem carefully enough... its how many to THROW OUT, not keep
4. make sure to make condense = {char, LL} instead of {char, INT} because i'm multiplying the .second's together

Difficulty: 2/10

Time started: [2:25 PM]
Time ended: [3:00 PM] (ugh, idea = 5 min, implement = 10-15 min, debug = 15+ min)
*/

bool debug = false; // if(debug) cout << "debug statement" << endl;

#define ll long long
#define fst first
#define snd second
#define db(x) if(debug) cout << (#x) << ": " << x << endl; // print `x` info
#define dbp(x, y) if(debug) cout << "{" << (#x) << ", " << (#y) << "}: {" << x << ", " << y << "};\n"; // print pair `x`,`y` info
#define dba(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) cout << arr[i] << " "; cout << "\n"; } // print array info
#define dbap(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) cout << "{" << arr[i].first << ", " << arr[i].second << "} "; cout << "\n"; } // print array of pairs
#define dbaa(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) { for(int &t : arr[i]) cout << t << " "; cout << "\n"; } cout << "\n"; } // print 2D array
#define cm << ", " <<
#define sp << " " <<

struct {
    template<class T>
    operator T() {
        T x; std::cin >> x; return x;
    }
} in;

/*
const int MAX_N = 1717; // maximum value N can take
const ll MOD = 998244353; // change if necessary
ll grid[MAX_N][MAX_N]; // */

ll n, k;

void solve() {
    cin >> n;

    vector<bool> types(n);
    
    string s; cin >> s;
    char norm = s[0];
    for (int i = 0; i < n; i++) types[i] = s[i] == norm;

    if (debug) {
        cout << "types: \n";
        for (auto p : types) cout << p << " ";
    }

    vector<pair<bool, ll>> condense;
    condense.push_back({ true, 1 }); // first one is guarenteed true
    for (int i = 1; i < n; i++) {
        if (condense.back().first == types[i]) condense[condense.size()-1].second++;
        else condense.push_back({ types[i], 1 });
    }

    if (debug) {
        cout << "condensed: \n";
        for (auto p : condense) dbp(p.first, p.second);
    }

    ll notWork = 0;

    int sz = condense.size();
    for (int i = 0; i < sz; i++) { // "left-most" chunk
        if (i < sz - 2 && condense[i + 1].second == 1) { // if GGGG H GGGG, then 16 combos
            notWork += condense[i].second * condense[i + 2].second;
        }

        if (condense[i].second == 1) continue;

        if(i != sz-1) notWork += condense[i].second - 1; // for the next one
        if(i != 0) notWork += condense[i].second - 1; // for the previous one
    }

    cout << notWork << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC = 1;
    // cin >> TC;
    while (TC--) {
        solve();
    }
}
