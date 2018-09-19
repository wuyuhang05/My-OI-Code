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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
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

const int MAXN = 1000 + 5;

struct Edge{
    int u,v;
    double w;

    bool operator < (const Edge &other) const {
        return w < other.w;
    }
}e[MAXN*MAXN];

std::pair<int,int> a[MAXN];
int N,L,cnt;
int fa[MAXN];

inline double dist(int i,int j){
    return std::sqrt(((double)(a[i].first-a[j].first)*(a[i].first-a[j].first) + (double)(a[i].second-a[j].second) * (a[i].second-a[j].second)));
}

inline void init(){
    FOR(i,1,N+1) fa[i] = i;
    FOR(i,1,N){
        FOR(j,i+1,N){
            e[++cnt] = (Edge){i,j,dist(i,j)};
        }
    }
    FOR(i,1,N){
        e[++cnt] = (Edge){0,i,a[i].second};
        e[++cnt] = (Edge){i,N+1,L-a[i].second};
    }
    e[++cnt] = (Edge){0,N+1,L};
}

inline int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

inline void Kruskal(){
    std::sort(e+1,e+cnt+1);
    FOR(i,1,cnt){
        int fx = find(e[i].u),fy=find(e[i].v);
        fa[fy] = fx;
        if(find(0) == find(N+1)){
            printf("%.3f\n",e[i].w);
            return;
        }
    }
}

int main(){
    read(N);read(L);
    FOR(i,1,N){
        read(a[i].first);read(a[i].second);
    }
    init();
    Kruskal();
    return 0;
}
