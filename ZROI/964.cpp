/*
 * Author: RainAir
 * Time: 2019-09-21 19:30:43
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

const int MAXN = 3e6 + 5;
const int MAXM = 1e6 + 5;
int n,a[MAXN];
bool p[MAXM],vis[MAXM];
int prime[MAXM],cnt,mx;

inline void prework(){
    FOR(i,2,MAXM){
        if(!p[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXM;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])) break;
        }
    }
}

struct Node{
    int l,r,len;
    Node(int l=0,int r=0) : l(l),r(r) {len = r-l;};

    bool operator < (const Node &t) const {
        if(len != t.len) return len < t.len;
        return l > t.l;
    }
}ans;

int lim,b[MAXN],sm[MAXN],S[MAXN];
std::vector<int> dec[MAXM];
/*
struct BIT{
    #define lowbit(x) ((x)&(-x))
    int tree[MAXN];
    BIT(){CLR(tree,0);}

    inline void add(int x,int d){
        while(x <= lim+233){
            tree[x] = std::max(tree[x],d);
            x += lowbit(x);
        }
    }

    inline void repair(int x){
        while(x <= lim+233){
            tree[x] = 0;
            x += lowbit(x);
        }
    }

    inline int query(int x){
        int ans = 0;
        while(x){
            ans = std::max(ans,tree[x]);
            x -= lowbit(x);
        }
        return ans;
    }
}bit;

inline int calc(int d,int l,int r){
    if(l > r) return 0;
    if(dec[d][0] > r) return 0;
    if(dec[d][(int)dec[d].size()-1] < l) return 0;
    return std::upper_bound(all(dec[d]),r)-std::lower_bound(all(dec[d]),l);
}

inline Node Solve(int d){//l = 22 tl = 8
 //   DEBUG(a[21]);
    lim = ::n-dec[d][0]+1;int n = dec[d].size();
//    for(auto x:dec[d]) DEBUG(x);
    FOR(i,1,n) sm[i] = 2*i+::n-dec[d][i-1],lim = std::max(lim,sm[i]);//,DEBUG(sm[i]);
    DEBUG(lim-sm[7]+1);
 //   FOR(i,1,n) if(lim-sm[i]+1 <= 6) DEBUG(dec[d][i-1]);
    FOR(i,1,n) bit.add(lim-sm[i]+1,i);
    DEBUG(dec[d][bit.query(6)-1]);
    Node res;
    sm[0] = ::n-dec[d][0]+1;
    FOR(i,1,n){
        int j = bit.query(lim-sm[i-1]+1);
        if(i > j) continue;
        int l = dec[d][i-1],r = dec[d][j-1];
        int rem = 2*(j-i+1)-(r-l+1);
//        if(j-i+1 == 16) DEBUG(r-l+1);
  //      if(l-rem > 0) l -= rem,rem = 0;
   //     else rem -= l-1,l = 1;
        if(i == 9) DEBUG(l),DEBUG(r),DEBUG(calc(d,23,23)),DEBUG(rem);
        while(rem && l > 1){
            if(l-rem > 0){
                int t = l;
                l -= rem;rem = calc(d,l,t-1);
                if(i == 9) DEBUG(l),DEBUG(rem),DEBUG(t-1);
            }//[l-rem,l]
            else rem += 2*calc(d,1,l-1)-(l-1),l = 1;
        }
        while(rem && r < n){
            int t = r;r += rem;
            rem = calc(d,t+1,r);
        }
        r = std::min(::n,r);
//        r = std::min(::n,r+rem);
//        if(r < l) continue;
        if(res < Node(l,r)) res = Node(l,r);
    }
    FOR(i,1,n) bit.repair(lim-sm[i]+1);
    FOR(i,0,n) sm[i] = 0;
    return res;
}
*/

inline Node Solve(int d){
    std::vector<P> G;
    FOR(i,1,dec[d].size()) G.pb(MP(dec[d][i-1]-2*i,i));
    std::sort(all(G));Node ans;int mx=0;
    for(int l = 0,r = 0;l < G.size();++l){
        for(;r < G.size() && G[r].fi <= G[l].fi+1;++r) mx = std::max(mx,G[r].se);
        int cnt = mx-G[l].se+1;
//        DEBUG(mx);DEBUG(cnt);
        int ll = dec[d][G[l].se-1],rr = dec[d][mx-1];
        ll -= cnt*2-(rr-ll+1);ll = std::max(ll,1);
        rr += cnt*2-(rr-ll+1);rr = std::min(rr,n);
        if(ans < Node(ll,rr)) ans = Node(ll,rr);
    }
    return ans;
}

inline void fg(int ps,int x){
    int q = std::sqrt(1.0*x);
    FOR(i,1,cnt){
        if(prime[i] > q) break;
        if(x == 1) break;
        if(x%prime[i]) continue;
        vis[prime[i]] = true;dec[prime[i]].pb(ps);
        while(!(x%prime[i])) x /= prime[i];
    }
    if(x != 1) dec[x].pb(ps);
}

int main(){
  //  freopen("b.in","r",stdin);
    prework();
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),mx = std::max(mx,a[i]);
    FOR(i,1,n) fg(i,a[i]);
//    DEBUG(Solve(17).len);return 0;
//    DEBUG(Solve(2).len);
//    return 0;
   // DEBUG(Solve(2).len);return 0;
    FOR(i,2,mx){
        if(!dec[i].size()) continue;
//        DEBUG(dec[i].size());
        Node t = Solve(i);
        if(ans < t) ans = t;
    }
    printf("%d %d\n",ans.l,ans.r);
    return 0;
}

