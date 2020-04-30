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
#define int LL
const int MAXN = 2e5 + 5;

int f[MAXN],ch[MAXN][2],rev[MAXN];
int mx[MAXN];
int sm[MAXN];//链
int xsm[MAXN];//链上每一个点的虚子树和的和
int ms[MAXN];//=sm[x]+xsm[x]
int son[MAXN];//这个点的虚子树和
int cov[MAXN],tag[MAXN];
int sz[MAXN],val[MAXN];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
    mx[x] = std::max(val[x],std::max(mx[lc],mx[rc]));
    sm[x] = sm[lc]+sm[rc]+val[x];
    xsm[x] = xsm[lc]+xsm[rc]+son[x];
    ms[x] = sm[x]+xsm[x];
    sz[x] = sz[lc]+sz[rc]+1;
}

inline void cover(int x,int d){
    mx[x] = cov[x] = val[x] = d;tag[x] = 0;
    sm[x] = d*sz[x];ms[x] = sm[x]+xsm[x];
}

inline void add(int x,int d){
    mx[x] += d;val[x] += d;
    if(cov[x]) cov[x] += d;
    else tag[x] += d;
    sm[x] += d*sz[x];ms[x] = sm[x]+xsm[x];
}

inline void reverse(int x){
    std::swap(lc,rc);rev[x] ^= 1;
}

inline void pushdown(int x){
    if(rev[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        rev[x] = 0;
    }
    if(cov[x]){
        if(lc) cover(lc,cov[x]);
        if(rc) cover(rc,cov[x]);
        cov[x] = tag[x] = 0;
    }
    if(tag[x]){
        if(lc) add(lc,tag[x]);
        if(rc) add(rc,tag[x]);
        tag[x] = 0;
    }
}

inline bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;f[x] = z;
    ch[x][!k] = y;f[y] = x;
    ch[y][k] = w;if(w) f[w] = y;
    pushup(y);pushup(x);
}
int st[MAXN];
inline void splay(int x){
    int y = x,z;
    st[z = 1] = y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[z][1]==y)^(ch[y][1]==x) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y = 0;x;x = f[y = x]){
        splay(x);son[x] += ms[rc]-ms[y];rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline void link(int x,int y){
    makeroot(x);makeroot(y);
    f[x] = y;son[y] += ms[x];pushup(y);
}

inline void cut(int x,int y){
    makeroot(x);access(y);splay(y);
    //son[y] -= ms[x];// !!!这是个实边!!!
    ch[y][0] = f[x] = 0;pushup(y);
}

inline void split(int x,int y){
    makeroot(x);access(y);splay(y);
}

signed main(){
    int n,m;scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",val+i),sz[i] = 1;
    FOR(i,2,n){
        int f;scanf("%lld",&f);link(f,i);
    }
    scanf("%lld",&m);
    FOR(i,1,m){
        int opt,x,y;scanf("%lld%lld%lld",&opt,&x,&y);
        if(opt == 1){
            int z;scanf("%lld",&z);
            split(x,y);add(y,z);
        }
        if(opt == 2){
            int z;scanf("%lld",&z);
            split(x,y);cover(y,z);
        }
        if(opt == 3){
            makeroot(x);access(y);splay(y);printf("%lld\n",son[y]+val[y]);
        }
        if(opt == 4){
            split(x,y);printf("%lld\n",mx[y]);
        }
        if(opt == 5){
            split(x,y);printf("%lld\n",sm[y]);
        }
        if(opt == 6){
            link(x,y);
        }
        if(opt == 7){
            cut(x,y);
        }
    }
    return 0;
}
