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

const int MAXN = 4e5 + 5;
int a[MAXN],n;
int pre[MAXN],suf[MAXN];
std::map<int,int> S;

inline bool work(int l,int r){
    if(l >= r) return 1;
    int mid = -1;
    FOR(i,0,r-l){
        if(pre[l+i] < l && suf[l+i] > r){
            mid = l+i;break;
        }
        if(pre[r-i] < l && suf[r-i] > r){
            mid = r-i;break;
        }
    }
    if(mid == -1) return 0;
    return work(l,mid-1)&&work(mid+1,r);
}

inline void Solve(){
    scanf("%d",&n);FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,n) pre[i] = S[a[i]],S[a[i]] = i;S.clear();
    ROF(i,n,1) suf[i] = S[a[i]],S[a[i]] = i;S.clear();
    FOR(i,1,n) if(!suf[i]) suf[i] = n+1;
    if(work(1,n)) printf("non-");
    puts("boring");
}


int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
