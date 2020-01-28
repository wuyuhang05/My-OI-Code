#include <unordered_map>
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
int n,a[MAXN];

struct Seg{
    int l,r,id;

    inline bool operator < (const Seg &t) const {
        return r == t.r ? l > t.l : r < t.r;
    }
}p[MAXN];

std::set<int> S;
std::unordered_map<int,std::stack<int> > SS;
int ans[MAXN];

inline bool cmp(const P &a,const P &b){
    return a.se == b.se ? a.fi < b.fi : a.se < b.se;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),SS[a[i]].push(i);
    FOR(i,1,n) scanf("%d%d",&p[i].l,&p[i].r),p[i].id = i;
    std::sort(a+1,a+n+1);std::sort(p+1,p+n+1);
    int ps = 0;bool flag = false;
    FOR(i,1,n){
        while(ps < n && a[ps+1] <= p[i].r) S.insert(a[++ps]);
        auto t = S.lower_bound(p[i].l);
        if(t == S.end()){
            puts("Let's search for another office.");
            return 0;
        }
        ans[p[i].id] = *t;auto tt = t;
        t++;if(t != S.end() && *t <= p[i].r){
            flag = true;
        }S.erase(tt);
    }
    if(flag){
        puts("Ask Shiftman for help.");return 0;
    }
    puts("Perfect!");
    FOR(i,1,n) printf("%d ",SS[ans[i]].top()),SS[ans[i]].pop();
    return 0;
}
