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

const int MAXN = 200+5;

int n,m;
P c[MAXN];
std::vector<P> a,b;
int f[MAXN][MAXN];
int sm[MAXN];
bool used[MAXN];

inline bool cmp(P x,P y){
    return x.se-x.fi > y.se-y.fi;
}

int main(){
    freopen("factory.in","r",stdin);
    freopen("factory.out","w",stdout);
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d%d",&c[i].fi,&c[i].se);
    FOR(i,1,n){
        bool flag = 1;
        FOR(j,1,n) if(i != j && c[i].fi <= c[j].fi && c[j].se <= c[i].se && !used[j]) {flag = 0;break;}
        if(flag) a.pb(c[i]);
        else b.pb(c[i]),used[i] = 1;
    }
    std::sort(all(a));std::sort(all(b),cmp);
    CLR(f,-0x3f);f[0][0] = 0;
    FOR(i,1,(int)a.size()){
        FOR(j,1,std::min(i,m)){
            FOR(k,1,i){
                if(a[k-1].se <= a[i-1].fi) continue;
                f[i][j] = std::max(f[i][j],f[k-1][j-1]+a[k-1].se-a[i-1].fi);
            }
        }
    }
    int ans = 0;
    FOR(i,1,(int)b.size()) sm[i] = sm[i-1]+(b[i-1].se-b[i-1].fi);
    FOR(i,0,m) ans = std::max(ans,f[(int)a.size()][i]+sm[m-i]);
    printf("%d\n",ans);
    return 0;
}
