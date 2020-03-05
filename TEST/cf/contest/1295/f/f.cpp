/*
 * Author: RainAir
 * Time: 2020-03-05 11:41:52
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200+5;
const int ha = 998244353;
int f[MAXN][MAXN]; // 前 i 个数 in jth 段
int l[MAXN],r[MAXN];

std::vector<int> S;
int n;

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%d%d",l+i,r+i);
        S.pb(l[i]);S.pb(r[i]+1);
    }
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) l[i] = std::lower_bound(all(S),l[i])-S.begin()+1,
        r[i] = std::lower_bound(all(S),r[i])-S.begin()+1;
    FOR(i,1,n){
        FOR(j,1,(int)S.size()){
            FOR(k,1,i-1){
                FOR(l,1,j-1){
                    f[i][j] += f[j][k]*C(len+pos-1,pos);
                }
            }
        }
    }
    return 0;
}
