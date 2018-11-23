#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
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
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000000+5;
char str1[MAXN],str2[MAXN];
int next[MAXN],ans;

void pre(char *str){
    int len = strlen(str+1),j=0;
    FOR(i,2,len){
        while(j && str[i] != str[j+1]) j = next[j];
        if(str[i] == str[j+1]) j++;
        next[i] = j;
    }
}

void kmp(char *str1,char *str2){
    int len1 = strlen(str1+1),len2 = strlen(str2+1),j = 0;
    FOR(i,1,len2){
        while(j && str1[j+1] != str2[i]) j = next[j];
        if(str1[j+1] == str2[i]) j++;
        if(j == len1){
            ans++;j = next[j];
        }
    }
}

inline void Solve(){
    ans = 0;
    scanf("%s%s",str1+1,str2+1);
    pre(str1);
    kmp(str1,str2);
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
