#include<bits/stdc++.h>

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

const int MAXN = 100+5;
int n,p;
int ans[MAXN][MAXN];// x行 y 列
std::mt19937 g(time(NULL));

inline int query(int xl,int xr,int yl,int yr){
    printf("1 %d %d %d %d\n",xl+1,yl+1,xr+1,yr+1);std::fflush(stdout);
    int x;scanf("%d",&x);return x;
}

inline int gen(int l,int r){
    return l+g()%(r-l+1);
}

inline void work(int xl,int xr,int yl,int yr,int sm){
    if(sm == 0) return;
    if(sm == (xr-xl+1)*(yr-yl+1)){
        FOR(i,xl,xr) FOR(j,yl,yr) ans[i][j] = 1;
        return;
    }
    if(xl == xr && yl == yr){
        ans[xl][xr] = sm;return;
    }
    if(xr-xl < yr-yl){
        int mid = (yr+yl)>>1;
        int t = query(xl,xr,yl,mid);
        work(xl,xr,yl,mid,t);work(xl,xr,mid+1,yr,sm-t);
    }
    else{
        int mid = (xl+xr)>>1;
        int t = query(xl,mid,yl,yr);
        work(xl,mid,yl,yr,t);work(mid+1,xr,yl,yr,sm-t);
    }
}

inline void Solve(){CLR(ans,0);
    scanf("%d%d",&n,&p);int sm = query(0,n-1,0,n-1);
    work(0,n-1,0,n-1,sm);
    puts("2");
    FOR(i,0,n-1) FOR(j,0,n-1) printf("%d%c",ans[i][j]," \n"[j==n-1]);
    std::fflush(stdout);int x;scanf("%d",&x);
    if(x == -1) exit(-1);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
