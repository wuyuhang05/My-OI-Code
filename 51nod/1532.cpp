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

const int MAXN = 3000000+5;
const int MAXM = 600+5;
std::bitset<MAXM> F,G[357];
char A[MAXN],str[MAXN];
int n,m;

int main(){
    int ch = getchar();
    while(ch != 'n') A[++n] = ch,ch = getchar();
    scanf("%d",&m);
    FOR(i,1,m){
        int x;scanf("%d",&x);scanf("%s",str+1);
        FOR(j,1,x) G[(int)str[j]][i] = 1;
    }
    bool flag = true;
    FOR(i,1,n){
        F <<= 1;F[1] = 1;
        F = F&G[(int)A[i]];
        if(F[m]){
            printf("%d\n",i-m+1);flag = false;
        }
    }
    if(flag) puts("NULL");
    return 0;
}
/*
 * f[i][j] A串前缀i和B串前缀j是否匹配
 * g[i][j] 字母i在j位置是否匹配
 * f[i][j] = f[i-1][j-1]&g[A[i]][j]
 * 写成bitset的形式:
 * F[i] = (F[i-1]<<1)&g[A[i]]
 */
