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

double a,b,c,d,L,R;
const double eps=1e-7;

inline double f(double x){
    return (c*x+d)/(a*x+b);
}

inline double simpson(double l,double r,double fl,double fr,double fm){
    return (r-l)*(fl+fr+4*fm)/6;
}

inline double asr(double l,double r,double eps,double fl,double fr,double fm){
    double mid = (l+r)/2,flm = f((l+mid)/2),frm = f((mid+r)/2);
    double L = simpson(l,mid,fl,fm,flm),R = simpson(mid,r,fm,fr,frm),A = simpson(l,r,fl,fr,fm);
    if(std::fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15;
    return asr(l,mid,eps/2,fl,fm,flm)+asr(mid,r,eps/2,fm,fr,frm);
}

int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&L,&R);
    printf("%.6f\n",asr(L,R,eps,f(L),f(R),f((L+R)/2)));
    return 0;
}
