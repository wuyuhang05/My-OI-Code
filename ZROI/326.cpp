#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = (a);i <= (b);++i)
#define RFOR(i,a,b) for(R int i = (a);i >= (b);--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 
    #define ll long long 
    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline void read(int &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    inline void read(ll &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    #undef ll 
    #undef OUT_SIZE 
    #undef BUF_SIZE 
}; 
using namespace fastIO;

const int MAXN = 200 + 5;
int N,M;
int a[MAXN][MAXN],b[MAXN][MAXN];
bool inq[MAXN][MAXN];
LL dist[MAXN][MAXN];

inline int dis(std::pair<int,int> a,std::pair<int,int> b){
    return std::abs(a.first-b.first) + std::abs(a.second-b.second);
}

inline LL query(int sx,int sy,int fx,int fy){
    FOR(i,1,N) FOR(j,1,N) dist[i][j] = INT_MAX;
    dist[sx][sy] = 0;
    std::queue<std::pair<int,int> > q;
    q.push(std::make_pair(sx,sy));
    inq[sx][sy] = 1;
    while(!q.empty()){
        std::pair<int,int> v = q.front();q.pop();
        inq[v.first][v.second] = false;
        if(dist[v.first][v.second] + b[v.first][v.second] > dist[fx][fy]) continue;
        FOR(i,std::max(1,v.first-a[v.first][v.second]),std::min(N,v.first + a[v.first][v.second])){
            FOR(j,std::max(1,v.second - a[v.first][v.second]),std::min(M,v.second + a[v.first][v.second])){
                std::pair<int,int> t = std::make_pair(i,j);
                if(dis(v,t) <= a[v.first][v.second] && dist[t.first][t.second] > dist[v.first][v.second] + b[v.first][v.second]){
                    dist[t.first][t.second] = dist[v.first][v.second] + b[v.first][v.second];
                    if(!inq[t.first][t.second]){
                        q.push(t);
                        inq[t.first][t.second] = true;
                    }
                }
            }
        }
    }
    return dist[fx][fy];
}

int x[4],y[4];

int main(){
    read(N);read(M);
    FOR(i,1,N) FOR(j,1,M) read(a[i][j]);
    FOR(i,1,N) FOR(j,1,M) read(b[i][j]);
    FOR(i,1,3) read(x[i]),read(y[i]);
    LL ans1 = query(x[2],y[2],x[1],y[1]) + query(x[3],y[3],x[1],y[1]);
    LL ans2 = query(x[1],y[1],x[2],y[2]) + query(x[3],y[3],x[2],y[2]);
    LL ans3 = query(x[1],y[1],x[3],y[3]) + query(x[2],y[2],x[3],y[3]);
    LL ans = std::min(ans1,std::min(ans2,ans3));
    if(ans >= INT_MAX){
        puts("NO");
        return 0;
    }
    if(ans == ans1)
        puts("X");
    else if(ans == ans2)
        puts("Y");
    else if(ans == ans3)
        puts("Z");
    printf("%lld\n",ans);
    return 0;
}

