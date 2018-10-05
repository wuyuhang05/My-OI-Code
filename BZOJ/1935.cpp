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

const int MAXN = 500000 + 5;

int N,M;

struct Point{
    int x,y,opt,pos;

    bool operator < (const Point &other) const {
        return x < other.x || x == other.x && y < other.y || x == other.x && y == other.y && !opt;
    }
}p[MAXN<<3],*last = p;
int size;

inline void *New(int x,int y,int opt=0,int pos=0){
    ++size;
    Point *ret = ++last;
    last->x = x;last->y = y;
    last->pos = pos;last->opt = opt;
}

// Bit Tree

int tree[MAXN << 2],maxy;
#define lowbit(x) x&-x

inline void add(int pos,int delta){
    while(pos <= maxy+1){
        tree[pos] += delta;
        pos += lowbit(pos);
    }
}

inline int calc(int pos){
    int ret = 0;
    while(pos){
        ret += tree[pos];
        pos -= lowbit(pos);
    }
    return ret;
}
#undef lowbit

int ans[MAXN];

int main(){
    read(N);read(M);
    FOR(i,1,N){
        int x,y;
        read(x);read(y);
        x++;y++;
        New(x,y);
        maxy = std::max(maxy,y);
    }
    FOR(i,1,M){
        int a,b,c,d;
        read(a);read(b);read(c);read(d);
        New(a,b,1,i);
        New(c+1,d+1,1,i);
        New(a,d+1,-1,i);
        New(c+1,b,-1,i);
        // F(c,d) - F(a,c) - F(b,c) + F(a,b)
    }
    std::sort(p + 1,p + size + 1);
    FOR(i,1,size){
        if(!p[i].opt)
            add(p[i].y,1);
        else ans[p[i].pos] += p[i].opt * calc(p[i].y);
    }
    FOR(i,1,M) printf("%d%c",ans[i],'\n');
    return 0;
}