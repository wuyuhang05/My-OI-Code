#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 1e5 + 5;
std::map<int,int> S;
int n,a[MAXN];

struct BIT{
    #define lowbit(x) ((x)&(-x))
    int tree[3*MAXN];
    
    inline void clear(){
        CLR(tree,0);
    }

    inline void add(int pos,int x){
        while(pos <= MAXN){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int calc(int pos){
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

int lu[MAXN],ld[MAXN],ru[MAXN],rd[MAXN];
int cnt1[MAXN],cnt2[MAXN];
// l:left r:right
// u:up   d:down

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),S.insert(MP(a[i],0));
    int sz = 0;
    for(std::map<int,int>::iterator it = S.begin();it != S.end();++it) 
        it->second = ++sz;
    FOR(i,1,n) a[i] = S[a[i]];
    FOR(i,1,n){
        lu[i] = bit.calc(a[i]-1);
        ld[i] = i-1-lu[i]-cnt1[a[i]];cnt1[a[i]]++;
        bit.add(a[i],1);
    }
    bit.clear();
    ROF(i,n,1){
        ru[i] = bit.calc(a[i]-1);
        rd[i] = n-i-ru[i]-cnt2[a[i]];cnt2[a[i]]++;
        bit.add(a[i],1);
    }
    LL sum1 = 0ll,sum2 = 0ll;
    FOR(i,1,n) sum1 += ru[i],sum2 += rd[i];
    LL ans = 1ll*sum1*sum2;
    FOR(i,1,n) ans -= 1ll*ru[i]*rd[i]; // a = c
    FOR(i,1,n) ans -= 1ll*ru[i]*lu[i]; // a = d
    FOR(i,1,n) ans -= 1ll*ld[i]*rd[i]; // b = c
    FOR(i,1,n) ans -= 1ll*ld[i]*lu[i]; // b = d
    printf("%lld\n",ans);
    return 0;
}
