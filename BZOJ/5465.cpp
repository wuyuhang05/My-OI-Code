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

const int MAXN = 300000+100;
const double EPS = 1e-8;

int nthdir;

struct dat{
    int pos[2],r,id;

    int& operator [](int x){
        if(x <= 1) return pos[x];
        if(x == 2) return r;
        return id;
    }

    bool operator < (const dat &t) const {
        return pos[nthdir] < t.pos[nthdir];
    }
}p[MAXN],data[MAXN];

int min[MAXN][2],max[MAXN][2],ch[MAXN][2];

inline void upmax(int &a,int b){
    if(a < b) a = b;
}

inline void upmin(int &a,int b){
    if(a > b) a = b;
}

inline bool cmp(dat x,dat y){
    return x[2] == y[2] ? x[3] < y[3] : x[2] > y[2];
}

inline void pushup(int x){
    min[x][0] = p[x][0]-p[x][2];max[x][0] = p[x][0]+p[x][2];
    min[x][1] = p[x][1]-p[x][2];max[x][1] = p[x][1]+p[x][2];
    if(lc){
        upmin(min[x][0],min[lc][0]);upmin(min[x][1],min[lc][1]);
        upmax(max[x][0],max[lc][0]);upmax(max[x][1],max[lc][1]);
    }
    if(rc){
        upmin(min[x][0],min[rc][0]);upmin(min[x][1],min[rc][1]);
        upmax(max[x][0],max[rc][0]);upmax(max[x][1],max[rc][1]);
    }
}

int cnt;

inline void build(int &x,int l,int r,int dir){
    int mid = (l + r) >> 1;nthdir = dir;
    std::nth_element(data+l,data+mid,data+r+1);x = ++cnt;
    p[x] = data[mid];
    if(l < mid) build(lc,l,mid-1,dir^1);
    if(r > mid) build(rc,mid+1,r,dir^1);
    pushup(x);
}

#define pf(x) ((x)*(x))

inline bool calc(int x,dat t){
    return pf(1ll*t[0]-p[x][0])+pf(1ll*t[1]-p[x][1]) - EPS <= pf(1ll*t[2]+p[x][2]);
}

inline bool far(int x,dat t){
    return (t[0]+t[2]<min[x][0]) || (t[1]+t[2]<min[x][1]) || (t[0]-t[2]>max[x][0]) || (t[1]-t[2]>max[x][1]);
}

int ans[MAXN];

inline void query(int x,dat t){
    if(far(x,t)) return;
    // DEBUG(p[x][3]);
    if(!ans[p[x][3]] && calc(x,t)) ans[p[x][3]] = t[3];
    if(lc) query(lc,t);
    if(rc) query(rc,t);
}

int N;

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d%d%d",&data[i][0],&data[i][1],&data[i][2]);
        data[i][3] = i;
    }
    int root;build(root,1,N,0);
    std::sort(data+1,data+N+1,cmp);
    FOR(i,1,N){
        // DEBUG(data[i][3]);
        if(!ans[data[i][3]]) query(root,data[i]);
    }
    FOR(i,1,N) printf("%d ",ans[i]);puts("");
    return 0;
}