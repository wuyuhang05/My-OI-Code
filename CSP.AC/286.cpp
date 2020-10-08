#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

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

const int MAXN = 1e6 + 5;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

bool p[MAXN];
int prime[MAXN],tot,d[MAXN];

inline void prework(){
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++tot] = i,d[i] = i;
        for(int j = 1;j <= tot && 1ll*i*prime[j] < MAXN;++j){
            p[i*prime[j]] = 1;d[i*prime[j]] = prime[j];
            if(!(i%prime[j])){
                d[i*prime[j]] = d[i];
                break;
            }
        }
    }
}

int a[MAXN],n,m,cnt[MAXN];
std::vector<int> dec[MAXN];
int pp[MAXN],ee[MAXN],sz;

inline void dfs(int dep,int id,int sm=1){
    if(dep == sz+1){
        dec[id].pb(sm);
        return;
    }
    dfs(dep+1,id,sm);
    FOR(i,1,ee[dep]) sm *= pp[dep],dfs(dep+1,id,sm);
}

inline void fj(int i){
    if(i == 1){
        dec[1].pb(1);
        return;
    }
    int x = i,las = d[x];x /= d[x];
    sz = 0;int cnt = 1;
    while(x != 1){
        if(las != d[x]){
            ++sz;
            pp[sz] = las;
            ee[sz] = cnt;
            las = d[x];cnt = 0;
        }
        x /= d[x];cnt++;
    }
    ++sz;pp[sz] = las;ee[sz] = cnt;
    dfs(1,i);
}

std::vector<int> G[MAXN];

int main(){
    prework();read(n);
    FOR(i,1,n) read(a[i]),++cnt[a[i]];
    ROF(i,MAXN-1,1){
        if(cnt[i]){
            fj(i);
            for(auto x:dec[i]) G[x].pb(i);
        }
    }
    read(m);std::vector<int> ans;
    FOR(i,1,m){
        int x;read(x);
        while(!G[x].empty() && !cnt[G[x].back()]) G[x].pop_back();
        if(G[x].empty()) break;
        int v = G[x].back();
        ans.pb(v);cnt[v]--;
    }
    printf("%d\n",(int)ans.size());
    for(auto x:ans) printf("%d ",x);puts("");
    return 0;
}