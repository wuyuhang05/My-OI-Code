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

const int MAXN = 4e5 + 5;
const int ha = 1e9 + 7;

int ans[MAXN];

inline void add1(int l,int r,int d){// 区间+
    ans[l] += d;ans[l+1] -= d;ans[r+1] -= d;ans[r+2] += d;
}

inline void add2(int l,int r){// 等差数列
    ans[l]++;ans[r+1] -= (r-l+2);ans[r+2] += (r-l+1);
}
int sm;
struct SAM{
    int ch[MAXN][10],fail[MAXN],rmin[MAXN],rmax[MAXN],len[MAXN];
    std::vector<int> G[MAXN];
    int tot,las;
    inline void clear(){
        FOR(i,1,tot){
            FOR(j,0,9) ch[i][j] = 0;
            fail[i] = rmin[i] = rmax[i] = len[i] = 0;G[i].clear();
        }
        tot = las = 1;
    }

    inline void copy(int x,int y){
        FOR(i,0,9) ch[x][i] = ch[y][i];fail[x] = fail[y];len[x] = len[y];
    }

    inline void insert(int c){
        int p = las,np = las = ++tot;len[np] = len[p]+1;
        for(;p&&!ch[p][c];p=fail[p]) ch[p][c] = np;
        if(!p) fail[np] = 1;
        else{
            int q = ch[p][c];
            if(len[q] == len[p]+1) fail[np] = q;
            else{
                int nq = ++tot;copy(nq,q);len[nq] = len[p]+1;fail[q] = fail[np] = nq;
                for(;p&&ch[p][c]==q;p=fail[p]) ch[p][c] = nq;
            }
        }
    }

    inline void dfs(int v){
        if(!rmin[v]) rmin[v] = 1e9;
        for(auto x:G[v]){
            dfs(x);
            rmin[v] = std::min(rmin[v],rmin[x]);
            rmax[v] = std::max(rmax[v],rmax[x]);
        }
        int l = len[fail[v]]+1,r = len[v],t = r-l+1;(sm += t)%=ha;
        if(rmin[v] <= rmax[v]-r+1) return;
        int L = rmax[v]-r+1,R = rmin[v]-1;
//        if(rmin[v] == rmax[v] && rmin[v] == 4){
//            DEBUG(L);DEBUG(L+t-1);
//            DEBUG(L+t);DEBUG(R);DEBUG(t);
//        }
        if(R-L+1 <= t) add2(L,R);
        else add2(L,L+t-1),add1(L+t,R,t);
    }

    inline void build(){
        FOR(i,1,tot) G[fail[i]].pb(i);//,DEBUG(fail[i]);
        dfs(1);
    }
}sam;

char str[MAXN];
int n;

inline void Solve(){
    sam.clear();scanf("%d",&n);
    scanf("%s",str+1);sm = 0;
    FOR(i,1,n) sam.insert(str[i]-'0'),sam.rmin[sam.las] = sam.rmax[sam.las] = i;
    FOR(i,0,n+2) ans[i] = 0;
    sam.build();
    FOR(i,1,n) (ans[i] += ans[i-1]) %= ha;
    FOR(i,1,n) (ans[i] += ans[i-1]) %= ha;
    int res = 0;
    FOR(i,1,n-1) ans[i] = (sm+ha-ans[i])%ha,(res = (1ll*res*100013%ha+ans[i])%ha) %= ha;//,DEBUG(ans[i]);
    printf("%d\n",res);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
