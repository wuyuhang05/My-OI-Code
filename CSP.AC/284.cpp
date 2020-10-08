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

const int MAXN = 2e5 + 5;
int n,m,N,q;
int ans[MAXN];

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

struct Node{
    int y;char opt,d;int id;// 0 = mod

    Node(int y=0,char opt=0,char d=0,int id=0) : y(y),opt(opt),d(d),id(id) {}
};
std::vector<Node> G[MAXN];

int l[MAXN],r[MAXN],B;

inline void add(int x1,int x2,int y1,int y2,int d,int id){
    if(x1 > x2 || y1 > y2) return;
    G[x2].pb(Node(y2,1,1*d,id));
    G[x2].pb(Node(y1-1,1,-1*d,id));
    G[x1-1].pb(Node(y2,1,-1*d,id));
    G[x1-1].pb(Node(y1-1,1,1*d,id));
}

const int MAXM = 500+5;

struct DS{// O(sqrt(n)) 单点修改 O(1) 查询前缀和
    int B,n;
    int bel[MAXN];
    int sm[MAXM][MAXM],pre[MAXM];

    inline void build(int xxx){
        n = xxx;B = std::sqrt(1.0*n);
        FOR(i,1,n) bel[i] = (i-1)/B+1;
    }

    inline void add(int pos,int x){
//        FOR(i,pos,n) pre[i] += x;
//        return;
        FOR(i,bel[pos]+1,bel[n]) pre[i] += x;
        FOR(i,pos-(bel[pos]-1)*B,bel[pos]*B-(bel[pos]-1)*B) sm[bel[pos]][i] += x;
    }

    inline int query(int x){
//        return pre[x];
        return pre[bel[x]]+sm[bel[x]][x-(bel[x]-1)*B];
    }
}ds;

bool vis[MAXN];
int uu[MAXN],vv[MAXN];

int main(){
//    freopen("D.in","r",stdin);
//    freopen("D.out","w",stdout);
    read(n);read(m);read(q);
    FOR(i,1,m){
        int u,v;read(u);read(v);
        if(u > v) std::swap(u,v);
        uu[i] = u;vv[i] = v;
        G[u].pb(Node(v,0));
    }
    B = 300;
    FOR(id,1,q){
        int k;read(k);
        if(k >= B){
            FOR(i,1,n) vis[i] = 0;
            FOR(i,1,k){
                int l,r;read(l);read(r);
                FOR(j,l,r) vis[j] = 1;
            }
            FOR(i,1,m) ans[id] += vis[uu[i]]&vis[vv[i]];
        }
        else{
            FOR(i,1,k) read(l[i]),read(r[i]);
 //           if(id != 6) continue;
            FOR(i,1,k){
                FOR(j,i,k){
                    add(l[i],r[i],l[j],r[j],1,id);
                }
            }
        }
    }
    ds.build(n);
    FOR(i,0,n){
        for(auto x:G[i]){
            if(x.opt == 0) ds.add(x.y,1);
        }
        for(auto x:G[i]){
            if(x.opt == 1) ans[x.id] += x.d*ds.query(x.y);
        }
    }
//    DEBUG(ans[1]);
    FOR(i,1,q) puts(ans[i]?"GG":"SAFE");
    return 0;
}