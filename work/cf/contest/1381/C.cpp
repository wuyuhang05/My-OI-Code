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
#define db double
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
int n,x,y;
int a[MAXN];
std::vector<int> G[MAXN];
int ans[MAXN];
std::map<int,int> T;

inline int get(int x){
    auto p = T.find(x);
    if(p == T.end()){
        if(T.empty()) return -1;
        int res = (*T.begin()).fi;
        T[res]--;if(!T[res]) T.erase(res);
        return res;
    }
    if(p != T.begin()){
        --p;int res = (*p).fi;
        T[res]--;if(!T[res]) T.erase(res);
        return res;
    }
    p++;
    if(p != T.end()){
        int res = (*p).fi;
        T[res]--;if(!T[res]) T.erase(res);
        return res;
    }
    return -1;
}

inline void Solve(){
    scanf("%d%d%d",&n,&x,&y);std::vector<P> S;
    T.clear();FOR(i,1,n+1) ans[i] = 0;
    FOR(i,0,n+1) G[i].clear();
    FOR(i,1,n) scanf("%d",a+i),G[a[i]].pb(i);
    FOR(i,1,n+1) S.pb(MP(G[i].size(),i));
    int ext=-1;
    FOR(i,1,n+1) if(G[i].empty()){ext = i;break;}
    std::sort(all(S));std::reverse(all(S));
    int now = x;y -= x;int ps = 0;
    while(now){
        if(now > S[ps].fi){
            now -= S[ps].fi;
            for(auto x:G[S[ps].se]){
                ans[x] = S[ps].se;
            }
            G[ps].clear();
        }
        else{
            while(now--) ans[G[S[ps].se].back()] = S[ps].se,G[S[ps].se].pop_back();
            if(G[S[ps].se].empty()) ps++;
            break;
        }
        ps++;
    }
    S.clear();
    FOR(i,1,n+1) if(!G[i].empty()) T[i] = G[i].size();
    FOR(i,1,n){
        if(ans[i]) continue;
        if(!y) break;
        int t = get(a[i]);y--;
        if(t == -1){
            puts("NO");
            return;
        }
        ans[i] = t;
    }
    FOR(i,1,n) if(!ans[i]) ans[i] = ext;
    puts("YES");
    FOR(i,1,n) printf("%d ",ans[i]);puts("");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
