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

const int MAXN = 1e6 + 5;
int n,m;

struct Node{
    double p1,p2,a,ip1,ip2;
}a[MAXN];

inline bool cmp1(Node x,Node y){
    return x.ip1 < y.ip1;
}

inline bool cmp2(Node x,Node y){
    return x.ip2 < y.ip2;
}

std::pair<double,double> A[MAXN],B[MAXN];

inline bool chk(double k){
    int ps = m;
    double mx = 0;
    FOR(i,1,n){
        while(ps && A[i].fi+B[ps].fi >= k) mx = std::max(mx,B[ps].se),ps--;
        if(mx+A[i].se >= k) return true;
    }
    return false;
}

int main(){
    int N;scanf("%d",&N);
    FOR(i,1,N){
        double p;scanf("%lf%lf",&a[i].a,&p);
        a[i].p1 = p;a[i].p2 = 1-p;
        a[i].ip1 = a[i].p1 ? 1/a[i].p1 : 1e18;
        a[i].ip2 = a[i].p2 ? 1/a[i].p2 : 1e18;
    }
    std::sort(a+1,a+N+1,cmp1);
    A[++n] = MP(0,0);
    double sm = 0;
    FOR(i,1,N){
        if(a[i].p1 == 0) break;
        sm += a[i].a;
        A[++n] = MP(sm,-(a[i].ip1-1)*sm);
    }
    std::sort(a+1,a+N+1,cmp2);sm = 0;
    B[++m] = MP(0,0);
    FOR(i,1,N){
        if(a[i].p2 == 0) break;
        sm += a[i].a;
        B[++m] = MP(-(a[i].ip2-1)*sm,sm);
    }
    std::sort(A+1,A+n+1);std::sort(B+1,B+m+1);
    double l = 0,r = 1e18;
    FOR(i,0,100){
        double mid = (l + r) / 2.0;
        if(chk(mid)) l = mid;
        else r = mid;
    }
    printf("%.6f\n",(l+r)/2.0);
    return 0;
}
