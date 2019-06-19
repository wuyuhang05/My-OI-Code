#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300000+5;
char str[MAXN],a[MAXN],b[MAXN];
int lena,lenb,n;

int sa[MAXN],rk[MAXN],tp[MAXN],tax[MAXN],M,height[MAXN];
/*
inline void Sort(){
    FOR(i,0,M) tax[i] = 0;
    FOR(i,1,n) ++tax[rk[i]];
    FOR(i,1,M) tax[i] += tax[i-1];
    ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
}
*/
inline void Sort(){
    FOR(i,0,M) tax[i] = 0;
    FOR(i,1,n) tax[rk[i]]++;
    FOR(i,1,M) tax[i] += tax[i-1];
    ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
}
int ans;
inline void SuffixSort(){
    M = 75;
    FOR(i,1,n) rk[i] = str[i]-'a'+1,tp[i] = i;
    Sort();
    for(int p = 0,w = 1;p < n;M = p,w <<= 1){
        p = 0;FOR(i,1,w) tp[++p] = n-w+i;
        FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i] - w;
        Sort();std::swap(rk,tp);
        rk[sa[1]] = p = 1;
        FOR(i,2,n) rk[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w]) ? p : ++p;
    }
    //FOR(i,1,n) printf("%d ",sa[i]);a
    int k = 0;
    FOR(i,1,n){
        if(k) --k;
        int j = sa[rk[i]-1];
        while(str[j+k] == str[i+k]) k++;
        height[rk[i]] = k;
        if((sa[rk[i]]>lena+1 && sa[rk[i]-1]<lena+1) || (sa[rk[i]]<lena+1&&sa[rk[i]-1]>lena+1))
            ans = std::max(ans,height[rk[i]]);
    }
}

int main(){
    scanf("%s%s",a+1,b+1);
    lena = strlen(a+1);lenb = strlen(b+1);
    FOR(i,1,lena) str[++n] = a[i];str[++n] = 'a'+26;
    FOR(i,1,lenb) str[++n] = b[i];
    SuffixSort();
    printf("%d\n",ans);
    return 0;
}
