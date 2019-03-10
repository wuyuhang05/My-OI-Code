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
#define int LL
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
int nthdir;

struct Point{
    int pos[2];
    int& operator [] (const int &x) {
        return pos[x];
    }

    bool operator < (const Point &t) const {
        return pos[nthdir] < t.pos[nthdir];
    }
}p[MAXN],data[MAXN];
int max[MAXN][2],min[MAXN][2],ch[MAXN][2],size[MAXN];
int bin[MAXN],top,cnt;

inline int New(){
    if(top) return bin[top--];
    return ++cnt;
}

inline void pushup(int x){
    FOR(i,0,1){
        min[x][i] = max[x][i] = p[x][i];
        if(lc){
            min[x][i] = std::min(min[x][i],min[lc][i]);
            max[x][i] = std::max(max[x][i],max[lc][i]);
        }
        if(rc){
            min[x][i] = std::min(min[x][i],min[rc][i]);
            max[x][i] = std::max(max[x][i],max[rc][i]);
        }
    }
    size[x] = size[lc] + size[rc] + 1;
}

inline int build(int l,int r,int dir){
    if(l > r) return 0;
    int x = New(),mid = (l + r) >> 1;
    nthdir = dir;std::nth_element(data+l,data+mid,data+r+1);
    p[x] = data[mid];lc = build(l,mid-1,dir^1);
    rc = build(mid+1,r,dir^1);
    pushup(x);return x;
}

#define pf(x) ((x)*(x))

LL dis(int x,Point p){
    return std::max(pf(max[x][0]-p[0]),pf(min[x][0]-p[0])) + std::max(pf(max[x][1]-p[1]),pf(min[x][1]-p[1]));
}

LL dis(Point a,Point b){
    return pf(a[0]-b[0])+pf(a[1]-b[1]);
}

std::priority_queue<LL,std::vector<LL>,std::greater<LL> > q;

void query(int x,Point P){
    int L = LLONG_MIN,R = LLONG_MIN;
    if(lc) L = dis(lc,P);
    if(rc) R = dis(rc,P);
    LL t = dis(P,p[x]);
    if(t > q.top()){
        q.pop();q.push(t);
    }
    if(L > R){
        if(L > q.top()) query(lc,P);
        if(R > q.top()) query(rc,P);
    }
    else{
        if(R > q.top()) query(rc,P);
        if(L > q.top()) query(lc,P);
    }
}

int N,M;

signed main(){
    //freopen("1.in","r",stdin);
    scanf("%lld%lld",&N,&M);
    FOR(i,1,N) scanf("%lld%lld",&data[i][0],&data[i][1]);
    int root = build(1,N,0);//M <<= 1;
    FOR(i,1,(M<<1)) q.push(0);
    FOR(i,1,N) query(root,data[i]);
    printf("%lld\n",q.top());
    return 0;
}