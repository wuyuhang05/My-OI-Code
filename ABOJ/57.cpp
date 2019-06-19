#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;
const int MAXM = 100000;
const LL ha = 2333333333333341;

inline LL rnd(){
    return ((LL)rand()<<31ll)|rand();
}

int n,q,lc[MAXN<<4],rc[MAXN<<4],size[MAXN<<4],a[MAXN],root[MAXN],cnt;
LL b[MAXN],v[MAXN<<4];

inline void insert(int prev,int &x,int l,int r,int pos){
    x = ++cnt;
    size[x] = size[prev] + 1;
    lc[x] = rc[x] = 0;
    v[x] = (v[prev] + b[pos])%ha;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) rc[x] = rc[prev],insert(lc[prev],lc[x],l,mid,pos);
    else lc[x] = lc[prev],insert(rc[prev],rc[x],mid+1,r,pos);
}

inline int qmax(int x,int y,int l,int r){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(size[rc[x]] != size[rc[y]]) return qmax(rc[x],rc[y],mid+1,r);
    else return qmax(lc[x],lc[y],l,mid);
}

inline int qmin(int x,int y,int l,int r){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(size[lc[x]] != size[lc[y]]) return qmin(lc[x],lc[y],l,mid);
    return qmin(rc[x],rc[y],mid+1,r);
}

bool chk(int l1,int r1,int l2,int r2){
    int l = 1,r = MAXM,mid;
    l1 = root[l1-1];r1 = root[r1];
    l2 = root[l2-1];r2 = root[r2];
    if((v[r1]-v[l1]+ha)%ha == (v[r2]-v[l2]+ha)%ha && size[r1]-size[l1] == size[r2] - size[l2]) return true;
    while(l < r){
        int mid = (l + r) >> 1;
        if((v[lc[r1]]-v[lc[l1]]+ha)%ha == (v[lc[r2]]-v[lc[l2]]+ha)%ha && size[lc[r1]]-size[lc[l1]] == size[lc[r2]] - size[lc[l2]])
                r1 = rc[r1],l1 = rc[l1],r2 = rc[r2],l2 = rc[l2],l = mid+1;
        else if((v[rc[r1]]-v[rc[l1]]+ha)%ha == (v[rc[r2]]-v[rc[l2]]+ha)%ha && size[rc[r1]] - size[rc[l1]] == size[rc[r2]]-size[rc[l2]])
            r1 = lc[r1],l1 = lc[l1],r2 = lc[r2],l2 = lc[l2],r = mid;
        else{
            if((size[lc[r1]]-size[lc[l1]]) - (size[lc[r2]]-size[lc[l2]]) == -1)
                std::swap(l1,l2),std::swap(r1,r2);
            if((size[lc[r1]]-size[lc[l1]]) - (size[lc[r2]]-size[lc[l2]]) == 1)
                if((v[r1]-v[l1]-b[qmax(lc[l1],lc[r1],l,mid)]+ha+ha)%ha == (v[r2]-v[l2]-b[qmin(rc[l2],rc[r2],mid+1,r)]+ha+ha)%ha)
                    return true;
            return false;
        }
    }
    return true;
}

inline void Solve(){
    cnt = 0;scanf("%d%d",&n,&q);
    FOR(i,1,n){
        scanf("%d",a+i);
        insert(root[i-1],root[i],1,MAXM,a[i]);
    }
    FOR(i,1,q){
        int l1,r1,l2,r2;scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        puts(chk(l1,r1,l2,r2) ? "YES" : "NO");
    }
}

int main(){
    srand(time(NULL));
    FOR(i,1,MAXM) b[i] = (rnd()%ha+ha)%ha;
    std::sort(b+1,b+MAXM+1);
    FOR(i,1,MAXM) b[i] = (b[i]+i)%ha;
    std::random_shuffle(b+1,b+MAXM+1);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
