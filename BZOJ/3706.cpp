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

const int MAXN = 1e6 + 5;
int n,m;
struct Edge{
    int u,v,c,id;
}e[MAXN];
int f[MAXN];
inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge(int x,int y){
    x = find(x);y = find(y);
    if(x == y) return;
    f[x] = y;
}
int cnt[MAXN],du[MAXN];
int ct2[2],ans;
int main(){
    scanf("%d%d",&n,&m);FOR(i,1,n) f[i] = i;ct2[0] = n;
    FOR(i,1,m){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
        int u = e[i].u,v = e[i].v;
        merge(u,v);
        if(e[i].c == 1){
            ct2[du[u]&1]--;du[u]++;ct2[du[u]&1]++;
            ct2[du[v]&1]--;du[v]++;ct2[du[v]&1]++;
        }
    }
    FOR(i,1,m) e[i].id = find(e[i].u);
    FOR(i,1,m){
        if(e[i].c == 1){
            if(!cnt[e[i].id]) ans++;
            cnt[e[i].id]++;
        }
    }
    int q;scanf("%d",&q);
    FOR(i,1,q){
        int opt;scanf("%d",&opt);
        if(opt == 1){
            int x;scanf("%d",&x);++x;int u = e[x].u,v = e[x].v;
            if(e[x].c == 0){
                ct2[du[u]&1]--;du[u]++;ct2[du[u]&1]++;
                ct2[du[v]&1]--;du[v]++;ct2[du[v]&1]++;
                if(!cnt[e[x].id]) ans++;cnt[e[x].id]++;
            }
            else{
                ct2[du[u]&1]--;du[u]--;ct2[du[u]&1]++;
                ct2[du[v]&1]--;du[v]--;ct2[du[v]&1]++;
                if(cnt[e[x].id] == 1) ans--;cnt[e[x].id]--;
            }
            e[x].c ^= 1;
        }
        if(opt == 2){
            printf("%d\n",ct2[1]?-1:ans);
        }
    }
    return 0;
}
