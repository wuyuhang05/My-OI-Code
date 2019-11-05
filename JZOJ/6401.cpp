/*
 * Author: RainAir
 * Time: 2019-11-02 08:38:52
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

int n,a[MAXN];
std::deque<int> ps[MAXN];
LL ans = 0;
int now = 1e9,l,r,mx;

inline bool gx(int ps){
    return std::min(ps-l,r-ps);
}

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void add(int pos,int x){
        while(pos < MAXN){
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

int main(){
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),ps[a[i]].pb(i),now = std::min(now,a[i]),mx = std::max(mx,a[i]);
    FOR(i,1,n) bit.add(i,1);
    l = 1,r = n;
    FOR(i,1,n){
        while(now <= mx && ps[now].empty()) ++now;
        if(ps[now].size() == 1){
            int x = ps[now].front(),p = bit.calc(x);
            if(p-l < r-p){
                ans += p-l;
                l++;
                bit.add(1,1);
                bit.add(x,-1);
            }
            else{
                ans += r-p;
                r--;
                bit.add(x+1,-1);
                bit.add(n+1,1);
            }
            ps[now].clear();
        }
        else{
            int x1 = ps[now].front(),x2 = ps[now].back();
            int p1 = bit.calc(x1),p2 = bit.calc(x2);
            bool flag = false;
            if(std::min(p1-l,r-p1) > std::min(p2-l,r-p2)) std::swap(x1,x2),std::swap(p1,p2),flag = true;
            if(p1-l < r-p1){
                ans += p1-l;
                l++;
                bit.add(1,1);
                bit.add(x1,-1);
            }
            else{
                ans += r-p1;
                r--;
                bit.add(x1+1,-1);
                bit.add(n+1,1);
            }
            if(flag) ps[now].pop_back();
            else ps[now].pop_front();
        }
    }
    printf("%lld\n",ans);
    return 0;
}
