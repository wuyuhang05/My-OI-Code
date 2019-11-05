/*
 * Author: RainAir
 * Time: 2019-11-05 16:09:12
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

const int MAXN = 2e5 + 5;
const int ha = 998244353;

char str[MAXN];
int n,sm;
int f[MAXN][3][3][2];

std::set<int> S;

inline int encode(char str[]){
    int ans = 0;
    FOR(i,1,n) ans = ans*3+(str[i]-'a'+1);
    return ans;
}

inline void dfs(char str[]){
    int t = encode(str);
    S.insert(t);
    std::vector<int> id;
    FOR(i,2,n){
        if(str[i] != str[i-1]) id.pb(i);
    }
    if(id.empty()) return;
    FOR(i,0,(int)id.size()-1){
        int x = id[i];
        int a = x-1,b = x;
        char t1 = str[a],t2 = str[b];
        char p1 = t1,p2 = t2;
        if(p1 > p2) std::swap(p1,p2);
        if(p1 == 'a' && p2 == 'b'){
            str[a] = str[b] = 'c';
        }
        if(p1 == 'a' && p2 == 'c'){
            str[a] = str[b] = 'b';
        }
        if(p1 == 'b' && p2 == 'c'){
            str[a] = str[b] = 'a';
        }
        int t = encode(str);
        if(!S.count(t)) dfs(str);
        str[a] = t1;str[b] = t2;
    }
}

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    scanf("%s",str+1);
    n = strlen(str+1);
    if(n <= 3){
        dfs(str);
        printf("%lu\n",S.size());
        return 0;
    }
    bool flag = true;
    FOR(i,2,n) if(str[i] != str[i-1]){
        flag = false;
        break;
    }
    if(flag){
        puts("1");
        return 0;
    }
    FOR(i,1,n) (sm += (str[i]-'a')) %= 3;
//    f[0][0][0/1/2][0/1] = 1;
    f[1][0][0][0] = f[1][1][1][0] = f[1][2][2][0] = 1;
    FOR(i,1,n-1){
        FOR(j,0,2){
            FOR(k,0,2){
                FOR(l,0,1){
                    FOR(x,0,2){
                        (f[i+1][(j+x)%3][x][l|(x==k)] += f[i][j][k][l]) %= ha;
                    }
                }
            }
        }
    }
    flag = 1;
    FOR(i,2,n) if(str[i] == str[i-1]){
        flag = 0;break;
    }
    printf("%lld\n",1ll*(1ll*f[n][sm][0][1]+1ll*f[n][sm][1][1]+1ll*f[n][sm][2][1]+flag)%ha);
    return 0;
}
