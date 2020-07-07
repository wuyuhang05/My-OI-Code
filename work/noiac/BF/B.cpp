#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 5e5 + 5;
std::vector<int> G[MAXN];
int a[MAXN],p[MAXN],v[MAXN];
int n;
int id[MAXN],ans;

inline void work(){
    std::multiset<int> S;
    int now = 0;
    FOR(i,1,n){
        for(auto x:G[id[i]]) S.insert(x);
        if(S.empty()) return;
        if((*S.rbegin()) < p[id[i]]) S.erase(S.begin());
        else{
            now++;
            S.erase(S.lower_bound(p[id[i]]));
        }
    }
    ans = std::max(ans,now);
}
std::mt19937 g(time(NULL));
int main(){
    scanf("%d",&n);bool flag = 1;
    FOR(i,1,n) scanf("%d",a+i),flag &= a[i]==1;
    FOR(i,1,n) scanf("%d",p+i);
    FOR(i,1,n) scanf("%d",v+i);
    FOR(i,1,n) G[a[i]].pb(v[i]);
    if(flag){
        FOR(i,1,n) id[i] = i;
        work();
        printf("%d\n",ans);
        exit(0);
    }
    std::vector<int> ii;
    FOR(i,1,n) ii.pb(i);
    std::shuffle(all(ii),g);
    FOR(tt,1,std::min(n,100000000/n)){
        int i = ii[tt-1];
        int tot = 0;
        FOR(j,i,n) id[j] = ++tot;
        FOR(j,1,i-1) id[j] = ++tot;
        work();
    }
    printf("%d\n",ans);
    return 0;
}
