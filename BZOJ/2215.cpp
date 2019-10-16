/*
 * Author: RainAir
 * Time: 2019-10-12 15:31:03
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

const int MAXN = 5000+5;
const int MAXM = MAXN*MAXN+3;

inline char nc(){
    #define SIZE 300000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    char ch = nc();x = 0;int flag = 0;
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

struct Edge{
    int to,nxt;
}e[MAXM<<1];
int head[MAXN<<1],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

bool mp[MAXN][MAXN];
int n,m;
int dfn[MAXN<<1],low[MAXN<<1];
int col[MAXN<<1];bool ins[MAXN<<1];
int st[MAXN<<1],tp,tot;

inline void dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;st[++tp] = v;ins[v] = true;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = st[tp--];
            col[t] = tot;
            ins[t] = false;
        }while(t != v);
    }
}

// 0:tuan 1:duliji
int type[MAXN];
int cntt[MAXN],ps[MAXN];

int main(){
    read(n);
    FOR(i,1,n){
        int k;read(k);
        FOR(j,1,k){
            int x;read(x);
            mp[i][x] = mp[x][i] = 1;
        }
    }
    FOR(i,1,n){
        FOR(j,i+1,n){
            if(mp[i][j]){
                add(i+n,j);add(j+n,i);
            }
            else{
                add(i,j+n);add(j,i+n);
            }
        }
    }
    FOR(i,1,2*n) if(!dfn[i]) dfs(i);
    FOR(i,1,n) if(col[i] == col[n+i]){
        puts("0");
        return 0;
    }
    // num[i+n] > num[i]
    FOR(i,1,n) type[i] = col[i+n] < col[i];
//    FOR(i,1,n) DEBUG(type[i]);
    // 0:tuan 1:duliji
    FOR(i,1,n){
        FOR(j,1,n){
            if(i == j) continue;
            if((type[i]&&!mp[i][j]&&!type[j]) || (!type[i]&&mp[i][j]&&type[j])){
                cntt[i]++;ps[i] = j;
            }
        }
    }
    int num[2] = {0};
    FOR(i,1,n) ++num[type[i]];
    int ans = num[0]&&num[1];
//    FOR(i,1,n) DEBUG(cntt[i]);
    FOR(i,1,n) if(!cntt[i]) ans += num[type[i]] != 1;
    FOR(i,1,n){
        FOR(j,1,i){
            if(type[i]^type[j]){
                if((!cntt[i] || (cntt[i] == 1 && ps[i] == j)) && (!cntt[j] || (cntt[j] == 1 && ps[j] == i))) ans++;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
