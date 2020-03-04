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

const int MAXN = 1e6 + 5;

struct SAM{
    int ch[MAXN][26],fail[MAXN],len[MAXN],dfn[MAXN];
    int tot = 1,las = 1,ts = 0;
    int ps[MAXN],sz[MAXN];std::vector<int> G[MAXN];

    inline int work(int p,int c){
        int q = ch[p][c],nq = ++tot;
        FOR(i,0,25) ch[nq][i] = ch[q][i];fail[nq] = fail[q];len[nq] = len[p]+1;
        fail[q] = nq;
        while(p&&ch[p][c] == q) ch[p][c] = nq,p = fail[p];
        return nq;
    }

    inline int insert(int c){
        int p = las,np = las = ++tot;len[np] = len[p]+1;
        while(p && !ch[p][c]) ch[p][c] = np,p = fail[p];
        if(!p) fail[np] = 1;
        else{
            if(len[ch[p][c]] == len[p]+1) fail[np] = ch[p][c];
            else fail[np] = work(p,c);
        }
        return np;
    }

    inline void dfs(int v){
        dfn[v] = ++ts;sz[v] = 1;
        for(auto x:G[v]){
            dfs(x);sz[v] += sz[x];
        }
    }

    inline void build(){
        FOR(i,2,tot) G[fail[i]].pb(i);
        dfs(1);
    }
}pre,suf;

char str[MAXN];
int n;
std::vector<int> S;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void add(int pos,int x){
        pos++;
        for(;pos < MAXN;pos += lowbit(pos)) tree[pos] += x;
    }

    inline int query(int pos){
        int res = 0;pos++;
        for(;pos;pos -= lowbit(pos)) res += tree[pos];
        return res;
    }
}bit;
int ans[MAXN];
struct Node{
    int x,y,opt,id,d;

    Node(int x=0,int y=0,int opt=0,int id=0,int d=0) : x(x),y(y),opt(opt),id(id),d(d) {}

    bool operator < (const Node &t) const {
        return x == t.x ? opt < t.opt : x < t.x;
    }
}A[MAXN];
int N;
int pr[MAXN],sf[MAXN];

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,1,n){
        pre.ps[i] = pre.insert(str[i]-'a');
        suf.ps[n-i+1] = suf.insert(str[n-i+1]-'a');
    }
    pre.build();suf.build();
    FOR(i,1,n-1) A[++N] = Node(pre.dfn[pre.ps[i]],suf.dfn[suf.ps[i+1]],1,0,1);
    int fullpre = pre.dfn[pre.ps[n]];
    int q;scanf("%d",&q);
    FOR(id,1,q){
        scanf("%s",str+1);int m = strlen(str+1);
        FOR(i,0,m+1) pr[i] = sf[i] = 0;pr[0] = sf[m+1] = 1;
        FOR(i,1,m){
            pr[i] = pre.ch[pr[i-1]][str[i]-'a'];
            if(!pr[i]) break;
        }
        ROF(i,m,1){
            sf[i] = suf.ch[sf[i+1]][str[i]-'a'];
            if(!sf[i]) break;
        }
        // FOR(i,1,m) printf("%d ",pr[i]);puts("");
        // FOR(i,1,m) printf("%d ",sf[i]);puts("");
        FOR(i,1,m){
            FOR(j,0,25){
                if(j == str[i]-'a') continue;
                int now = pre.ch[pr[i-1]][j];if(!now) continue;
                int won = sf[i+1];if(!won) continue;//DEBUG(won);
                int l1 = pre.dfn[now],r1 = pre.dfn[now]+pre.sz[now]-1;
                int l2 = suf.dfn[won],r2 = suf.dfn[won]+suf.sz[won]-1;
                // printf("%d %d %d %d\n",l1,r1,l2,r2);DEBUG(fullpre);
                if(l1 <= fullpre && fullpre <= r1 && i == m) ans[id]++;
                A[++N] = Node(r1,r2,2,id,1);A[++N] = Node(r1,l2-1,2,id,-1);
                A[++N] = Node(l1-1,r2,2,id,-1);A[++N] = Node(l1-1,l2-1,2,id,1);
            }
        }
    }
    std::sort(A+1,A+N+1);
    FOR(i,1,N){
        if(A[i].opt == 1){
            bit.add(A[i].y,1);
        }
        else{
            ans[A[i].id] += A[i].d*bit.query(A[i].y);
        }
    }
    FOR(i,1,q) printf("%d\n",ans[i]);
    return 0;
}