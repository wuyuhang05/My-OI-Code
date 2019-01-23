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

const int MAXN = 1000000 + 5;
const int MAXV = 5000000 + 5;

bool vis[MAXV],in[MAXN];
int prime[MAXV],cnt;
int d[MAXV];
int N;
int p[MAXN],tail;
int num[MAXN];

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

int main(){
    pre();
    scanf("%d",&N);DEBUG(N);int ans = 0;
    while(N--){
        int opt,x;scanf("%d%d",&opt,&x);
        //DEBUG(opt);DEBUG(x);DEBUG(N);
        if((opt == 1 && in[x]) || (opt == 2 && !in[x])) continue;
        if(opt == 3){
            printf("Ans: %d\n",ans);
            continue;
        }
        int w = x,v;tail = 0;
        while(d[w] > 1){
            p[tail++] = v = d[w];
            while(!(w % v)) w /= v;
        }
        if(opt == 2){
            DEBUG((1<<tail)-1);
            FOR(S,0,(1 << tail)-1){
                int cnt = 0,res = 1;
                FOR(i,0,tail-1){
                    if(S & (1 << i)){
                        cnt++;res *= p[i];
                    }
                }
                num[res]--;//DEBUG(cnt);DEBUG(num[res]);DEBUG(-num[res]);
                ans += (cnt & 1) ? num[res] : -num[res];
                //DEBUG(num);
                //DEBUG(ans);
            }
        }
        else if(opt == 1){
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
    }
    return 0;
}