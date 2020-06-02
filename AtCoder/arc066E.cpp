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

const int MAXN = 2e5 + 5;

int a[MAXN],opt[MAXN],n;
LL suf[MAXN],sm[MAXN];

int main(){
    scanf("%d%d",&n,a+1);opt[1] = 1;
    FOR(i,2,n){
        char str[3];scanf("%s",str);
        opt[i] = str[0]=='-'?-1:1;
        scanf("%d",a+i);
    }
    FOR(i,1,n) sm[i] = sm[i-1]+a[i];
    int lst = n;
    ROF(i,n,1){
        suf[i] = sm[lst]-sm[i];
        if(opt[i+1] == -1) lst = i;
    }
//    FOR(i,1,n) DEBUG(suf[i]);
    LL ans = a[1],pre = 0;
    FOR(i,2,n) ans += a[i]*opt[i];
    FOR(i,1,n-1){
        pre += opt[i]*a[i];
        if(opt[i+1] == 1) continue;
        else ans = std::max(ans,pre+sm[n]-sm[i]-2*suf[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
