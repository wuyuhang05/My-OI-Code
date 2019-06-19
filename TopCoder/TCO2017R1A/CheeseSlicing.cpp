// BEGIN CUT HERE

// END CUT HERE
#line 5 "problem.cpp"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100+5;

class CheeseSlicing{
public:
    int f[MAXN][MAXN][MAXN];

    inline void upd(int &a,int b){
        if(a < b) a = b;
    }
public:
    int totalArea(int A, int B, int C, int S){
        int ans = 0;
        FOR(i,S,A){
            FOR(j,S,B){
                FOR(k,S,C){
                    std::vector<int> dim;dim.pb(i);dim.pb(j);dim.pb(k);
                    std::sort(all(dim));
                    f[i][j][k] = std::max(f[i][j][k],dim[1]*dim[2]);
                    ans = std::max(ans,f[i][j][k]);
                    for(int x = S;x < 2*S && x <= std::min(j,k) && i+x <= A;x++){
                        upd(f[i+x][j][k],f[i][j][k]+j*k);
                    }
                    for(int x = S;x < 2*S && x <= std::min(i,k) && j+x <= B;x++){
                        upd(f[i][j+x][k],f[i][j][k]+i*k);
                    }
                    for(int x = S;x < 2*S && x <= std::min(i,j) && k+x <= C;x++){
                        upd(f[i][j][k+x],f[i][j][k]+i*j);
                    }
                }
            }
        }
        return ans;
	}
};

// BEGIN CUT HERE
// test
int main(void){
	CheeseSlicing test;
	DEBUG(test.totalArea(5,5,5,2));
	return 0;
}
// test end
// END CUT HERE

