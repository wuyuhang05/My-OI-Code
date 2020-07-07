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

int n;

inline int query(int x){//  0 小于 1 大于
    printf("%d\n",x);std::fflush(stdout);
    char str[23];scanf("%s",str);
    if(str[0] == 'E') exit(0);
    return str[0] == 'G';
}

namespace Subtask1{
//public:
    inline bool chk(int x){
        query(1);
        return query(x);
    }

    inline void Solve(){
        int l = 1,r = n,ans = -1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(chk(mid)) ans = mid,l = mid+1;
            else r = mid-1;
        }
        query(ans);
        query(1);query(1);
        l = 1,r = n,ans = -1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(chk(mid)) ans = mid,l = mid+1;
            else r = mid-1;
        }
        query(ans);
    }
}

const int MAXN = 1e6 + 5;
int sm[MAXN],lc[MAXN],rc[MAXN],tag[MAXN],tot,rt;

inline void cover(int &x){
    if(!x) x = ++tot;
    tag[x] = 1;sm[x] = 0;
}

inline void pushdown(int x){
    if(tag[x]){
        cover(lc[x]);cover(rc[x]);
        tag[x] = 0;
    }
}

inline void modify(int &x,int l,int r,int L,int R){
    if(!x){x = ++tot;sm[x] = r-l+1;}
    if(l == L && r == R){cover(x);return;}
    int mid = (l + r) >> 1;pushdown(x);
    if(R <= mid) modify(lc[x],l,mid,L,R);
    else if(L > mid) modify(rc[x],mid+1,r,L,R);
    else modify(lc[x],l,mid,L,mid),modify(rc[x],mid+1,r,mid+1,R);
    sm[x] = (lc[x]?sm[lc[x]]:(mid-l+1))+(rc[x]?sm[rc[x]]:(r-mid));
}

inline int queryp(int &x,int l,int r,int p){
    if(!x){x = ++tot;sm[x] = r-l+1;}
    if(l == r) return l;
    int mid = (l + r) >> 1;pushdown(x);
    int ls = lc[x]?sm[lc[x]]:(mid-l+1);
    if(p <= ls) return queryp(lc[x],l,mid,p);
    else return queryp(rc[x],mid+1,r,p-ls);
}

namespace Subtask2{
//public:

    inline void Solve(){
        sm[rt = tot = 1] = n;
        while(sm[1] >= 3){
            int d = sm[1]/3;
            int midl = queryp(rt,1,n,d),midr = queryp(rt,1,n,sm[1]-d);
            int t[6];
            t[1] = query(midl);t[2] = query(midr);
            if(t[1] == t[2]){
                if(t[1] == 0){
                    modify(rt,1,n,midr,n);
                }
                else if(t[2] == 1){
                    modify(rt,1,n,1,midl);
                }
            }
            else if(t[1] == 0 && t[2] == 1){
                modify(rt,1,n,midl,midr);
            }
            else{
                t[3] = query(midr);
                if(t[2] == t[3]){
                    modify(rt,1,n,midr,n);
                    // t[2] == 0
                }
                else{
                    t[4] = query(midl);
                    if(t[4] == 0){
                        modify(rt,1,n,midl,midr);
                    }
                    else{
                        modify(rt,1,n,1,midl);
                    }
                }
            }
        }
        FOR(i,1,sm[1]) query(queryp(rt,1,n,i));
    }
}

int main(){
    scanf("%d",&n);
    Subtask2::Solve();
    exit(0);
    if(n <= 100000) Subtask2::Solve();
    Subtask1::Solve();
    return 0;
}
