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

const int MAXN = 500000+5;

struct Point{
    int x,y;
    Point(int x=0,int y=0) : x(x), y(y) {}

    bool operator < (const Point &t) const {
        return x == t.x ? y < t.y : x < t.x;
    }
    Point operator + (const Point &t) const {
        return Point(x+t.x,y+t.y);
    }

    Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    int operator * (const Point &t) const {
        return x*t.x + y*t.y;
    }

    int operator ^ (const Point &t) const { // Cross
        return x*t.y - y*t.x;
    }
};

std::vector<Point> v[MAXN<<2],t[MAXN<<2];
#define lc (x<<1)
#define rc (x<<1|1)

inline void insert(int x,int l,int r,const Point &p,int pos){
    t[x].pb(p);
    if(r == pos){ // build
        std::sort(all(t[x]));
        FOR(i,0,r-l){
            while(v[x].size() > 1 && ((t[x][i]-v[x][v[x].size()-1])^(v[x][v[x].size()-2]-v[x][v[x].size()-1])) >= 0) v[x].pop_back();
            v[x].pb(t[x][i]);
        }
    }
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid) insert(lc,l,mid,p,pos);
    else insert(rc,mid+1,r,p,pos);
}

inline int query(int x,int l,int r,int L,int R,const Point &t){
    if(l == L && r == R){
        int ll = 1,rr = v[x].size()-1,ans = 0;
        while(ll <= rr){
            int mid = (ll+rr) >> 1;
            if(t*v[x][mid] > t*v[x][mid-1]) ans = mid,ll = mid+1;
            else rr = mid-1;
        }
        return t*v[x][ans];
    }
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R,t);
    if(L > mid) return query(rc,mid+1,r,L,R,t);
    else return std::max(query(lc,l,mid,L,mid,t),query(rc,mid+1,r,mid+1,R,t));
}

int N,lastans,cnt;

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        int opt,x,y,l,r;scanf("%d%d%d",&opt,&x,&y);
        x ^= lastans;y ^= lastans;
        if(opt & 1){
            insert(1,1,N,Point(x,y),++cnt);
        }
        else{
            scanf("%d%d",&l,&r);l ^= lastans;r ^= lastans;
            printf("%d\n",lastans=query(1,1,N,l,r,Point(x,y)));
        }
    }
    return 0;
}
