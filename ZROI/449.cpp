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

#define P std::pair<LL,LL>
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

const int MAXN = 60 + 5;
const int ha = 1000000000 + 7;
#define int LL
std::map<P,int> f[MAXN];
LL size[MAXN],a[MAXN],b[MAXN],len[MAXN],c[MAXN],d[MAXN],S[MAXN];
LL ans[MAXN];

int queryDis(int k,LL u,LL v){
    if(!k || u==v) return 0ll;
    if(u > v) std::swap(u,v);
    if(u < S[a[k]] && v < S[a[k]]) return queryDis(a[k],u,v);
    if(u >= S[a[k]] && v >= S[a[k]]) return queryDis(b[k],u-S[a[k]],v-S[a[k]]);
    v -= S[a[k]];
    P now(u,v);
    if(f[k].count(now)) return f[k][now];
    int ans = len[k];
    ans = (ans + queryDis(a[k],u,c[k]))%ha;
    ans = (ans + queryDis(b[k],d[k],v))%ha;
    return f[k][now] = ans;
}

int querySum(int k,LL root){
    if(!k) return 0ll;
    P now(root,-1);
    if(f[k].count(now)) return f[k][now];
    int ans = 0;
    if(root < S[a[k]]){
        ans = (ans + querySum(a[k],root))%ha;
        ans = (ans + querySum(b[k],d[k]))%ha;
        ans = (ans + 1ll*size[b[k]]*(len[k]+queryDis(a[k],root,c[k]))%ha);
    }
    else{
        root -= S[a[k]];
        ans = (ans + querySum(b[k],root));
        ans = (ans + querySum(a[k],c[k]));
        ans = (ans + 1ll*size[a[k]]%ha*(len[k]+queryDis(b[k],root,d[k]))%ha)%ha;
    }
    return f[k][now] = ans;
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--){
        int N;scanf("%lld",&N);
        S[0] = size[0] = 1;f[0].clear();
        FOR(i,1,N){
            scanf("%lld%lld%lld%lld%lld",a+i,b+i,c+i,d+i,len+i);
            S[i] = S[a[i]]+S[b[i]];f[i].clear();
            size[i] = S[i]%ha;
        }
        FOR(i,1,N){
            ans[i] = ans[a[i]];
            ans[i] = (ans[i] + ans[b[i]])%ha;
            ans[i] = (ans[i] + querySum(a[i],c[i])*size[b[i]]%ha)%ha;
            ans[i] = (ans[i] + querySum(b[i],d[i])*size[a[i]]%ha)%ha;
            ans[i] = (ans[i] + len[i]*size[a[i]]%ha*size[b[i]]%ha)%ha;
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}
/*
1
2
0 0 0 0 2
1 1 0 0 4
*/