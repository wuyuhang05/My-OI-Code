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

struct DS{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    int mn[MAXN<<2],mx[MAXN<<2],sm[MAXN<<2];

    inline void update(int x,int l,int r,int p,int d){
        if(l == r) {mn[x] = mx[x] = d;return;}
        int mid = (l + r) >> 1;
        if(p <= mid) update(lc,l,mid,p,d);
        else update(rc,mid+1,r,p,d);
        mn[x] = std::min(mn[lc],mn[rc]);
        mx[x] = std::max(mx[lc],mx[rc]);
    }

    inline void update2(int x,int l,int r,int p){
        if(l == r) {sm[x] ^= 1;return;}
        int mid = (l + r) >> 1;
        if(p <= mid) update2(lc,l,mid,p);
        else update2(rc,mid+1,r,p);
        sm[x] = sm[lc]+sm[rc];
    }

    inline bool chk(int x,int k,int flag){
        return flag ? mx[x] <= k : mn[x] >= k;
    }

    inline int queryl(int x,int l,int r,int p,int k,int flag){
        if(chk(x,k,flag)) return l-1;
        if(l == r) return l;
        int mid = (l + r) >> 1;
        if(p <= mid) return queryl(lc,l,mid,p,k,flag);
        int t = queryl(rc,mid+1,r,p,k,flag);
        return t > mid ? t : queryl(lc,l,mid,p,k,flag);
    }

    inline int queryr(int x,int l,int r,int p,int k,int flag){
        if(chk(x,k,flag)) return r+1;
        if(l == r) return l;
        int mid = (l + r) >> 1;
        if(p > mid) return queryr(rc,mid+1,r,p,k,flag);
        int t = queryr(lc,l,mid,p,k,flag);
        return t <= mid ? t : queryr(rc,mid+1,r,p,k,flag);
    }

    inline int query2(int x,int l,int r,int L,int R){
        if(L > R) return 0;
        if(l == L && r == R) return sm[x];
        int mid = (l + r) >> 1;
        if(R <= mid) return query2(lc,l,mid,L,R);
        if(L > mid) return query2(rc,mid+1,r,L,R);
        return query2(lc,l,mid,L,mid)+query2(rc,mid+1,r,mid+1,R);
    }

    inline int findkth(int x,int l,int r,int k){
        if(l == r) return l;
        int mid = (l + r) >> 1;
        if(sm[lc] >= k) return findkth(lc,l,mid,k);
        return findkth(rc,mid+1,r,k-sm[lc]);
    }
}tree;

int n,k,q,T;
int a[MAXN];
int las = 0;

inline void work(){
    int l = 1,r = 1e9,ans = -1;
    int ps = tree.findkth(1,1,n,(k+1)>>1);
    if(k&1){ // 想要更大的最后一次操作
        while(l <= r){
            int mid = (l + r) >> 1;
            int ls = tree.queryl(1,1,n,ps,mid,0),rs = tree.queryr(1,1,n,ps,mid,0);
            bool flag = true;
            if(tree.query2(1,1,n,ls+1,rs-1) < (k>>1)+1) flag = false;
            if(flag) ans = mid,l = mid+1;
            else r = mid-1;
        }
    }
    else{
        while(l <= r){// 所有区间的最大值最小
            // 二分这个最小值
            // 询问是否存在一个区间 只含<=t 的
            // 发现这些区间都经过一个共同点
            // 我们从这个共同点往左往右找到连续一段<=t的
            // 如果包含的点数>=(k/2)+1 说明一定有一个区间在这里面
            int mid = (l + r) >> 1;
            int ls = tree.queryl(1,1,n,ps,mid,1),rs = tree.queryr(1,1,n,ps,mid,1);
            bool flag = true;
            if(tree.query2(1,1,n,ls+1,rs-1)<(k>>1)+1) flag = false;
            if(flag) ans = mid,r = mid-1;
            else l = mid+1;
        }
    }
    printf("%d\n",las = ans);
}

int main(){
    scanf("%d%d%d%d",&n,&k,&q,&T);
    FOR(i,1,n){
        int x;scanf("%d",&x);tree.update(1,1,n,i,x);
    }
    FOR(i,1,k){
        int x;scanf("%d",&x);tree.update2(1,1,n,x);
        a[x] = 1;
    }
    work();
    FOR(i,1,q){
        int opt,x;scanf("%d%d",&opt,&x);
        if(T) x = (x-1+las)%n+1;
        if(opt == 1){
            tree.update2(1,1,n,x);
            k -= a[x];
            a[x] ^= 1;
            k += a[x];
        }
        if(opt == 2){
            int v;scanf("%d",&v);
            tree.update(1,1,n,x,v);
        }
        work();
    }
    return 0;
}
