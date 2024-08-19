using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

/*
Working at: https://usaco.org/index.php?page=viewproblem2&cpid=1159

Idea:
1. first find connected components. cc[0] will contain node 1, but keep track of "last" s.t. cc[last] contains node N
2. 1 road can connect two CCs. we have two options: use two roads to directly connect cc[0] and cc[last], or connect cc[0] -> cc[i] -> cc[last]
3. to calculate the minimum difference between two elements in two arrays, loop through one and binary search on the other for the closest value
4. now, the 1st case is easy - simply O(N log N) to calculate the min distance from cc[0] and cc[last]
5. second case ALSO O(N log N) - because binary searching cc[0]/cc[last] is max O(log N) and finding ALL THE CONNECTED COMPONENTS SUM TO N.


first step is easy O(N log N)

Tricks/Bugs:
1. need to CLEAR arrays if resizing them
2. GODDAMN okay so ig adding the & in vector<ll> &a make it go from TLE to 91ms. lesson learned: VERY expensive to copy arrays
3.

Difficulty: 5/10

Time started: [3:55 PM]
Time ended: [4:33 PM]
*/

bool debug = false; // if(debug) cout << "debug statement" << endl;

#define ll long long
#define fst first
#define snd second
#define db(x) if(debug) cout << (#x) << ": " << x << endl; // print `x` info
#define dbp(x, y) if(debug) cout << "{" << (#x) << ", " << (#y) << "}: {" << x << ", " << y << "};\n"; // print pair `x`,`y` info
#define dba(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) cout << arr[i] << " "; cout << "\n"; } // print array info
#define dbap(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) cout << "{" << arr[i].first << ", " << arr[i].second << "} "; cout << "\n"; } // print array of pairs
#define dbaa(arr) if(debug) { cout << (#arr) << ": \n"; for(int i = 0; i < arr.size(); i++) { for(auto t : arr[i]) cout << t << " "; cout << "\n"; } cout << "\n"; } // print 2D array
#define cm << ", " <<
#define sp << " " <<

struct {
    template<class T>
    operator T() {
        T x; std::cin >> x; return x;
    }
} in;

ll n, m;
vector<vector<ll>> adj;

vector<bool> vis;
vector<vector<ll>> cc; //connected components

int last = -1; // index of the cc that contains N

void dfs(ll u) {
    if (u == n-1) last = cc.size() - 1;
    for (ll v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            cc.back().push_back(v);
            dfs(v);
        }
    }
}

ll minDifference(vector<ll> &a, vector<ll> &b) {//<a>, <b> sorted
    // finds i,j s.t. a[i]-b[j] is minimized, returns a[i]-b[j]
    //if (a.size() < b.size()) swap(a, b); // time conservation

    ll mini = 1e12;

    for (int t : b) {
        ll cur = 1e12;

        int low = lower_bound(a.begin(), a.end(), t) - a.begin();
        if (low == 0) cur = a[low] - t;
        else if (low == a.size()) cur = t - a[low - 1];
        else cur = min(a[low]-t, t-a[low - 1]); // i.e. if <a> = {2, 4, 7} and t = 5, a[low] = 7 but the answer is 4

        if (cur < 0) cout << "ERROR: `cur` is NEGATIVE\n";
        mini = min(mini, cur);
    }

    return mini;
}

void solve() {
    cin >> n >> m;
    
    cc.clear();
    adj.clear(); adj.resize(n);
    vis.clear(); vis.resize(n, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u; u--;
        cin >> v; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // get connected components
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            cc.push_back({ i }); //~O(M)
            dfs(i);
            sort(cc.back().begin(), cc.back().end()); //O(N log N)
        }
    }

    dbaa(cc); // working
    
    db(last);

    // case 1 - directly go from start to end
    ll diff = minDifference(cc[0], cc[last]);
    ll ans = (diff / 2) * (diff / 2) + (diff - diff / 2) * (diff - diff / 2);
    
    db(ans);

    //if(n>5)throw invalid_argument("nuh uh...");

    // case 2 - use an intermediate connected component
    for (int i = 0; i < cc.size(); i++) {
        if (i == 0 || i == last) continue;

        ll distStart = minDifference(cc[0], cc[i]);
        ll distEnd = minDifference(cc[last], cc[i]);

        ans = min(ans, distStart * distStart + distEnd * distEnd);
    }
    
    db(ans);

    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int TC = 1;
    cin >> TC;
    while (TC--) {
        solve();
    }
}
