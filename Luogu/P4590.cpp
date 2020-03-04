/*
* Author: RainAir
* File Name: P4590.cpp
* Date: 2020-02-28 10:08:12
* Last Modified time: 2020-02-28 11:37:20
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

const int MAXN = 1000+5;
const int MAXK = 15+1;
const int ha = 1e9 + 7;
int f[2][3][(1<<MAXK)+3],now = 0;
int n,m;
char str[MAXN];
int T[MAXN];
int nxt[3][3];
int tmp[MAXN],ntmp[MAXN];

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

int ans[MAXN],pc[(1<<MAXK)+3];

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	FOR(i,1,m) T[i] = str[i] == 'N' ? 0 : (str[i] == 'O' ? 1 : 2);
	nxt[0][0] = 1;
	nxt[1][0] = 1;nxt[1][1] = 2;
	nxt[2][0] = 1;nxt[2][2] = 3;
	f[now = 0][0][0] = 1;
	FOR(i,1,n){
		FOR(j,0,2){
			FOR(S,0,(1<<m)-1){
				if(!f[now][j][S]) continue;
				FOR(x,0,2){
					if(nxt[j][x] == 3) continue;
					FOR(k,1,m) tmp[k] = tmp[k-1]+((S>>(k-1))&1);
					FOR(k,1,m) ntmp[k] = std::max(ntmp[k-1],std::max(tmp[k],tmp[k-1]+(T[k]==x)));
					int nS = 0;
					FOR(k,1,m) nS |= ((ntmp[k]-ntmp[k-1])<<(k-1));
					add(f[now^1][nxt[j][x]][nS],f[now][j][S]);
				}
			}
		}
		CLR(f[now],0);
		now ^= 1;
	}
	FOR(S,0,(1<<m)-1){
		pc[S] = pc[S>>1]+(S&1);
		FOR(j,0,2) add(ans[pc[S]],f[now][j][S]);
	}
	FOR(i,0,m) printf("%d\n",ans[i]);
	return 0;
}
/*
考虑判定性问题:设 f[i][j] 表示 A 匹配到了 i B 匹配到了 j 的长度
// f[i][j] -> f[i+1][j]
f[i] -> g[i]
// f[i][j] -> f[i][j+1]
f[i] -> g[i+1]
// f[i][j]+1 -> f[i+1][j+1] if str[i+1]==str[j+1]
f[i]+1 -> g[i+1]

先不考虑 NOI 的限制:f[i][S] 表示填了前 i 位 当前的dp 状态是S(也就是和 K 的每一个前缀比较的答案) 的串的个数
枚举这里填什么 挨个更新就可以
还要再记录一个和 NOI 匹配到了第几位 
*/