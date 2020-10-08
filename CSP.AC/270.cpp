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

const int MAXN = 1e6 + 5;
int n;
int a[MAXN<<1];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) a[i] = i;
    FOR(i,2,n){
        int t = 0;
        for(int j = i-1;j <= i-1+n-1;j += i){
            std::swap(t,a[j]);
        }
        std::swap(t,a[i-1+n]);
    }
    FOR(i,n,n+n-1) printf("%d ",a[i]);puts("");
    return 0;
}
