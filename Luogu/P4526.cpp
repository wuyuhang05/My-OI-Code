#include<bits/stdc++.h>

#define fi first
#define se second
#define db long double
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

db a;
const db EPS = 1e-8;

db f(db x){
    return pow(x,a/x-x);
}

db simpson(db l,db r,db fl,db fr,db fm){
    return (r-l)*(fl+fr+4*fm)/6;
}

db asr(db l,db r,db eps,db fl,db fr,db fm){
    db mid = (l+r)/2,flm = f((l+mid)/2),frm = f((mid+r)/2);
    db L = simpson(l,mid,fl,fm,flm),R = simpson(mid,r,fm,fr,frm),A = simpson(l,r,fl,fr,fm);
    if(std::fabs(L+R-A) <= 15*eps) return (L+R)+(L+R-A)/15;
    return asr(l,mid,eps/2,fl,fm,flm)+asr(mid,r,eps/2,fm,fr,frm);
}

int main(){
    scanf("%Lf",&a);
    if(a < 0) {puts("orz");return 0;}
    printf("%.5Lf\n",asr(EPS,20,EPS,f(EPS),f(20),f(20/2)));
    return 0;
}
