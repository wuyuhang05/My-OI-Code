// START at 8:50:00
#include <bits/stdc++.h>

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

const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;

inline void add(int &x,int y){
    x += y;if(x >= ha) x -= ha;
}

struct BIT{
    int tree[MAXN];
    #define lowbit(x) ((x)&(-(x)))

    inline void add(int pos,int x){
        while(pos){
            ::add(tree[pos],x);
            pos -= lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos < MAXN){
            ::add(res,tree[pos]);
            pos += lowbit(pos);
        }
        return res;
    }
}pre,suf;

int n,a[MAXN];

int main(){
//    freopen("D.in","r",stdin);
  //  freopen("D.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,2,n) suf.add(a[i],n-i+1);
    int ans = 0;
    FOR(i,2,n-1){
        pre.add(a[i-1],i-1);
        suf.add(a[i],ha-(n-i+1));
        add(ans,1ll*pre.query(a[i]+1)*suf.query(a[i]+1)%ha);
    }
    printf("%d\n",ans);
    return 0;
}
// END at 8:53:12
