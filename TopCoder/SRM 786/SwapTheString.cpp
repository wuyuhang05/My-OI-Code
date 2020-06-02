#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
const int MAXM = 233;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXM];

    inline void add(int pos,int x){
        while(pos < MAXM){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

class SwapTheString {
    int A[MAXN];
    int f[MAXN][26];
    std::string str;
    public:
    long long findNumberOfSwaps(std::string P, int A0, int X, int Y, int N, int K) {
        A[0] = A0;
        FOR(i,1,N-1) A[i] = (1ll*A[i-1]*X+Y)%1812447359;
        str = P;str.resize(N);
        FOR(i,P.length(),N-1) str[i] = (char)(A[i]%26+'a');
        if(K >= N) return 0;
        LL ans = 0;
        FOR(i,0,K-1){
            CLR(bit.tree,0);
            for(int t=0,j = i;j < N;j += K,++t){
                ans += bit.query(str[j]-1);
                bit.add(str[j],1);
            }
        }
        return ans;
    }
};

// CUT begin
using namespace std;
ifstream data("SwapTheString.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string P, int A0, int X, int Y, int N, int K, long long __expected) {
    time_t startClock = clock();
    SwapTheString *instance = new SwapTheString();
    long long __result = instance->findNumberOfSwaps(P, A0, X, Y, N, K);
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
        string P;
        from_stream(P);
        int A0;
        from_stream(A0);
        int X;
        from_stream(X);
        int Y;
        from_stream(Y);
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(P, A0, X, Y, N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1589584440;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SwapTheString (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
