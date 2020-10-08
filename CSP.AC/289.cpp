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

const int MAXN = 2e5 + 5;
int n,a[MAXN],b[MAXN],k;

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",a+i),b[a[i]]++;
    int t = 0;FOR(i,1,n) t += (b[i] != 0);
    std::sort(b+1,b+n+1);
    int ans = 0;
    FOR(i,1,n){
        if(t <= k) break;
        if(!b[i]) continue;
        ans +=  b[i];t--;
    }
    printf("%d\n",ans);
    return 0;
}
