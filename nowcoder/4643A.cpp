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

const int MAXN = 1e5 + 5;
double x[MAXN],y[MAXN];
int n,r;
#define pw(x) ((x)*(x))

int main(){
    scanf("%d%d",&n,&r);
    FOR(i,1,n) scanf("%lf%lf",x+i,y+i);
    x[n+1] = x[1];y[n+1] = y[1];
    double ans = 0;
    FOR(i,2,n){
        double r1 = std::sqrt(pw(x[i]-x[1])+pw(y[i]-y[1]));
        double a = std::sqrt(pw(x[i]-x[i-1])+pw(y[i]-y[i-1]));
        double b = std::sqrt(pw(x[i]-x[i+1])+pw(y[i]-y[i+1]));
        double c = std::sqrt(pw(x[i+1]-x[i-1])+pw(y[i+1]-y[i-1]));
        double deg = acos(a/(2.0*r))+acos(b/(2.0*r))-acos((-pw(c)+pw(a)+pw(b))/(2.0*a*b));
        ans += r1*deg;
    }
    printf("%.20lf\n",ans);
    return 0;
}
