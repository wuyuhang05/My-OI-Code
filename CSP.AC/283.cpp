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

const int MAXN = 2e6 + 5;
int n,k;
//std::map<int,int> ch[MAXN];
std::vector<P> ch[MAXN];
//std::vector<int> ch[MAXN];
int dep[MAXN];
char str[100000+5];
int rt = 1,tot = 1;
int sm[MAXN];

inline int find(int v,int y){
    for(auto x:ch[v]) if(x.fi == y) return x.se;
    return 0;
}

inline void insert(char str[]){
    int len = strlen(str+1),v = rt;
    FOR(i,1,len){
        int o = str[i]-'a';
        int t = find(v,o);
        if(!t) ch[v].pb(MP(o,++tot)),dep[tot] = dep[v]+1,t = tot;
        v = t;
    }
    sm[v]++;
}

LL ans = 0;

inline void dfs(int v){
    for(auto x:ch[v]){
        dfs(x.se);
        sm[v] += sm[x.se];
    }
    ans += dep[v]*(sm[v]/k);
    sm[v] %= k;
}

int main(){
//    freopen("C.in","r",stdin);
//    freopen("C.out","w",stdout);
    scanf("%d%d",&n,&k);
    FOR(i,1,n){
        scanf("%s",str+1);insert(str);
    }
    dfs(1);
    printf("%lld\n",ans);
    return 0;
}