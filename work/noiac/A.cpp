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

const int MAXN = 2e5 + 5;
const double EPS = 1e-10;
int a[MAXN],n,L,R;
int x[MAXN],y[MAXN];

inline int sgn(double x){
    if(std::fabs(x) <= EPS) return 0;
    if(x < 0) return -1;
    return 1;
}

int cs;

inline int get(double M,int p){
    if(cs >= 6){
        double mx = -1e18;int ps = -1;
        FOR(i,std::max(1,p-1),std::min(n,p+1)){
            double gx = y[i]-(R-L)+1.0*(R-L)*((x[i] <= M) ? 1.0*(x[i]-L)/(M-L):1.0*(R-x[i])/(R-M));
            if(mx < gx){
                mx = gx;ps = i;
            }
        }
        return ps;
    }
    double mx = -1e18;int ps = -1;
    FOR(i,1,n){
        double gx = y[i]-(R-L)+1.0*(R-L)*((x[i] <= M) ? 1.0*(x[i]-L)/(M-L):1.0*(R-x[i])/(R-M));
        if(p == 9){
 //           DEBUG(gx);
        }
        if(mx < gx){
            mx = gx;ps = i;
        }
    }
    return ps;
}

int main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    scanf("%d%d%d%d",&cs,&n,&L,&R);
    FOR(i,1,n) scanf("%d",x+i);
    FOR(i,1,n) scanf("%d",y+i);
    double las = L;
    double sm = 0;x[n+1] = x[n+2] = R;
    FOR(i,1,n){
        if(get(x[i],i) != i){
            printf("%.12f\n",0.0);
            continue;
        }
        int ll = i,rr = n,ans = -1;
        while(ll <= rr){
            int mid = (ll + rr) >> 1;
            if(get(x[mid],i) == i) ans = mid,ll = mid+1;
            else rr = mid-1;
        }
        double l = x[ans],r = x[ans+1];
        FOR(jjj,1,50){
            double mid = (l + r) / 2.0;
            if(get(mid,i) == i) l = mid;
            else r = mid;
        }
        l = (l+r)/2.0;
   //     printf("%.10f %.10f %d\n",las,l,x[i]);
        if(las > l){
            printf("%.12f\n",0.0);
            continue;
        }
        printf("%.12f\n",1.0*(l-las)/(R-L));
//        sm += 1.0*(l-las)/(R-L);
        las = l;
    }
//    printf("%.10f\n",sm);
    return 0;
}
