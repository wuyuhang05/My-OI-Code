#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 100000 + 5;
int n,m;

struct BIT{
    struct Node{
        #define lowbit(x) (x&-x)
        LL tree[MAXN];

        inline void add(int pos,LL x){
            for(int i = pos;i <= n;i += lowbit(i)) tree[i] += x;
        }

        inline LL calc(int pos){
            int res = 0;
            for(int i = pos;i;i -= lowbit(i)) res += tree[i];
            return res;
        }
    }bit1,bit2;

    inline LL sum(int pos){
        return (pos+1)*bit1.calc(pos) - bit2.calc(pos);
    }

    inline LL query(int l,int r){
        return sum(r) - sum(l-1);
    }

    inline void add(int pos,LL x){
        bit1.add(pos,x);bit2.add(pos,pos*x);
    }

    inline void modify(int l,int r,LL x){
        add(r+1,-x);add(l,x);
    }
}BIT;

struct node{
    int opt,l,r;LL k;int id;
}p[MAXN],t[2][MAXN];

int ans[MAXN];

inline void Solve(int L,int R,int l,int r){ // 操作[L,R],答案[l,r]
    if(L > R) return;
    if(l == r){
        FOR(i,L,R) if(p[i].opt == 2) ans[p[i].id] = l;
        return;
    }
    int t1=0,t2=0,mid = (l + r) >> 1;
    FOR(i,L,R){
        if(p[i].opt & 1){
            if(p[i].k <= mid) t[0][t1++] = p[i];
            else t[1][t2++] = p[i],BIT.modify(p[i].l,p[i].r,1);
        }
        else{
            LL tmp = BIT.query(p[i].l,p[i].r);
            if(tmp < p[i].k) p[i].k -= tmp,t[0][t1++] = p[i];
            else t[1][t2++] = p[i];
        }
    }
    int Mid = L+t1;
    FOR(i,L,Mid-1){
        p[i] = t[0][i-L];
        if((p[i].opt & 1) && p[i].k > mid) BIT.modify(p[i].l,p[i].r,-1);
    }
    FOR(i,Mid,R){
        p[i] = t[1][i-Mid];
        if((p[i].opt & 1) && p[i].k > mid) BIT.modify(p[i].l,p[i].r,-1);
    }
    Solve(L,Mid-1,l,mid);Solve(Mid,R,mid+1,r);
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,m) scanf("%lld%lld%lld%lld",&p[i].opt,&p[i].l,&p[i].r,&p[i].k),p[i].id = i;
    Solve(1,m,1,n);
    FOR(i,1,m) if(ans[i]) printf("%lld\n",ans[i]);
    return 0;
}