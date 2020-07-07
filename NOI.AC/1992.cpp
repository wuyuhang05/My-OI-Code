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
#include<cassert>

const int MAXN = 1e6 + 5;

int k,n,a[MAXN];
double f[MAXN],val[MAXN];
std::vector<int> pos[MAXN];
int ps[MAXN];
std::vector<P> stk[MAXN];

inline double calc(int l,int r){// [l,r]
    return f[l-1]+val[ps[r]-ps[l]+1];
}

inline int findp(int x,int y,int l,int r){// x > y
    int ans = -1;// 找到最后一个 y 比 x RainAir 的地方
  //  FOR(i,l,r) printf("%.10lf %.10lf\n",calc(x,pos[a[x]][i]),calc(y,pos[a[x]][i]));
    while(l <= r){
        int mid = (l + r) >> 1;
//        DEBUG(calc(x,pos[a[x]][mid])),DEBUG(calc(y,pos[a[x]][mid]));
        if(calc(x,pos[a[x]][mid]) >= calc(y,pos[a[x]][mid])) ans = mid,l = mid+1;
        else r = mid-1;
    }
    return ans;
}

int main(){
    scanf("%d%d",&k,&n);
    FOR(i,1,n) scanf("%d",a+i),pos[a[i]].pb(i),ps[i] = (int)pos[a[i]].size()-1;
    if(k == 2){
        printf("%d\n",n);return 0;
    }
    FOR(i,1,n) val[i] = k==3?1.0*i*sqrt(1.0*i):1.0*i*i;
    FOR(i,1,n){
        a[0] = a[i];
        while(!stk[a[i]].empty() && stk[a[i]].back().se < ps[i]) stk[a[i]].pop_back();
        f[i] = f[i-1]+val[1];
        if(!stk[a[i]].empty()) f[i] = std::max(f[i],calc(stk[a[i]].back().fi,i));
        int now = -1;
        while(!stk[a[i]].empty() && stk[a[i]].back().se <= findp(i,stk[a[i]].back().fi,ps[i]+1,(int)pos[a[i]].size()-1)) now = stk[a[i]].back().se,stk[a[i]].pop_back();
        if(stk[a[i]].empty()){
            stk[a[i]].pb(MP(i,(int)pos[a[i]].size()-1));
//            DEBUG(a[i]);
//            if(now != -1) assert(now==(int)pos[a[i]].size()-1);
        }
        else{
            int t = findp(i,stk[a[i]].back().fi,ps[i]+1,(int)pos[a[i]].size()-1);
            if(std::max(t,now) != -1){
//                stk[a[i]][(int)stk[a[i]].size()-1].se = std::max(now,t)+1;
//                assert(std::max(t,now) < stk[a[i]].back().se);
                stk[a[i]].pb(MP(i,std::max(t,now)));
            }
        }
    //    f[i] = f[i-1];
    //    FOR(j,0,ps[i]){
    //        f[i] = std::max(f[i],f[pos[a[i]][j]-1]+val[ps[i]-j+1]);
    //    }
    }
//    FOR(i,1,n)DEBUG(f[i]);
    printf("%.10lf\n",(double)f[n]);
    return 0;
}
