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

const int MAXN = 7000+5;
int n,q;
int now;

struct Node{
    int k,b,id;
    Node(int k=0,int b=0,int id=0) : k(k),b(b),id(id) {}
}a[MAXN];

inline bool cmp(const Node &a,const Node &b){
    LL ay = 1ll*a.k*now+a.b,by = 1ll*b.k*now+b.b;
    return ay==by ? a.id < b.id : ay > by;
}

int main(){
//    freopen("C.in","r",stdin);
//    freopen("C.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&a[i].k,&a[i].b),a[i].id = i;
    scanf("%d",&q);
    FOR(i,1,q){
        int x;scanf("%d%d",&now,&x);
        std::nth_element(a+1,a+x,a+n+1,cmp);
        printf("%d\n",a[x].id);
    }
    return 0;
}
