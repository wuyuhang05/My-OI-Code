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

const int MAXN = 2000+5;
int n,m,x;
int col[MAXN];
std::vector<int> S;
std::vector<int> G[MAXN];
int A[MAXN];
int vis[MAXN];
int L,R,now;
std::vector<int> bl[MAXN];

inline void dfs(int v,int fa=0){
    vis[v] = now;bl[now].pb(v);
    for(auto x:G[v]){
        if(x == fa) continue;
        if(x < L || x > R) continue;
        dfs(x,v);
    }
}
int cnt[MAXN],nowans;

inline void add(int x){
    cnt[x]++;
    if(cnt[x]&1) nowans++;
    else nowans--;
}

inline void del(int x){
    cnt[x]--;
    if(cnt[x]&1) nowans++;
    else nowans--;
}

int main(){
    scanf("%d%d%d",&n,&m,&x);
    FOR(i,1,n) scanf("%d",col+i),S.pb(col[i]);
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) col[i] = std::lower_bound(all(S),col[i])-S.begin()+1;
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);G[u].pb(v);G[v].pb(u);
    }
    FOR(i,0,x) scanf("%d",A+i);
    
    while(m--){
        scanf("%d%d",&L,&R);FOR(i,L,R) vis[i] = 0;now = 0;
        int ans = 0;
        FOR(i,L,R){
            if(!vis[i]) now++,dfs(i);
        }
        FOR(i,1,now){
            for(auto x:bl[i]) add(col[x]);
            ans += A[nowans];
            for(auto x:bl[i]) del(col[x]);
        }
        FOR(i,1,now) bl[i].clear();
        printf("%d\n",ans);
    }
    return 0;
}
