/*
 * Author: RainAir
 * Time: 2019-10-26 15:34:45
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

const int MAXN = 3000+5;
int n;
P a[MAXN],b[MAXN];
bool useda[MAXN],usedb[MAXN];
int ta[MAXN];
int ans[MAXN],id[MAXN];

inline int calc(){
    std::stack<int> st;
    int tp = 1,end = n,res = 0;
    FOR(i,1,n){
        if(usedb[b[i].se]) continue;
        while(tp <= n && a[tp].fi < b[i].fi){
            if(!useda[a[tp].se]) st.push(a[tp].se);
            ++tp;
        }
        if(st.empty()){
            while(useda[a[end].se]) end--;
            ans[a[end--].se] = b[i].fi;
        }
        else ans[st.top()] = b[i].fi,st.pop(),++res;
    }
    return res;
}

int base;
int tb[MAXN];

inline bool cmp(int x,int y){
    return tb[x] < tb[y];
}

int ttt[MAXN];

inline void work(){
    std::vector<int> S;
//    DEBUG(ta[45]);
    int now = 0;
    FOR(i,1,n){
        useda[i] = true;
  //      FOR(i,1,n) printf("%d ",usedb[i]);puts("");
        S.clear();S.pb(0);
        FOR(j,1,n) if(!usedb[j]) S.pb(j);
        std::sort(all(S),cmp);
        int l = 1,r = (int)S.size()-1,ans,ps = 0;
        FOR(j,1,r){
            ps = j;
            if(tb[S[j]] > ta[i]) break;
        }
        l = ps;ans = -1;
        if(tb[S[l]] <= ta[i]) ++l;
        while(l <= r){
            int mid = (l + r) >> 1;
            usedb[S[mid]] = true;
            int gx = calc()+now+1;
            if(gx == base) ans = mid,l = mid + 1;
            else r = mid-1;
            usedb[S[mid]] = false;
        }
        if(ans != -1){
            usedb[S[ans]] = true;
            ttt[i] = tb[S[ans]];
            now++;
            continue;
        }
        l = 1,r = ps;
        while(l <= r){
            int mid = (l + r) >> 1;
            usedb[S[mid]] = true;
            int gx = calc()+now;
            if(gx == base) ans = mid,l = mid+1;
            else r = mid-1;
            usedb[S[mid]] = false;
        }
        usedb[S[ans]] = true;
        ttt[i] = tb[S[ans]];
    }
}

int main(){
    freopen("card.in","r",stdin);
    freopen("card.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i].fi),a[i].se = i,ta[i] = a[i].fi;
    FOR(i,1,n) scanf("%d",&b[i].fi),b[i].se = i,tb[i] = b[i].fi;
    std::sort(a+1,a+n+1);std::sort(b+1,b+n+1);
    base = calc();
//    DEBUG(base);
    work();
    FOR(i,1,n) printf("%d ",ttt[i]);
    return 0;
}
