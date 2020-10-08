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
int a[MAXN],n,b[MAXN];

int main(){
    scanf("%d",&n);
    long double a=0,b=0;
    FOR(i,1,n) a += log(i);
    ROF(i,n,1){
        b += log(i);
        a -= log(i);
        if(a < b){
            printf("%d\n",i);
            break;
        }
    }
    return 0;
}