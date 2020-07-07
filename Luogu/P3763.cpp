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
const int ha = 1e9 + 9;
const int BASE = 5;

int pw[MAXN];
int ctoi[MAXN];
int S[MAXN],T[MAXN];
char str[MAXN];
int sm1[MAXN],sm2[MAXN];
int n,m;

inline int calc(int sm[],int l,int r){
    return (sm[r]+ha-1ll*sm[l-1]*pw[r-l+1]%ha)%ha;
}

inline int find(int l1,int l2){
//    DEBUG(S[l1]);DEBUG(T[l2]);
    if(S[l1] != T[l2]) return 0;
    int l = 2,r = std::min(n-l1,m-l2)+1,ans = 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(calc(sm1,l1,l1+mid-1) == calc(sm2,l2,l2+mid-1)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    return ans;
}

inline void Solve(){
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,1,n) S[i] = ctoi[str[i]];
    scanf("%s",str+1);m = strlen(str+1);
    FOR(i,1,m) T[i] = ctoi[str[i]];
    S[n+1] = 233;T[m+1]=666;
    FOR(i,1,n) sm1[i] = (1ll*sm1[i-1]*BASE%ha+S[i])%ha;
    FOR(i,1,m) sm2[i] = (1ll*sm2[i-1]*BASE%ha+T[i])%ha;
    int ans = 0;
    FOR(ii,1,n){
        int l1=ii;
        if(l1+m-1 > n) break;
        int l2 = 1;bool flag = 1;
        FOR(i,1,3){
            int t = find(l1,l2);
//            DEBUG(l1);DEBUG(l2);DEBUG(t);
            l1 += t+1;l2 += t+1;
            if(l2 > m) break;
        }
        int t = find(l1,l2);
        l1 += t;l2 += t;
        flag &= (l2>m);
        if(!flag) continue;
        ans++;
  //      DEBUG(ii);
    }
    printf("%d\n",ans);
}

int main(){
    freopen("1.in","r",stdin);
    ctoi['A'] = 1;ctoi['G'] = 2;ctoi['C'] = 3;ctoi['T'] = 4;
    pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 1ll*pw[i-1]*BASE%ha;
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
