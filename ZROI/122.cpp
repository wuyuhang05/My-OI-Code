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

#define cint(x) x-'a'+1
const int MAXN = 5000 + 5;
char str1[MAXN],str2[MAXN];
int f[MAXN],g[MAXN];
int N;

int main(){
    scanf("%d",&N);
    scanf("%s%s",str1+1,str2+1);
    FOR(i,1,N) f[cint(str1[i])]++;
    FOR(i,1,N) g[cint(str2[i])]++;
    // 
    FOR(i,1,N){
        if(str2[i] == 'a'){
            g[1]--;
            if(f[2] && f[1]+f[2]-1 >= g[3] && f[2]+f[3]-1>=g[1] && f[3]+f[1]>=g[2]){
                f[2]--;
                putchar('b');
            }
            else{
                f[3]--;
                putchar('c');
            }
        }
        if(str2[i] == 'b'){
            g[2]--;
            if(f[1] && f[1]+f[2]-1 >= g[3] && f[2]+f[3]>=g[1] && f[3]+f[1]-1>=g[2]){
                f[1]--;
                putchar('a');
            }
            else{
                f[3]--;
                putchar('c');
            }
        }
        if(str2[i] == 'c'){
            g[3]--;
            if(f[1] && f[1]+f[2]-1 >= g[3] && f[2]+f[3]>=g[1] && f[3]+f[1]-1>=g[2]){
                f[1]--;
                putchar('a');
            }
            else{
                f[2]--;
                putchar('b');
            }
        }
    }
    puts("");
    return 0;
}