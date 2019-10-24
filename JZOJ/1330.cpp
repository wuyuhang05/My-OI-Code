/*
 * Author: RainAir
 * Time: 2019-10-24 09:56:44
 */
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500+5;
const int MAXK = 100+5;
int n,k;
char str[MAXN];int now;
int f[2][MAXK][MAXK][2];
int cnt1,cnt2;
//01
int main(){
 //   DEBUG(sizeof(f)/1024);
    scanf("%d%d",&n,&k);
    scanf("%s",str+1);
    FOR(i,1,n){
        if(str[i] == 'j') ++cnt1;
        else ++cnt2;
    }
    cnt1 = std::min(cnt1,k);
    cnt2 = std::min(cnt2,k);
    FOR(a,0,MAXK-1) FOR(b,0,MAXK-1) f[now][a][b][0] = f[now][a][b][1] = -1e9;
    if(str[1] == 'j') f[now][0][0][0] = f[now][1][0][1] = 0;
    else f[now][0][1][0] = f[now][0][0][1] = 0;
    int ans = 0;
    FOR(i,2,n){
        now ^= 1;
        FOR(a,0,MAXK-1) FOR(b,0,MAXK-1) f[now][a][b][0] = f[now][a][b][1] = -1e9;
        FOR(a,0,cnt1){
            FOR(b,0,cnt2){
                if(str[i] == 'j'){
                    f[now][a][b][0] = std::max(f[now^1][a][b][1],f[now^1][a][b][0]);
                    if(a) f[now][a][b][1] = std::max(f[now^1][a-1][b][0]+(i!=1),f[now^1][a-1][b][1]);
                }
                else{
                    f[now][a][b][1] = std::max(f[now^1][a][b][0]+(i!=1),f[now^1][a][b][1]);
                    if(b) f[now][a][b][0] = std::max(f[now^1][a][b-1][0],f[now^1][a][b-1][1]);
                }
            }
        }
        FOR(j,0,k) ans = std::max(ans,std::max(f[now][j][j][0],f[now][j][j][1]));
    }
   // int ans = 0;
 //   FOR(i,0,k) ans = std::max(ans,std::max(f[now][i][i][0],f[now][i][i][1]));
    printf("%d\n",ans);
    return 0;
}

