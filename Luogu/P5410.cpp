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

const int MAXN = 2e7 + 5;
int z[MAXN],p[MAXN];
char a[MAXN],b[MAXN];

inline void Z(char str[],int z[]){
    int n = strlen(str+1);
    z[1] = n;int l = 0,r = 0;
    FOR(i,2,n){
        if(i < r) z[i] = std::min(z[i-l+1],r-i+1);
        while(i+z[i] <= n && str[i+z[i]]==str[z[i]+1]) ++z[i];
        if(i+z[i]-1 > r) r = i+z[i]-1,l = i;
    }
}

inline void work(char a[],char b[],int z[],int c[]){// get b's Z and res
    int n = strlen(a+1),m = strlen(b+1);Z(b,z);
    int l = 0,r = 0;
    FOR(i,1,n){
        if(i < r) c[i] = std::min(r-i+1,z[i-l+1]);
        while(i+c[i] <= n && c[i]+1 <= m && a[i+c[i]] == b[c[i]+1]) c[i]++;
        if(i+c[i]-1 > r) r = i+c[i]-1,l = i;
    }
}

int main(){
    scanf("%s%s",a+1,b+1);int m = strlen(b+1),n = strlen(a+1);
    work(a,b,z,p);
    LL ans = 0;
    FOR(i,1,m) ans ^= 1ll*i*(z[i]+1);
    printf("%lld\n",ans);ans = 0;
    FOR(i,1,n) ans ^= 1ll*i*(p[i]+1);
    printf("%lld\n",ans);
    return 0;
}
