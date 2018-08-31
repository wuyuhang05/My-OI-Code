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
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50000 + 5;

int N,M,x;

struct BIT{
    #define lowbit(x) x&-x
    LL tree[MAXN];
    
    inline void clear(){
        CLR(tree,0);
    }
    
    inline void add(int pos,int x){
        while(pos <= N){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline LL query(int pos){
        LL ret = 0;
        while(pos){
            ret += tree[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
    #undef lowbit
}bit;

LL sum[MAXN],a[MAXN],origin[MAXN];
std::map<LL,int> S;

inline void Solve(int k){
    S.clear();
    FOR(i,0,N){
        a[i] = sum[i] - (LL)i*k;
        S.insert(std::make_pair(a[i],0));
    }
    bit.clear();
    int tN = 0;
    for(std::map<LL,int>::iterator it = S.begin();it != S.end();it++){
        it->second = ++tN;
        origin[tN] = it->first;
    }
    FOR(i,0,N) a[i] = S[a[i]];
    LL ans = 0;
    FOR(i,0,N){
        // DEBUG(a[i]);
        // DEBUG(ans);DEBUG(i);
        bit.add(a[i],1);
        ans += i-bit.query(a[i]-1);
    }
    printf("%lld\n",ans);
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d",&x);
        sum[i] = sum[i-1]+x;
    }
    scanf("%d",&M);
    FOR(i,1,M){
        int k;scanf("%d",&k);
        Solve(k);
    }
    return 0;
}
