/*
 * Author: RainAir
 * Time: 2019-07-25 18:28:05
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
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

inline char nc(){
    #define SIZE 100000+1
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
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

const int MAXN = 2e5+5;
const int BASE = 100;
int n,m;

struct Query{
    int x1,y1,x2,y2,id;
    Query(){}
    Query(int x1,int y1,int x2,int y2,int id) : x1(x1),y1(y1),x2(x2),y2(y2),id(id) {}
};
std::vector<Query> Q;

struct Node{
    int x,y,dis;
    Node(){}
    Node(int x,int y,int dis) : x(x),y(y),dis(dis) {}

    bool operator < (const Node &t) const {
        return dis > t.dis;
    }
};

std::vector<std::vector<int> > r,c,dis;
std::vector<std::vector<bool> > vis;
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

inline void dij(int xs,int ys,int xl,int xr,int yl,int yr){
    FOR(i,xl,xr) FOR(j,yl,yr) dis[i][j] = 1e9,vis[i][j] = false;
    std::priority_queue<Node> q;
    q.push(Node(xs,ys,dis[xs][ys]=0));
    while(!q.empty()){
        Node v = q.top();q.pop();
        if(vis[v.x][v.y]) continue;
        vis[v.x][v.y] = true;
        FOR(i,0,3){
            int xx = v.x+dx[i],yy = v.y + dy[i];
            if(xx >= xl && xx <= xr && yy >= yl && yy <= yr){
                int w=-1;
                if(v.y < yy) w = r[v.x][v.y];
                if(yy < v.y) w = r[xx][yy];
                if(v.x < xx) w = c[v.x][v.y];
                if(xx < v.x) w = c[xx][yy];
                assert(w != -1);
                //printf("(%d,%d) -> (%d,%d):%d\n",v.x,v.y,xx,yy,w);

                if(dis[xx][yy] > dis[v.x][v.y]+w){
                    dis[xx][yy] = dis[v.x][v.y]+w;
                    q.push(Node(xx,yy,dis[xx][yy]));
                }
            }
        }
    }
}

int ans[MAXN];

inline void work(int xl,int xr,int yl,int yr,const std::vector<Query> &q){
    if(xl > xr || yl > yr || q.empty()) return;
    std::vector<Query> ql,qr;
    //DEBUG(xl);DEBUG(xr);DEBUG(yl);DEBUG(yr);
    if((xr-xl+1)*(yr-yl+1) <= BASE){
        FOR(i,0,(int)q.size()-1){
            dij(q[i].x1,q[i].y1,xl,xr,yl,yr);
            ans[q[i].id] = std::min(dis[q[i].x2][q[i].y2],ans[q[i].id]);
        }
        return;
    }
    if((xr-xl+1) > (yr-yl+1)){ // 分治 x
        int mid = (xl+xr)>>1;
        FOR(i,yl,yr){
            dij(mid,i,xl,xr,yl,yr);
            FOR(i,0,(int)q.size()-1){
                ans[q[i].id] = std::min(ans[q[i].id],dis[q[i].x1][q[i].y1]+dis[q[i].x2][q[i].y2]);
            }
        }
        FOR(i,0,(int)q.size()-1){
            if(q[i].x1 < mid && q[i].x2 < mid) ql.pb(q[i]);
            if(q[i].x1 > mid && q[i].x2 > mid) qr.pb(q[i]);
        }
        work(xl,mid-1,yl,yr,ql);
        work(mid+1,xr,yl,yr,qr);
    }
    else{
        int mid = (yl+yr) >> 1;
        FOR(i,xl,xr){
            dij(i,mid,xl,xr,yl,yr);
            FOR(i,0,(int)q.size()-1){
                ans[q[i].id] = std::min(ans[q[i].id],dis[q[i].x1][q[i].y1]+dis[q[i].x2][q[i].y2]);
            }
        }
        FOR(i,0,(int)q.size()-1){
            if(q[i].y1 < mid && q[i].y2 < mid) ql.pb(q[i]);
            if(q[i].y1 > mid && q[i].y2 > mid) qr.pb(q[i]);
        }
        work(xl,xr,yl,mid-1,ql);
        work(xl,xr,mid+1,yr,qr);
    }
}

signed main(){
 //   freopen("6.in","r",stdin);
  //  freopen("6.out","w",stdout);
    read(n);read(m);
    r.resize(n+5);c.resize(n+5);dis.resize(n+5);vis.resize(n+5);
    FOR(i,1,n) r[i].resize(m+5),c[i].resize(m+5),dis[i].resize(m+5),vis[i].resize(m+5);
    FOR(i,1,n) FOR(j,1,m-1) read(r[i][j]);
    FOR(i,1,n-1) FOR(j,1,m) read(c[i][j]);
    int q;read(q);
    FOR(i,1,q){
        ans[i] = INT_MAX;
        int x1,y1,x2,y2;read(x1);read(y1);read(x2);read(y2);
        Q.pb(Query(x1,y1,x2,y2,i));
    }
    work(1,n,1,m,Q);
    FOR(i,1,q) printf("%d\n",ans[i]);
    return 0;
}
