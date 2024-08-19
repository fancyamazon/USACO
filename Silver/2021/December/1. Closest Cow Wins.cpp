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
Working at: https://usaco.org/index.php?page=viewproblem2&cpid=1158

Idea
the implementation is VERY long. to make it more clear, each step in the inspiration <-> a phase in the implementation
1. first, for each patch of grass, assign a "bound" to it. that is the shortest distance from it to a evil(farmer Nhoj)'s cow. WE MUST PLACE A COW AT A DISTANCE SHORTER than that bound to obtain it
2. notice that grass and cows can be like 1s and 0s... for example, 1 1 1 0 0 1 0 1 0 1 1. CONDENSE it into "clumps". 
3. notice that for each clump, we can guarantee that we can get it in two cows (make sure see why). if we ONLY use one cow, then notice that we can take either a PREFIX of the clump or SUFFIX. the condition is that we can take from i to j if the distance from grass[j] to grass[i] is less than the sum of the bounds (see why) 
4. finally, we use a priority_queue to take the first n most valuable clumps of grass. we can only use 2 cows on a clump after using 1. ordered sets would also work here

Tricks/Bugs:
1. BRUH i copy pasted the code from problem 2. of dec. should've thought about it more - ALWAYS TRY TO MAKE CODE EFFICIENT
    - okay. i take back everything. copy pasting it was good. 
2. the implementation is MUCH, MUCH more tedious than thinking up the process. there are 3 complex parts of it, TONS of wacky vectror<pair<ll,paor<>>> etc stuff
3. BUT it worked first submission !!! finally good bug testing

Difficulty: 6.5/10

Time started: [6:05 PM]
Time ended: [7:44 PM]

took a 10 minute break in between, driving from starbucks -> home

took another 10-15 minute between for amy's math 
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

ll k, m, n;

vector<ll> bounds;

void getBounds(vector<pair<ll, ll>>& grass, vector<ll>& evil) {//<a>, <b> sorted
    // for each grass, find the closest evil cow

    for (int i = 0; i < k; i++) {
        ll cur = 1e12;

        ll t = grass[i].fst;
        int low = lower_bound(evil.begin(), evil.end(), t) - evil.begin();
        if (low == 0) cur = evil[low] - t;
        else if (low == evil.size()) cur = t - evil[low - 1];
        else cur = min(evil[low] - t, t - evil[low - 1]); // i.e. if <evil> = {2, 4, 7} and t = 5, evil[low] = 7 but the closest evil cow is cow @ 4

        if (cur < 0) cout << "ERROR: `cur` is NEGATIVE\n";

        bounds[i] = cur;
    }
}

void solve() {
    cin >> k >> m >> n;

    vector<pair<ll, ll>> grass(k); // {grass position, taste of grass }
    vector<ll> evil(m);

    for (pair<ll, ll>& t : grass) cin >> t.first >> t.second;
    sort(grass.begin(), grass.end());

    for (ll& t : evil) cin >> t;
    sort(evil.begin(), evil.end());

    // get bounds
    bounds.resize(k);
    getBounds(grass, evil);

    // "clump" the grass 
    vector<vector<pair<int, ll>>> clumps; // vector of {<grass> idx, bound} 

    int gr = 0;// grass index
    int ev = 0; // evil index
    bool lastSeen = 0; // did we last see grass or evil cow. true = grass, false = evil

    while (gr < k) {
        if (ev >= m) {
            // add the rest of the cows to the clump
            if (!lastSeen) {
                clumps.push_back({ { gr, bounds[gr] } });
                gr++;
            }
            while (gr < k) {
                clumps.back().push_back({ gr, bounds[gr] });
                gr++;
            }
            break;
        }
        if (grass[gr].fst == evil[ev]) {
            gr++; ev++; // literally ignore this piece of stupid grass anyway
        }
        else if(grass[gr].fst > evil[ev]) {
            // process ev cow
            lastSeen = false; ev++;
        }
        else {
            // process gr grass
            if(lastSeen) clumps.back().push_back({ gr, bounds[gr] });
            else {
                clumps.push_back({ { gr, bounds[gr] } });
                lastSeen = true;
            }
            gr++;
        }

    }

    if (debug) {
        cout << "clump info:\n";
        for (auto arr : clumps) {
            dbap(arr);
        }
        cout << "\n";
    }

    // for each "clump" of grass, find the values if we place 1 cow or place 2
    priority_queue<pair<ll, pair<int, int>>> pq; // {value, {isFirst, idx} } tie break with TAKING FIRST before a SECOND - that opens up oppurtunities

    vector<ll> takeSecond(clumps.size()); // value of placing a second cow on it

    for (int i = 0; i < clumps.size(); i++) {
        vector<pair<int, ll>>& clump = clumps[i];
        ll one = 0; // taking one
        
        //LEFT->RIGHT
        ll left = 0;
        int j = 0;
        while (j < clump.size() && grass[clump[j].fst].fst - grass[clump[0].fst].fst < clump[j].snd + clump[0].snd) {
            left += grass[clump[j].fst].snd;
            j++;
        }

        //RIGHT->LEFT
        ll right = 0;
        j = clump.size() - 1;
        while (j >= 0 && grass[clump[clump.size() - 1].fst].fst - grass[clump[j].fst].fst < clump[j].snd + clump[clump.size() - 1].snd) {
            right += grass[clump[j].fst].snd;
            j--;
        }

        one = max(left, right);

        ll total = 0;
        for (auto &nxt : clump) total += grass[nxt.fst].snd;

        takeSecond[i] = total - one;
        pq.push({ one, {1, i} }); // only insert where you take one
    }


    // take the first n rewards. can only take second once taken first
    ll ans = 0;

    while (!pq.empty() && n > 0) {
        auto cur = pq.top(); pq.pop();
        ll val = cur.fst;
        int isFirst = cur.snd.fst; 
        int idx = cur.snd.snd;

        ans += val;
        n--;

        if (isFirst) pq.push({ takeSecond[idx], {0, idx} });
    }

    cout << ans << endl;
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
