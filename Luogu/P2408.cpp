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
char str[MAXN];
int n;

struct SuffixArray{
    int sa[MAXN],tax[MAXN],tp[MAXN],rk[MAXN];
    int M = 27;

    inline void sort(){
        FOR(i,0,M) tax[i] = 0;
        FOR(i,1,n) tax[rk[i]]++;
        FOR(i,1,M) tax[i] += tax[i-1];
        ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
    }

    int H[MAXN];// H[i] = lcp(sa[i-1],sa[i])

    inline void getH(){
        int j = 0;
        FOR(i,1,n){
            if(j) j--;
            while(str[i+j] == str[sa[rk[i]-1]+j]) ++j;
            H[rk[i]] = j;
        }
    }

    inline void build(){
        FOR(i,1,n) rk[i] = str[i]-'a'+1,tp[i] = i;
        sort();
        for(int w = 1,p=0;p < n;w <<= 1,M = p){
            p = 0;
            FOR(i,1,w) tp[++p] = n-w+i;
            FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i]-w;
            sort();
            std::swap(tp,rk);
            rk[sa[1]] = p = 1;
            FOR(i,2,n) rk[sa[i]] = tp[sa[i-1]] == tp[sa[i]] && tp[sa[i-1]+w] == tp[sa[i]+w] ? p : ++p;
        }
        getH();
    }
}SA;

int main(){
    scanf("%d",&n);scanf("%s",str+1);
    SA.build();
    LL ans = 1ll*n*(n+1)/2;
    FOR(i,1,n) ans -= SA.H[i];
    printf("%lld\n",ans);
    return 0;
}
