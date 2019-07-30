/*
 * Author: RainAir
 * Time: 2019-07-17 08:47:03
 * -1s-1s-1s-1s-1s-1s-1s-1s-1s-1s-1s-1s-1s-1s!!!!!!!
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")



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

const int MAXN = 2000+5;
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
#define SIZE 100000
inline char nc(){
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

int col[MAXN][MAXN],n,m,sx,sy;
int dis[MAXN][MAXN];

struct Node{
    int x,y,dis,col;
    Node(){}
    Node(int x,int y,int dis,int col) : x(x),y(y),dis(dis),col(col) {}
    
    bool operator < (const Node &t) const {
        return dis > t.dis;
    }
};

inline void bfs(){
    std::priority_queue<Node> q;q.push(Node(sx,sy,0,col[sx][sy]));dis[sx][sy] = 0;
    while(!q.empty()){
        Node v = q.top();q.pop();
        int x = v.x,y = v.y,c = v.col;
        FOR(i,0,3){
            int xx = x + dx[i],yy = y+dy[i];
            if(xx >= 1 && xx <= n && yy >= 1 && yy <= m){
                int gx = col[xx][yy] != col[x][y];
                //DEBUG(x);DEBUG(y);DEBUG(xx);DEBUG(yy);DEBUG(gx);
                if(dis[xx][yy] > dis[x][y] + gx){
                    dis[xx][yy] = dis[x][y] + gx;
                    q.push(Node(xx,yy,dis[xx][yy],col[xx][yy]));
                }
            }
        }
    }
}

int main(){
 //   freopen("data.in","r",stdin);
   // freopen("a.out","w",stdout);
    read(n);read(m);read(sx);read(sy);
    FOR(i,1,n) FOR(j,1,m) read(col[i][j]),dis[i][j] = 1e9;
    bfs();
    FOR(i,1,n){
        FOR(j,1,m) printf("%d%c",dis[i][j],(j == m) ? '\n' : ' ');
    }
    return 0;
}

