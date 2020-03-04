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

const int MAXN = 3e5 + 5;
char str[MAXN];
int n;

struct SA{
    int tax[MAXN],tp[MAXN],rk[MAXN],sa[MAXN];
    int M = 128,n;

    inline void sort(){
        FOR(i,0,M) tax[i] = 0;
        FOR(i,1,n) tax[rk[i]]++;
        FOR(i,1,M) tax[i] += tax[i-1];
        ROF(i,n,1) sa[tax[rk[tp[i]]]--] = tp[i];
    }

    inline void build(){
        FOR(i,1,n) rk[i] = str[i],tp[i] = i;
        sort();
        for(int w = 1,p = 0;p < n;w <<= 1,M = p){
            p = 0;
            FOR(i,1,w) tp[++p] = n-w+i;
            FOR(i,1,n) if(sa[i] > w) tp[++p] = sa[i]-w;
            sort();
            std::swap(rk,tp);
            rk[sa[1]] = p = 1;
            FOR(i,2,n) rk[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w]) ? p : ++p;
        }
    }
}sa;

int main(){
    scanf("%s",str+1);n = strlen(str+1);
    FOR(i,n+1,2*n) str[i] = str[i-n];
    sa.n = n*2;sa.build();
//    FOR(i,1,2*n) DEBUG(sa.sa[i]);
    FOR(i,1,2*n){
        if(sa.sa[i] <= n) putchar(str[sa.sa[i]+n-1]);
    }
    puts("");
    return 0;
}
