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
const int MAXM = 200;
int n,m;
int a[MAXN],sm[MAXN];
LL f[2][MAXN],g[MAXN];
std::deque<int> q;

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),sm[i] = sm[i-1]+a[i];
    if(sm[n] < m){
        puts("0");
        return 0;
    }
    LL ans = sm[n];int now = 0;
    FOR(i,1,n) f[now^1][i] = sm[i-1]*(sm[i-1]>=m)+a[i];
    ans = std::min(ans,f[now^1][n]);
    FOR(j,2,std::min(n,MAXM)){
        q.clear();q.pb(j-1);
        CLR(f[now],0);
        g[j-1] = 1e18;
        FOR(i,j,n){
            f[now][i] = 1e18;
            // sm[i-1]-sm[p] <= m
            // sm[p] >= sm[i-1]-m
            int p = std::lower_bound(sm,sm+i,sm[i-1]-m)-sm;
     //       DEBUG(i);DEBUG(p);DEBUG(sm[i-1]-m);
            while(!q.empty() && q.front() < p) q.pop_front();
            f[now][i] = std::min(f[now][i],f[now^1][q.front()]+j*a[i]);
            // sm[p] < sm[i-1]-m
            f[now][i] = std::min(f[now][i],g[p-1]+sm[i-1]+j*a[i]);
            g[i] = std::min(g[i-1],f[now^1][i]-sm[i]);
            while(!q.empty() && f[now^1][q.back()] >= f[now^1][i]) q.pop_back();
            q.pb(i);
        }
        FOR(i,j,n){
            ans = std::min(ans,f[now][i]+(sm[n]-sm[i])*(sm[n]-sm[i]>=m));
        }
//        DEBUG(j);
//if(j==3)        FOR(i,1,n) DEBUG(f[now][i]);
        now ^= 1;
    }
    printf("%lld\n",ans);
    return 0;
}
/*
 * f[i][j]: 考虑 前 i 个数  砍了 j 次的代价
 * f[i][j] = min(f[k][j-1]+j*a[i]+cost(k+1,i-1))
 * cost(l,r) = [sm[r]-sm[l-1] > m]*(sm[r]-sm[l-1])
 * 优化：考虑分类讨论 当 sm[i-1]-sm[k]<=m 时 min(f[k][j-1])+j*a[i]
 * 当 sm[i-1]-sm[k]>m 时 min(f[k][j-1]-sm[k])+sm[i-1]+j*a[i]
 * 第一种情况维护一个单调队列
 * 第二种情况维护一个前缀 min
 * 发现有用的 j 并不多：假设我们什么也不做 代价最大是 2000i，如果搞了 j 次那么最小代价是1000j*(j-1)/2 
 * 有用一定满足 1000j*(j-1)/2<2000i => j(j-1)<4i => j ~ O(\sqrt(i)) 就可以通过了
 */
