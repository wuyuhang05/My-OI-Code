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

const int MAXN = 2e5 + 5;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    LL tree[MAXN];

    inline void add(int pos,LL x){
        for(;pos<MAXN;pos+=lowbit(pos)) tree[pos] = std::max(tree[pos],x);
    }

    inline LL qry(int pos){
        LL res=0;
        for(;pos;pos-=lowbit(pos)) res = std::max(res,tree[pos]);
        return res;
    }
}bit;

int n;
std::vector<int> S;

struct Node{
    int x,y,v;
    bool operator < (const Node &t) const {
        if(x != t.x) return x < t.x;
        return y < t.y;
    }
}a[MAXN];

int main(){
    scanf("%*d%d",&n);
    FOR(i,1,n){
        int t,p;scanf("%d%d%d",&t,&p,&a[i].v);t *= 2;
        a[i].x = t+p;a[i].y = t-p;S.pb(a[i].y);
    }
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) a[i].y = std::lower_bound(all(S),a[i].y)-S.begin()+1;
    std::sort(a+1,a+n+1);
    LL ans = 0;
//    puts("");
//    FOR(i,1,n) printf("%d %d %d\n",a[i].x,a[i].y,a[i].v);
    FOR(i,1,n){
        LL t;
        ans = std::max(ans,t = a[i].v+bit.qry(a[i].y));
        bit.add(a[i].y,t);
    }
    printf("%lld\n",ans);
    return 0;
}
/*
 * f[i] 最后一次接到的馅饼是 i
 * f[i] = max(f[j])+v[i] if 2t[i]-2t[j] >= |p[i]-p[j]|
 * 拆一下限制: <=> 2t[i]-p[i]>=2t[j]-p[j] and 2t[i]+p[i] >= 2t[j]+p[j]
 * => t[i] >= t[j]  所以只要满足上述限制的一定时间会满足限制
 * 按照 t[i]+p[i]  排序 只需要关心 t[i]-p[i]>=t[j]-p[j] 是可以简单维护的
 */
