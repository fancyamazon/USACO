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
lowered prev time of 336 ms to 66 ms 

Working at: https://usaco.org/index.php?page=viewproblem2&cpid=1160

Idea:
1. when taking a pair of indices i,j, use a DIFFERENCE ARRAY to update a range of values (we only have to recreate it once)
2. what this looks like: (i,j) -> diff[ai + aj]++, diff[bi + bj + 1]--
3. since ai + aj and bi + bj occur completely separately, SEPARATE THEM
4. since M is small enough, we place all ai and bi into buckets (at most M+1) and iterate through each pair
5. keep track of a few more things: (i,j)=(j,i) so double when i != j; <diff>.size needs to be 2m+2 to avoid arr out of bounds

Tricks/Bugs:
1. when doing difference arrays, make sure to do idx+1 when removing... for example the range [3,9] has diff[3]++ and diff[10]--
2. otherwise first try after getting sample right

Difficulty: 4/10

Time started: [3:04 PM]
Time ended: [3:47 PM]
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

ll n, m;

void solve() {
    cin >> n >> m;

    vector<ll> st(m + 1); 
    vector<ll> en(m + 1); 
    for (int i = 0; i < n; i++) {
        ll a, b; 
        cin >> a >> b;
        st[a]++;
        en[b]++;
    }
    
    dba(st);
    dba(en);

    vector<ll> diff(2*m + 2);//diff[2m+1] is to avoid out-of-bounds
    for (int i = 0; i <= m; i++) { // O(M^2) is fast enough
        // intra-group (only count once)
        if (st[i]) diff[2*i] += st[i] * st[i];
        if (en[i]) diff[2*i+1] -= en[i] * en[i];

        // inter-group (count twice)
        for (int j = i+1; j <= m; j++) {
            if (st[i] && st[j]) diff[i+j] += 2 * st[i] * st[j];
            if (en[i] && en[j]) diff[i+j+1] -= 2 * en[i] * en[j];
        }
    }

    dba(diff);

    // recreate the real array
    ll cur = 0;
    for (int i = 0; i <= 2 * m; i++) {
        cur += diff[i];
        cout << cur << "\n"; 
    }
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
