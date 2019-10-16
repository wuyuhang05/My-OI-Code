//#include <unordered_map>
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
#define P std::pair<LL,LL>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 40;
LL a[MAXN];
int n,mid;
LL ans,cnt;
//std::unordered_map<int,int> s;
std::map<LL,LL> s;
std::vector<LL> v;

inline void dfs1(int step,P state){
    if(step == mid + 1){
        if(!state.fi) return;
        if(!s[state.se]) s[state.se] = state.fi,v.pb(state.se);
        else s[state.se] = std::min(s[state.se],state.fi);
        return;
    }
    dfs1(step+1,MP(state.fi+1,state.se+a[step]));
    dfs1(step+1,state);
}

LL mabs(LL x){
    return x < 0ll ? -x : x;
}

inline void upd(LL &a,LL &b,P state,int x){
    if(mabs(a) > mabs(state.se+v[x]) || (mabs(a) == mabs(state.se+v[x]) && b > state.fi+s[v[x]])){
        a = state.se+v[x];
        b = state.fi+s[v[x]];
    }
}

inline void dfs2(int step,P state){
    if(step == n + 1){
        if(state.fi){
            if(mabs(ans) > mabs(state.se) || (mabs(ans) == mabs(state.se) && cnt > state.fi)){
                ans = state.se;cnt = state.fi;
                //return;
            }
        }
        int x = std::lower_bound(all(v),-state.se)-v.begin();
        LL a = LLONG_MAX,b = LLONG_MAX;
        if(x < v.size()) upd(a,b,state,x);
        if(x+1 < v.size()) upd(a,b,state,x+1);
        if(x-1 >= 0) upd(a,b,state,x-1);
        if(mabs(ans) > mabs(a) || (mabs(ans) == mabs(a) && cnt > b)){
            ans = a;cnt = b;
        }
        return;
    }
    dfs2(step+1,MP(state.fi+1,state.se+a[step]));
    dfs2(step+1,state);
}

inline void Solve(){
    FOR(i,1,n) scanf("%lld",&a[i]);
    if(n == 1){
        printf("%lld %lld\n",mabs(a[1]),1ll);
        return;
    }
    ans = cnt = LLONG_MAX;mid = n>>1;
    s.clear();v.clear();dfs1(1,MP(0ll,0ll));
    FOR(i,0,(int)v.size()-1){
        LL x = v[i];
        if(mabs(ans) > x || (mabs(ans) == x && s[ans] < cnt)){
            ans = x;cnt = s[x];
        }
    }
    std::sort(all(v));dfs2(mid+1,MP(0ll,0ll));
    printf("%lld %lld\n",mabs(ans),cnt);
}

int main(){
    while(true){
        scanf("%d",&n);if(!n) return 0;
        Solve();
    }
    return 0;
}
