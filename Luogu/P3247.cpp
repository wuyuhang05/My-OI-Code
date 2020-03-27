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


const int MAXN = 2e5 + 5;
int n,m;

struct Node{
    int u,v,a,b,k;
    Node(int u=0,int v=0,int a=0,int b=0,int k=0) : u(u),v(v),a(a),b(b),k(k) {}
}a[MAXN],tmp[MAXN],b[MAXN];

int f[MAXN],mxa[MAXN],mxb[MAXN],sz[MAXN],tot;

struct Data{
    int u,v,fx,fy,mxax,mxbx,mxay,mxby,szx,szy;
    Data(int u=0,int v=0,int fx=0,int fy=0,int mxax=0,int mxbx=0,int mxay=0,int mxby=0,int szx=0,int szy=0) : u(u),v(v),fx(fx),fy(fy),mxax(mxax),mxbx(mxbx),mxay(mxay),mxby(mxby),szx(szx),szy(szy) {}
}st[MAXN];

inline int find(int x){
    return x == f[x] ? x : find(f[x]);
}

inline void merge(int x,int y,int a,int b){
    x = find(x);y = find(y);if(sz[x] < sz[y]) std::swap(x,y);
    st[++tot] = Data(x,y,f[x],f[y],mxa[x],mxb[x],mxa[y],mxb[y],sz[x],sz[y]);
    if(x != y){
        sz[x] += sz[y];f[y] = x;
        mxa[x] = std::max(mxa[x],mxa[y]);mxb[x] = std::max(mxb[x],mxb[y]);
    }
    mxa[x] = std::max(mxa[x],a);mxb[x] = std::max(mxb[x],b);
}

inline void undo(){
//    assert(tot != 0);
    int u = st[tot].u,v = st[tot].v;
    f[u] = st[tot].fx;f[v] = st[tot].fy;mxa[u] = st[tot].mxax;mxb[u] = st[tot].mxbx;
    mxa[v] = st[tot].mxay;mxb[v] = st[tot].mxby;sz[u] = st[tot].szx;sz[v] = st[tot].szy;tot--;
}
bool ans[MAXN];
int main(){
//    freopen("10.in","r",stdin);
//    freopen("10.ans","w",stdout);
    read(n);read(m);
    FOR(i,1,m) read(a[i].u),read(a[i].v),read(a[i].a),read(a[i].b);
    std::sort(a+1,a+m+1,[](const Node &a,const Node &b){return a.a < b.a;});
    int q;read(q);
    FOR(i,1,q) read(b[i].u),read(b[i].v),read(b[i].a),read(b[i].b),b[i].k = i;
    std::sort(b+1,b+n+1,[](const Node &a,const Node &b){return a.b < b.b;});
    int blo = std::sqrt(1.0*m*log(n)/log(2));
    for(int i = 1;i <= m;i += blo){//[i,i+blo-1]
        std::fill(mxa+1,mxa+n+1,-1);std::fill(mxb+1,mxb+n+1,-1);std::iota(f+1,f+n+1,1);std::fill(sz+1,sz+n+1,1);tot = 0;
        int cnt = 0;FOR(j,1,q) if(b[j].a >= a[i].a && (i+blo > m || b[j].a < a[i+blo].a)) tmp[++cnt] = b[j];// 必须是小于号 要不然一个询问可能会被跑多次 这样都扔到最后面就好了
        if(!cnt) continue;
        if(i > 1) std::sort(a+1,a+i,[](const Node &a,const Node &b){return a.b < b.b;});
        int now = 1;
//        DEBUG(cnt);
        FOR(j,1,cnt){
            for(;now < i && a[now].b <= tmp[j].b;++now) merge(a[now].u,a[now].v,a[now].a,a[now].b);
            int t = 0;
            FOR(k,i,std::min(m,i+blo-1)){
                if(a[k].a <= tmp[j].a && a[k].b <= tmp[j].b) merge(a[k].u,a[k].v,a[k].a,a[k].b),++t;
            }
            int fu = find(tmp[j].u),fv = find(tmp[j].v);
            ans[tmp[j].k] = (fu==fv)&&(mxa[fu] == tmp[j].a && mxb[fu] == tmp[j].b);
//            assert((fu != fv) || (mxa[fu] <= tmp[j].a && mxb[fu] <= tmp[j].b));
//            FOR(k,1,n) printf("%d ",f[k]);puts("");
            while(t--) undo();
        }
    }
    FOR(i,1,q) puts(ans[i]?"Yes":"No");
    return 0;
}
