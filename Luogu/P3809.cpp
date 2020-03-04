#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000000+5;

char str[MAXN];
int sa[MAXN],rk[MAXN],tp[MAXN],tax[MAXN];
int N,M;

inline void sort(){
    CLR(tax,0);
    FOR(i,1,N) tax[rk[i]]++;
    FOR(i,1,M) tax[i] += tax[i-1];
    ROF(i,N,1) sa[tax[rk[tp[i]]]--] = tp[i];
}

inline void SuffixSort(){
    M = 75;
    FOR(i,1,N) rk[i] = str[i]-'0' + 1,tp[i] = i;
    sort();
    for(int w = 1,p = 0;p < N;M = p,w <<= 1){
        p = 0;
        FOR(i,1,w) tp[++p] = N-w+i; // 后面已经没有了,字典序当然小
        FOR(i,1,N) if(sa[i] > w) tp[++p] = sa[i] - w; // 更新后面还有的字典序
        sort();
        std::swap(tp,rk);
        rk[sa[1]] = p = 1;
        FOR(i,2,N) rk[sa[i]] = (tp[sa[i-1]] == tp[sa[i]] && tp[sa[i-1]+w] == tp[sa[i]+w]) ? p : ++p;
    }
    FOR(i,1,N) printf("%d ",sa[i]);
    puts("");
}

int main(){
    scanf("%s",str+1);
    N = strlen(str+1);
    SuffixSort();
    return 0;
}