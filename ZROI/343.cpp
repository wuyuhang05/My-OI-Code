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
const int MAXN = 2000 + 5;
int N;

struct Point{
    LL x,y;
}p[MAXN];

struct Matrix{
    Point min,max;
    int imp,pos;
    bool vis;
    bool operator < (const Matrix &other) const {
        return imp > other.imp;
    }
}a[MAXN];

inline LL jiao(const Matrix &a,const Matrix &b){
    Matrix ret;
    ret.min.x = std::max(a.min.x,b.min.x);
    ret.min.y = std::max(a.min.y,b.min.y);
    ret.max.x = std::min(a.max.x,b.max.x);
    ret.max.y = std::min(a.max.y,b.max.y);
    if(ret.min.x < ret.max.x && ret.min.y < ret.max.y){
        return (ret.max.x - ret.min.x) * (ret.max.y - ret.min.y);
    }
    else return -1ll;
}

inline LL get(const Matrix &a,const Matrix &b,LL jj){
    // DEBUG(jj);
    return (a.max.x-a.min.x)*(a.max.y-a.min.y) + (b.max.x-b.min.x) * (b.max.y-b.min.y) - jj;
}

int cnt = 0;
int ans[MAXN],top = 0;

int main(){
    read(N);
    FOR(i,1,N){
        int ii;
        read(ii);
        int x,y,w,h;
        read(x);read(y);read(w);read(h);
        if(ii < 600000) continue;
        a[++cnt] = (Matrix){(Point){x-w,y-h},(Point){x+w,y+h},ii,i,false};
    }
    std::sort(a + 1,a + cnt + 1);// DEBUG(cnt);
    FOR(i,1,cnt){
        // DEBUG(a[i].pos);
        // DEBUG(a[i].min.x);DEBUG(a[i].min.y);DEBUG(a[i].max.x);DEBUG(a[i].max.y);
        if(a[i].vis) continue;
        ans[++top] = a[i].pos;
        FOR(j,i+1,cnt){
            LL ji = jiao(a[i],a[j]);
            if(ji == -1) continue;
            LL ans = get(a[i],a[j],ji);// DEBUG(i);DEBUG(j);DEBUG(ji);DEBUG(ans);
            if(ji * 2ll > ans) a[j].vis = true;
        }
    }// system("Sleep 1");
    std::sort(ans + 1,ans + top + 1);
    FOR(i,1,top){
        printf("%d%c",ans[i],(i == top) ? '\n' : ' ');
    }
    return 0;
}
