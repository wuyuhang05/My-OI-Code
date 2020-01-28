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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;

int f[MAXN],sz[MAXN];
std::stack<P> opt;

inline int find(int x){
    return x == f[x] ? x : find(f[x]);
}

inline bool Union(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return false;
    if(sz[fx] < sz[fy]) std::swap(fx,fy);
    f[fy] = fx;sz[fx] += sz[fy];
    opt.push(MP(fy,fx));
    return true;
}

inline void undo(){
    P t = opt.top();opt.pop();
    f[t.fi] = t.fi;sz[t.se] -= sz[t.fi];
}

int n,m;
std::map<P,int> S;
int qx[MAXN],qy[MAXN],ans[MAXN];

#define lc ((x)<<1)
#define rc ((x)<<1|1)
std::vector<P> sm[MAXN<<2];

inline void modify(int x,int l,int r,int L,int R,P d){
    if(l == L && r == R){
        sm[x].pb(d);
        return;
    }
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R,d);
    else if(L > mid) modify(rc,mid+1,r,L,R,d);
    else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
}

inline void dfs(int x,int l,int r){
    int cnt = 0;
    FOR(i,0,(int)sm[x].size()-1) cnt += Union(sm[x][i].fi,sm[x][i].se);
    if(l == r){
        if(qx[l]){
            // DEBUG(qx[l]);DEBUG(qy[l]);
            int fx = find(qx[l]),fy = find(qy[l]);
            ans[l] = fx == fy;
        }
        while(cnt--) undo();
        return;
    }
    int mid = (l + r) >> 1;
    dfs(lc,l,mid);dfs(rc,mid+1,r);
    while(cnt--) undo();
}

char str[MAXN];

int main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n*2) f[i] = i,sz[i] = 1;
    int i = 1;m = 1e5;
    while(~scanf("%s",str)){
        if(str[0] == 'E') break;
        int opt = (str[0] == 'O' ? 0 : (str[0] == 'C' ? 1 : 2));
        int x,c1,y,c2;scanf("%d%d%d%d",&c1,&x,&c2,&y);
        c1--;c2--;
        if(c1) x += n;if(c2) y += n;
        // DEBUG(x);DEBUG(y);
        if(x > y) std::swap(x,y);
        if(opt == 0){
            S[MP(x,y)] = i;
        }
        if(opt == 1){
            int t = S[MP(x,y)];
            modify(1,1,m,t,i,MP(x,y));
            S.erase(MP(x,y));
        }
        if(opt == 2){
            qx[i] = x;qy[i] = y;
        }
        ++i;
    }
    for(std::map<P,int>::iterator it = S.begin();it != S.end();++it) modify(1,1,m,it->se,m,it->fi);
    dfs(1,1,m);
    FOR(i,1,m) if(qx[i]) puts(ans[i] ? "Y" : "N");
    return 0;
}