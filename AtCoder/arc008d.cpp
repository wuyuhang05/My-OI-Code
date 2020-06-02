#include<bits/stdc++.h>

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

const int MAXN = 5e5 + 5;
int ans[MAXN];
P a[MAXN];
int n;
std::set<int> S;

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i].fi),a[i].se = i;
    std::sort(a+1,a+n+1);
    FOR(i,1,n*n) S.insert(i);
    FOR(i,1,n){
        S.erase(a[i].fi);ans[a[i].fi] = a[i].se;
        FOR(j,2,a[i].se){
            if(*S.begin() > a[i].fi){
                puts("No");
                return 0;
            }
            ans[*S.begin()] = a[i].se;
            S.erase(S.begin());
        }
    }
    ROF(i,n,1){
        FOR(j,1,n-a[i].se){
            auto t = S.end();t--;
            if(*t < a[i].fi){
                puts("No");
                return 0;
            }
            ans[*t] = a[i].se;
            S.erase(t);
        }
    }
    puts("Yes");
    FOR(i,1,n*n) printf("%d ",ans[i]);puts("");
    return 0;
}
