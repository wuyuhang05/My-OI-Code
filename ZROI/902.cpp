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

const int MAXN = 2e6 + 5;
int T;
char str[MAXN];
int n;

int ch[MAXN][4],fail[MAXN],len[MAXN],tot=1,las=1;
std::vector<int> G[MAXN];
int mn[MAXN],cmn[MAXN],sz[MAXN];

inline void clear(){
    FOR(i,0,tot){
        FOR(j,0,3) ch[i][j] = 0;
        fail[i] = len[i] = 0;G[i].clear();sz[i] = 0;
    }
    FOR(i,0,2*n+3) mn[i] = cmn[i] = 1e9;
    tot = las = 1;
}

inline void copy(int x,int y){
    FOR(i,0,3) ch[x][i] = ch[y][i];
    fail[x] = fail[y];len[x] = len[y];
}

inline void insert(int c){
    int p = las,np = las = ++tot;len[np] = len[p]+1;sz[np] = 1;
    for(;p&&!ch[p][c];p=fail[p]) ch[p][c] = np;
    if(!p) fail[np] = 1;
    else{
        int q = ch[p][c];
        if(len[q] == len[p]+1) fail[np] = q;
        else{
            int nq = ++tot;copy(nq,q);
            len[nq] = len[p]+1;fail[q] = fail[np] = nq;
            for(;p&&ch[p][c]==q;p=fail[p]) ch[p][c] = nq;
        }
    }
}

inline void dfs1(int v){
    for(auto x:G[v]){
        dfs1(x);
        sz[v] += sz[x];
    }
    int ps=-1;
    for(auto x:G[v]) if(mn[v] > mn[x]){ps = x;cmn[v] = mn[v];mn[v] = mn[x];}
    for(auto x:G[v]){
        if(x == ps) continue;
        cmn[v] = std::min(cmn[v],mn[x]);
    }
}

int ansx[MAXN],ansy[MAXN];

inline void dfs2(int v){
    if(ansx[len[v]] == -1 && sz[v] >= 2){
        ansx[len[v]] = mn[v];ansy[len[v]] = cmn[v];
    }
    FOR(i,0,3){
        if(ch[v][i]) dfs2(ch[v][i]);
    }
}

inline void Solve(){
    scanf("%s",str+1);n = strlen(str+1);std::reverse(str+1,str+n+1);
    clear();
    FOR(i,1,n) insert(str[i]-'a'),mn[las] = n-i+1,cmn[las] = 1e9;//,DEBUG(las);
    FOR(i,2,tot) G[fail[i]].pb(i);//,printf("%d %d\n",fail[i],i);
    dfs1(1);
    FOR(i,1,n) ansx[i] = ansy[i] = -1;
    dfs2(1);
    FOR(i,1,n){
        if(ansx[i] != -1) printf("%d %d\n",ansx[i],ansy[i]);
        else printf("%d %d\n",n-i+1,n-i+1);
    }
}

int main(){
    scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
