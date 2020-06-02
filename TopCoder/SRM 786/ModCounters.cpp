#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
//#define P stdd::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
// f[i][j] i 时刻 期望多少个=j 的数字
// f[i][j] = f[i-1][j] + f[i-1][j-1]/n - f[i-1][j]/n
const int ha = 1000000007;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}
int A[2000005];
int a[512],b[512],res[512],t[512];
class ModCounters {
    std::vector<int> S;
    inline void mul(int c[],int a[],int b[]){
        FOR(i,0,511){
            FOR(j,0,511){
                (c[(i+j)%512] += 1ll*a[i]*b[j]%ha)%=ha;
            }
        }
    }

    public:
    int findExpectedSum(std::vector<int> P, int A0, int X, int Y, int N, int K) {
        A[0] = A0;FOR(i,1,N-1) A[i] = (1ll*A[i-1]*X%1812447359+Y)%1812447359;
        S = P;S.resize(N);FOR(i,P.size(),N-1) S[i] = A[i]%512;
        FOR(i,0,N-1) b[S[i]]++;
        a[0] = 1ll*(N-1)*qpow(N)%ha;a[511] = qpow(N);res[0] = 1;
        while(K){
            if(K & 1){
                mul(t,res,a);
                FOR(i,0,511) res[i] = t[i],t[i] = 0;
            }
            mul(t,a,a);FOR(i,0,511) a[i] = t[i],t[i] = 0;
            K >>= 1;
        }
        LL ans = 0;
        FOR(i,0,511){
            LL t = 0;
            FOR(k,0,511){
                (t += 1ll*res[(k-i+512)%512]*b[k]%ha)%=ha;
            }
            (ans += 1ll*t*i%ha)%=ha;
        }
        return ans;
    }
};

// CUT begin
using namespace std;
ifstream data("ModCounters.sample");

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

bool do_test(vector<int> P, int A0, int X, int Y, int N, int K, int __expected) {
    time_t startClock = clock();
    ModCounters *instance = new ModCounters();
    int __result = instance->findExpectedSum(P, A0, X, Y, N, K);
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
        vector<int> P;
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
        int __answer;
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
        int T = time(NULL) - 1589586473;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ModCounters (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
