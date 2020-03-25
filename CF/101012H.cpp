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

const int MAXN = 300;
const int MAXM = 2e5 + 5;
int n,k,now;
std::vector<LL> w[MAXN+5];
LL f[2][MAXM];

inline void work(int l,int r,int L,int R,int p,int q){ // j = k*p+q
    // 正在更新[l,r] 决策区间[L,R]
    if(l > r) return;
    int mid = (l + r) >> 1,ps=mid;
    f[now][mid*p+q] = std::max(f[now][mid*p+q],f[now^1][mid*p+q]);
    ROF(j,std::min(mid-1,R),L){
        if(mid-j>(int)w[p].size()) break;
        if(f[now][mid*p+q] < f[now^1][j*p+q]+w[p][mid-j-1]){
            f[now][mid*p+q] = f[now^1][j*p+q]+w[p][mid-j-1];
            ps = j;
        }
    }
    work(l,mid-1,L,ps,p,q);work(mid+1,r,ps,R,p,q);
}

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n){
        int s,v;scanf("%d%d",&s,&v);
        w[s].pb(v);
    }
    FOR(i,1,MAXN) std::sort(all(w[i])),std::reverse(all(w[i]));
    FOR(i,1,MAXN) FOR(j,1,(int)w[i].size()-1) w[i][j] += w[i][j-1];
    FOR(i,1,MAXN){
        if(w[i].empty()) continue;
        now ^= 1;CLR(f[now],0);
        FOR(j,0,i-1) //%i=j
            work(0,(k-j)/i,0,(k-j)/i,i,j);
        FOR(j,1,k) f[now][i] = std::max(f[now][i],f[now][i-1]);
    }
    FOR(i,1,k) printf("%lld ",f[now][i]);puts("");
    return 0;
}
/*
 * 按照重量分组 重量相同的放在一组
 * 考虑朴素dp：f[i][j] = f[i-1][j-k*w]+cost(k) O(300k^2)
 * 借鉴一下多重背包的做法 我们把j按照%i分类讨论 重新标号 现在转移方程变成：
 * f[i][j] = f[i-1][k]*cost(j,k) 其中cost(j,k) 是前j-k大的和
 * 易证明cost(i,j)+cost(i+1,j+1) >=  cost(i+1,j)+cost(i,j+1) 所以具有决策单调性
 */
