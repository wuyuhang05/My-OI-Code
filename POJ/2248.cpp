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

int n,len;
int t[MAXN];
bool x[MAXN];

inline bool dfs(int step){
    if(step > len){
        return t[len] == n;
    }
    //if(found) return;
    CLR(x,0);
    ROF(i,step-1,1){
        ROF(j,step-1,1){
            if(t[i]+t[j] <= t[step-1]) break;
            if(t[i]+t[j] > n || x[t[i]+t[j]]) continue;
            t[step] = t[i]+t[j];x[t[i]+t[j]] = true;
            if(dfs(step+1)) return true;
        }
    }
    return false;
}

inline void Solve(){
    if(n == 1){
        puts("1");return;
    }
    FOR(i,2,n){
        len = i;//CLR(t,0);
        CLR(x,0);
        t[1] = 1;
        if(dfs(2)){
            FOR(i,1,len)printf("%d%c",t[i],(i == len) ? '\n' : ' ');
            return;
        }
    }
    //FOR(i,0,(int)ans.size()-1) printf("%d ",ans[i]);puts("");
}

int main(){
    while(~scanf("%d",&n) && n) Solve();
    return 0;
}
