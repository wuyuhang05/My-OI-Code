#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

class TwoDistance {
    struct Data_Structure{
        std::multiset<int> S1,S2;
        inline void clear(){
            S1.clear();S2.clear();
        }
    
        inline void insert(int x){
            auto p = S1.insert(x);
            auto pre = p,suf = p;--pre;++suf;
            if(p != S1.begin()) S2.insert(x-*pre);
            if(suf != S1.end()) S2.insert(*suf-x);
            if(p != S1.begin() && suf != S1.end()) S2.erase(S2.find(*suf-*pre));
        }

        inline void del(int x){
            auto p = S1.find(x);
            auto pre = p,suf = p;--pre;++suf;
            if(p != S1.begin()) S2.erase(S2.find(x-*pre));
            if(suf != S1.end()) S2.erase(S2.find(*suf-x));
            if(p != S1.begin() && suf != S1.end()) S2.insert(*suf-*pre);
            S1.erase(p);
        }
    
        inline int query(){
            if(S2.empty()) return 0;
            return *S2.begin();
        }
    }DS;

    struct Edge{
        int to,nxt;
    }e[MAXN<<1];
    int head[MAXN],cnt;

    inline void add(int u,int v){
        e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
    }

    int A[MAXN<<1];LL ans;
    std::vector<int> V,E;
    int f[MAXN];
    std::vector<int> son[MAXN],sson[MAXN];

    inline void pdfs(int v,int fa=0){
        f[v] = fa;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            pdfs(e[i].to,v);
        }
    }

    inline void dfs(int v,int fa=0){
        DS.clear();
        if(fa) DS.insert(V[fa-1]);
        for(auto x:son[v]) DS.insert(V[x-1]);
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            DS.del(V[e[i].to-1]);
            for(auto x:sson[e[i].to]) DS.insert(V[x-1]);
            ans += DS.query();
            DS.insert(V[e[i].to-1]);
            for(auto x:sson[e[i].to]) DS.del(V[x-1]);
        }
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            dfs(e[i].to,v);
        }
    }

    public:
    long long findMinValue(int N, std::vector<int> edge, std::vector<int> val, int D, int seed) {
        cnt = 0;FOR(i,1,N) head[i] = 0;cnt = 0;
        A[0] = seed;FOR(i,1,2*N-1)  A[i] = (LL)(A[i-1] * 1103515245ll + 12345) % 2147483648;
        V = val;V.resize(N);FOR(i,val.size(),N-1) V[i] = A[i];
        E = edge;E.resize(N);FOR(i,edge.size(),N-1) E[i] = A[N+i]%std::min(i,D);
        FOR(i,1,N-1) add(i+1,E[i]+1);ans = 0;
        pdfs(1);
        FOR(i,1,N){
            if(f[i]) son[f[i]].pb(i);
            if(f[f[i]]) sson[f[f[i]]].pb(i);
        }
        dfs(1);DS.clear();
        for(auto x:sson[1]) DS.insert(V[x-1]);
        ans += DS.query();
        return ans;
    }
};

// CUT begin
using namespace std;
ifstream data("TwoDistance.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, vector<int> edge, vector<int> val, int D, int seed, long long __expected) {
    time_t startClock = clock();
    TwoDistance *instance = new TwoDistance();
    long long __result = instance->findMinValue(N, edge, val, D, seed);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int N;
        from_stream(N);
        vector<int> edge;
        from_stream(edge);
        vector<int> val;
        from_stream(val);
        int D;
        from_stream(D);
        int seed;
        from_stream(seed);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, edge, val, D, seed, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1589595987;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "TwoDistance (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
