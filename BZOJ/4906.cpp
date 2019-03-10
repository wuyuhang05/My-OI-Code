#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define lc(x) (ch[x][0])
#define se second
#define U unsigned
#define rc(x) (ch[x][1])
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500000+5;

inline char nc(){
    static char buf[MAXN],*p1 = buf+MAXN,*p2 = buf+MAXN;
    if(p1 == p2){
        p1 = buf;p2 = buf + fread(buf,1,MAXN,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;char ch = nc();int flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<3) + (x<<1) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

inline void read(LL &x){
    x = 0;char ch = nc();int flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<3) + (x<<1) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

struct Data{
    LL f[4][4];
    Data(){}
    Data(LL a,LL b,LL c,LL l){
        CLR(f,0);a *= l;b *= l;c *= l;
        f[0][0] = f[3][3] = a;f[1][1] = b;f[2][2] = c;
        f[0][1] = std::max(a,b);f[1][2] = std::max(b,c);f[2][3] = std::max(a,c);
        f[0][2] = f[1][3] = f[0][3] = std::max(a,std::max(b,c));
    }

    Data operator + (const Data &t) const{
        Data res;CLR(res.f,0);
        FOR(l,1,4){
            FOR(i,0,4-l){
                int j = i+l-1;
                FOR(k,i,j) res.f[i][j] = std::max(res.f[i][j],f[i][k]+t.f[k][j]);
            }
        }
        return res;
    }
}val[MAXN];
int fa[MAXN],ch[MAXN][2],A[MAXN],L[MAXN],B[MAXN],C[MAXN],q[MAXN],size[MAXN];
int N,cnt,top,root,rebuilder;
LL len[MAXN],tot;

const double alpha = 0.8;

inline bool isbad(int x){
    return alpha*size[x] < std::max(size[lc(x)],size[rc(x)]);
}

inline void pushup(int x){
    val[x] = Data(A[x],B[x],C[x],L[x]);
    if(lc(x)) val[x] = val[lc(x)] + val[x];
    if(rc(x)) val[x] = val[x] + val[rc(x)];
    len[x] = len[lc(x)] + len[rc(x)] + L[x];
    size[x] = size[lc(x)] + size[rc(x)] + 1;
}

inline int find(int x,LL pos){
    if((len[lc(x)] < pos || (!lc(x) && !pos)) && len[lc(x)]+L[x] >= pos) return x;
    if(len[lc(x)] >= pos) return find(lc(x),pos);
    tot += len[lc(x)]+L[x];
    return find(rc(x),pos-len[lc(x)]-L[x]);
}

inline void insert(int &x,int a,int b,int c,LL pos,int l,int pre=0){
    if(!x){
        x = ++cnt;val[x] = Data(a,b,c,l);
        A[x] = a;B[x] = b;C[x] = c;L[x] = len[x] = l;size[x] = 1;fa[x] = pre;
        return;
    }
    if(pos < len[lc(x)]+L[x]) insert(lc(x),a,b,c,pos,l,x);
    else insert(rc(x),a,b,c,pos-len[lc(x)]-L[x],l,x);
    pushup(x);
    if(isbad(x)) rebuilder = x;
}

inline void update(int x,int k,LL pos,int l){
    if(x == k){
        L[x] = l;pushup(x);
        return;
    }
    if(pos <= len[lc(x)]) update(lc(x),k,pos,l);
    else update(rc(x),k,pos-len[lc(x)]-L[x],l);
    pushup(x);
}

inline void dfs(int x){
    if(lc(x)) dfs(lc(x));
    q[++top] = x;
    if(rc(x)) dfs(rc(x));
}

inline void build(int &x,int l,int r,int pre){
    if(l > r){
        x = 0;return;
    }
    int mid = (l + r) >> 1;//DEBUG(mid);
    x = q[mid];fa[x] = pre;
    build(lc(x),l,mid-1,x);build(rc(x),mid+1,r,x);
    pushup(x);
}

inline void rebuild(int x){
    rebuilder = top = 0;dfs(x);int y = fa[x];
    if(!y) build(root,1,top,0);
    else build(ch[y][rc(y)==x],1,top,y);
}

signed main(){
    int N;read(N);
    insert(root,0,0,0,0,0);
    LL lastans = 0;
    FOR(i,1,N){
        LL p;int a,b,c,d;
        read(p);read(a);read(b);read(c);read(d);
        tot = 0;int x = find(root,p);
        if(tot + len[lc(x)] + L[x] != p){
            LL left = tot + len[lc(x)] + L[x] - p;
            update(root,x,p,L[x]-left);
            insert(root,a,b,c,p,d);if(rebuilder) rebuild(rebuilder);
            insert(root,A[x],B[x],C[x],p+d,left);
        }
        else insert(root,a,b,c,p,d);
        printf("%lld\n",val[root].f[0][3]-lastans);
        lastans = val[root].f[0][3];if(rebuilder) rebuild(rebuilder);
    }
    return 0;
}