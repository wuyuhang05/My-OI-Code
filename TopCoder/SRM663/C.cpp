/*
 * Author: RainAir
 * Time: 2019-10-08 14:35:20
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 16+1;
#define int LL
class CheeseRolling{
public:
    LL n;
    LL f[MAXN][(1<<MAXN)+3];
    LL pc[(1<<MAXN)+3];
    LL G[MAXN][MAXN];
    std::vector<LL> ans;
    inline LL DP(int i,int S){
        int &ans = f[i][S];
        if(ans != -1) return ans;
        if(pc[S] == 2){
            FOR(x,0,n-1){
                if((1<<x)&S && G[i][x]) return ans = 2; // 有序
            }
            return ans = 0;
        }
        ans = 0;
        int sz = (pc[S]-2)>>1;
        FOR(j,0,n-1){
            if((1<<j)&S && G[i][j]){ // G[i][i] = 0
                int res = (S^(1<<i))^(1<<j);
                for(int T = res;T;T = (T-1)&res){
                    if(pc[T] == sz)
                        ans += 2*DP(i,T|(1<<i))*DP(j,(res^T)|(1<<j));
                }
            }
        }
        return ans;
    }

    inline std::vector<LL> waysToWin(std::vector<std::string> wins){
        n = wins.size();
        FOR(i,1,(1<<MAXN)) pc[i] = pc[i>>1]+(i&1);
        FOR(i,0,n-1){
            FOR(j,0,n-1){
                G[i][j] = wins[i][j] == 'Y';
            }
        }
        CLR(f,-1);
        FOR(i,0,n-1) f[i][(1<<i)] = 1;
        FOR(i,0,n-1) ans.pb(DP(i,(1<<n)-1));
        return ans;
    }
}test;
#undef int

int main(){
    int n;scanf("%d",&n);
    std::vector<std::string> a;
    FOR(i,1,n){
        std::string str;std::cin >> str;
        a.pb(str);
    }
    std::vector<LL> res = test.waysToWin(a);
    for(auto x:res) printf("%lld ",x);puts("");
    return 0;
}
