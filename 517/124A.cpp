/*
 * Time: 2019-11-11 20:44:11
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void add(int pos,int x){
        pos++;
        while(pos < MAXN){
            tree[pos] += x;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        pos++;
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
}bit;

std::vector<P> G[MAXN];
int cnt = 0;

int main(){
    int n,m;scanf("%d%d",&n,&m);
    cnt = n;
    FOR(i,1,n){
        int l,r;scanf("%d%d",&l,&r);
        G[r-l+1].pb(MP(l,r));
    }
    FOR(i,1,m){
        int ans = cnt;
        for(int ps = 0;ps <= m;ps += i)
            ans += bit.query(ps);
        FOR(j,0,(int)G[i].size()-1)
            bit.add(G[i][j].fi,1),bit.add(G[i][j].se+1,-1),--cnt;
        printf("%d\n",ans);
    }
    return 0;
}
