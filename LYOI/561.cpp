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

const int MAXN = 1000000 + 5;
const int MAXV = 5000000 + 5;

bool vis[MAXV],in[MAXN];
int prime[MAXV],cnt;
int d[MAXV];

inline void pre(){
    vis[0] = vis[1] = true;
    FOR(i,2,MAXV){
        if(!vis[i]) prime[++cnt] = i,d[i] = i;
        for(int j = 1;j <= cnt && 1ll * i * prime[j] <= MAXV;j++){
            vis[i*prime[j]] = 1;
            d[i*prime[j]] = prime[j];
            if(!(i%prime[j])) break;
        }
    }
}

int N,M;
int a[MAXN];
int p[MAXN],tail;
int num[MAXN];

int main(){
    freopen("disease.in","r",stdin);
    freopen("disease.out","w",stdout);
    read(N);read(M);
    FOR(i,1,N) read(a[i]);
    pre();int ans = 0;
    while(M--){
        int x;read(x);
        int w = a[x],v;tail = 0;
        while(d[w] > 1){
            p[tail++] = v = d[w];
            while(!(w % v)) w /= v;
        }
        if(in[x]){
            FOR(S,0,(1 << tail)-1){
                int cnt = 0,res = 1;
                FOR(i,0,tail-1){
                    if(S & (1 << i)){
                        cnt++;res *= p[i];
                    }
                }
                num[res]--;
                ans += (cnt & 1) ? num[res] : -num[res];
               //DEBUG(ans);
            }
        }
        else{
            FOR(S,0,(1 << tail)-1){
                int cnt = 0,res = 1;
                FOR(i,0,tail-1){
                    if((1 << i) & S){
                        cnt++;res *= p[i];
                    }
                }
                ans += (cnt & 1) ? -num[res] : num[res];
                num[res]++;
            }
        }
        in[x]^=1;
        printf("%d\n",ans);
    }
    return 0;
}
/*
5 6
1 2 3 4 6
1
2
3
4
5
1
*/