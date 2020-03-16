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

inline int calc(int l,int r){
    return (l-1)^((l-1)>>1)^r^(r>>1);
}

struct SEG{
    #define lc ((x)<<1)
    #define rc ((x)<<1|1)
    int sm[MAXN<<2],tag[MAXN<<2];

    inline void pushup(int x){
        sm[x] = sm[lc]^sm[rc];
    }

    inline void cover(int x,int l,int r)
}

int main(){
    return 0;
}
