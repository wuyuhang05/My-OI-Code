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

const int MAXN = 3e5 + 5;
const int MAXM = 1e5 + 5;

double a[MAXN];

struct Node{
    int l,r;
    Node(int l=0,int r=0) : l(l),r(r) {}

    bool operator < (const Node &t) const {
        if(a[l] != a[t.l]) return a[l] < a[t.l];
        return a[r] < a[t.r];
    }

    bool operator == (const Node &t) const {
        return a[l] == a[t.l] && a[r] == a[t.r];
    }
};
int tot;
int id[MAXN],tp,rt;
int css;
struct SGT{
    Node v[MAXN];int ch[MAXN][2],sz[MAXN];
    #define lc (ch[x][0])
    #define rc (ch[x][1])

    inline void dfs(int x){
        if(lc) dfs(lc);
        id[++tp] = x;
        if(rc) dfs(rc);
    }
    
    inline void build(int &x,int l,int r,double L,double R){
        if(l > r){
            x = 0;return;
        }
        int mid = (l + r) >> 1;
        x = id[mid];a[x] = (L+R)/2;
        build(lc,l,mid-1,L,a[x]);build(rc,mid+1,r,a[x],R);
        sz[x] = sz[lc]+sz[rc]+1;
    }

    inline void rebuild(int &x,double L,double R){
//        return;
        tp = 0;dfs(x);
        build(x,1,tp,L,R);
    }
    int R;
    inline int insert(int &x,double l,double r,Node d){
        if(!x){
            if(css == 9) DEBUG(l),DEBUG(r);
            v[x = ++tot] = d;sz[x] = 1;a[x] = (l+r)/2;
            return x;
        }
        if(d == v[x]) return x;
        int p;//sz[x]++;
        if(d < v[x]) p = insert(lc,l,(l+r)/2,d);
        else p = insert(rc,(l+r)/2,r,d);
        sz[x] = sz[lc]+sz[rc]+1;
        if(sz[x]*0.75 > std::max(sz[lc],sz[rc])){
            if(R){
                if(lc == R) rebuild(lc,l,(l+r)/2);
                else rebuild(rc,(l+r)/2,r);
                R = 0;
            }
        }
        else R = x;
        return p;
    }
    #undef lc
    #undef rc
}T;
#define lc ((x)<<1)
#define rc ((x)<<1|1)

int mx[MAXM<<2];
int ps[MAXM];

inline void pushup(int x){
    mx[x] = a[ps[mx[lc]]] >= a[ps[mx[rc]]] ? mx[lc] : mx[rc];
}

inline void update(int x,int l,int r,int p){
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc,l,mid,p);
    else update(rc,mid+1,r,p);
    pushup(x);
}

inline int query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return mx[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    int p = query(lc,l,mid,L,mid),q = query(rc,mid+1,r,mid+1,R);
    return a[ps[p]] >= a[ps[q]] ? p : q;
}

inline void build(int x,int l,int r){
    if(l == r){
        mx[x] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}
int n,m;
int main(){
    scanf("%d%d",&n,&m);
//    a[0] = -1;
//    T.insert(rt,0,1,Node(0,0));
//    FOR(i,1,n) ps[i] = 1;
    build(1,1,n);
    FOR(i,1,m){
        css = i;
        char opt[23];int l,r;scanf("%s%d%d",opt,&l,&r);
        if(opt[0] == 'C'){
            int p;scanf("%d",&p);
     //       if(i == 9) DEBUG(a[rt]);
            ps[p] = T.insert(rt,0,1,Node(ps[l],ps[r]));
            if(T.R) T.rebuild(rt,0,1),T.R = 0;//别忘了改root
            update(1,1,n,p);
        }
        else{
            printf("%d\n",query(1,1,n,l,r));
        }
    }
    return 0;
}
/*
5 10
C 1 1 1
C 2 1 2
Q 1 2
C 4 4 4
C 5 5 5
Q 4 5
Q 3 3
C 4 2 3
C 4 4 4
Q 3 4
*/
