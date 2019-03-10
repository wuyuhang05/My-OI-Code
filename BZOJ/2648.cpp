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
#define lc (ch[x][0])
#define se second
#define U unsigned
#define rc (ch[x][1])
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000000+5;
int min[MAXN][2],max[MAXN][2],ch[MAXN][2];
int nthdir;

inline void upmin(int &a,int b){
    if(a > b) a = b;
}

inline void upmax(int &a,int b){
    if(a < b) a = b;
}

struct Point{
    int pos[2];
    int& operator [](int x){
        return pos[x];
    }

    bool operator < (const Point &t) const {
        return pos[nthdir] < t.pos[nthdir];
    }

    int operator - (const Point &t) const {
        return std::abs(pos[0]-t.pos[0]) + std::abs(pos[1]-t.pos[1]);
    }

    Point(int x,int y){
        pos[0] = x;pos[1] = y;
    }
    Point(){}
}p[MAXN];

inline void pushup(int x){
    if(lc){
        upmin(min[x][0],min[lc][0]);
        upmin(min[x][1],min[lc][1]);
        upmax(max[x][0],max[lc][0]);
        upmax(max[x][1],max[lc][1]);
    }
    if(rc){
        upmin(min[x][0],min[rc][0]);
        upmin(min[x][1],min[rc][1]);
        upmax(max[x][0],max[rc][0]);
        upmax(max[x][1],max[rc][1]);
    }
}

inline int build(int l,int r,int dir){
    nthdir = dir;int x = (l + r) >> 1;
    std::nth_element(p+l,p+x,p+r+1);
    min[x][0] = max[x][0] = p[x][0];
    min[x][1] = max[x][1] = p[x][1];
    if(l < x) lc = build(l,x-1,dir^1);
    if(r > x) rc = build(x+1,r,dir^1);
    pushup(x);return x;
}
int cnt;
inline void insert(int x,Point P,int dir){
    if(P[dir] < p[x][dir]){
        if(lc) insert(lc,P,dir^1);
        else{
            lc = ++cnt;p[cnt] = P;
            min[cnt][0] = max[cnt][0] = P[0];
            min[cnt][1] = max[cnt][1] = P[1];
        }
    }
    else{
        if(rc) insert(rc,P,dir^1);
        else{
            rc = ++cnt;p[cnt] = P;
            min[cnt][0] = max[cnt][0] = P[0];
            min[cnt][1] = max[cnt][1] = P[1];
        }
    }
    pushup(x);
}

inline int calc(int x,Point P){
    return std::max(0,min[x][0]-P[0]) + std::max(0,min[x][1]-P[1]) + std::max(0,P[0]-max[x][0]) + std::max(0,P[1]-max[x][1]);
} // 点 P 到分割集 x 的距离

int ans = INT_MAX;

inline void query(int x,Point P){
    ans = std::min(ans,P-p[x]);
    int L = INT_MAX,R = INT_MAX;
    if(lc) L = calc(lc,P);
    if(rc) R = calc(rc,P);
    if(L < R){
        if(L < ans) query(lc,P);
        if(R < ans) query(rc,P);
    }
    else{
        if(R < ans) query(rc,P);
        if(L < ans) query(lc,P);
    }
}

int N,M;

int main(){
    //freopen("1.in","r",stdin);
    scanf("%d%d",&N,&M);cnt = N;
    FOR(i,1,N) scanf("%d%d",&p[i][0],&p[i][1]);
    int root = build(1,N,0);
    while(M--){
        int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
        if(opt & 1) insert(root,Point(x,y),0);
        else{
            ans = INT_MAX;query(root,Point(x,y));
            printf("%d\n",ans);
        }
    }
    return 0;
}