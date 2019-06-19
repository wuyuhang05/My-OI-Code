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

const int MAXN = 1000000+5;
const int ha = 998244353;

#define lc (ch[x][0])
#define rc (ch[x][1])
int sum[MAXN<<5],ch[MAXN<<5][2],root[MAXN],tot;

inline void pushup(int x){
    sum[x] = sum[lc] + sum[rc];
}

inline void insert(int &x,int l,int r,int pos){
    if(!x) x = ++tot;
    sum[x]++;
    if(l == r) return;
    int mid = (l + r) >> 1;
    pos <= mid ? insert(lc,l,mid,pos) : insert(rc,mid+1,r,pos);
}

inline void merge(int &x,int y,int l,int r){
    if(!x || !y){
        x = x|y;return;
    }
    if(l == r) return;
    int mid = (l + r) >> 1;
    merge(lc,ch[y][0],l,mid);
    merge(rc,ch[y][1],mid+1,r);
    pushup(x);
}

int query(int x,int l,int r){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    return sum[lc] ? query(lc,l,mid) : query(rc,mid+1,r);
}

void del(int &x,int l,int r,int pos){
    if(r <= pos){
        x = 0;return;
    }
    int mid = (l + r) >> 1;
    del(lc,l,mid,pos);
    if(mid < pos) del(rc,mid+1,r,pos);
    pushup(x);if(!sum[x]) x = 0;
}

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    int ans = 1;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        if(u > v) std::swap(u,v);
        insert(root[u],1,n,v);
    }
    FOR(i,1,n){
        int x = query(root[i],1,n);ans = 1ll*ans*(n-sum[root[i]])%ha;
        merge(root[x],root[i],1,n);del(root[x],1,n,x);
    }
    printf("%d\n",ans);
    return 0;
}
