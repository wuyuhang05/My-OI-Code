/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-16 10:52:50
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
int a[MAXN],b[MAXN],n;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN<<1];

    inline void clear(){
        CLR(tree,0);
    }

    inline void add(int pos,int d){
        while(pos <= n+233){
            tree[pos] += d;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

inline bool chk(int k){
    b[0] = 0;
    FOR(i,1,n) b[i] = a[i]<k ? -1 : 1;
    int mn = 0;LL ans = 0;
    FOR(i,1,n) b[i] += b[i-1],mn = std::min(mn,b[i]);// 0~n+1
    mn = -mn;++mn;
    FOR(i,0,n) b[i] += mn;
    bit.clear();bit.add(b[0],1);
    FOR(i,1,n){
        ans += bit.query(b[i]);
        bit.add(b[i],1);
    }
 //   DEBUG(4ll*ans);DEBUG(1ll*n*(n-1));
    return 4*ans >= 1ll*n*(n+1);
}

int main(){
   // freopen("a.in","r",stdin);
    scanf("%d",&n);
    int l = 1e9,r = 0;
    FOR(i,1,n) scanf("%d",a+i),l = std::min(l,a[i]),r = std::max(r,a[i]);
    int ans = -1;
//    DEBUG(chk(1));
//    return 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    printf("%d\n",ans);
    return 0;
}

