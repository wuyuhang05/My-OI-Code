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
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
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

const int MAXN = 10 + 5;

struct Node{
    int du,pos;

    bool operator < (const Node &other) const {
        return du > other.du;
    }
}frog[MAXN];

int map[MAXN][MAXN];

inline void solve(){
    int N;read(N);
    FOR(i,1,N){
        read(frog[i].du);
        frog[i].pos = i;
    }
    CLR(map,0);
    FOR(i,1,N){
        std::sort(frog + i,frog + N + 1);
        if(frog[i].du > N-i+1){
            puts("NO");
            return;
        }
        FOR(j,i+1,i+frog[i].du){
            if(!frog[j].du){
                puts("NO");
                return;
            }
            frog[j].du--;
            map[frog[i].pos][frog[j].pos] = map[frog[j].pos][frog[i].pos] = 1;
        }
        frog[i].du = 0;
    }
    puts("YES");
    FOR(i,1,N){
        FOR(j,1,N){
            printf("%d ",map[i][j]);
        }
        puts("");
    }
}

int main(){
    int T;read(T);
    while(T--){
        solve();
        puts("");
    }
    return 0;
}