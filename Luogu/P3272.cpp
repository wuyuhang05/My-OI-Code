/*
* @Author: apple2
* @Date:   2020-02-25 18:30:07
* @Last Modified by:   apple2
* @Last Modified time: 2020-02-25 18:30:14
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 12+1;
const int MAXM = 3e5 + 5;
const int ha = 20110520;
int pw[MAXN];
char str[100+5][100+5],t[100+5][100+5];
int n,m;
int f[2][MAXM];
int now;

inline void add(int &x,int y){
	(x += y);if(x >= ha) x -= ha;
}

int main(){
	pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = pw[i-1]*3;
	scanf("%d%d",&n,&m);
	FOR(i,0,n-1) scanf("%s",str[i]);
	if(n < m){
		FOR(i,0,n-1) FOR(j,0,m-1) t[j][i] = str[i][j];
		std::swap(n,m);CLR(str,0);
		FOR(i,0,n-1) FOR(j,0,m-1) str[i][j] = t[i][j];
	}
	f[now][0] = 1;
	FOR(i,0,n-1){
		FOR(j,0,m-1){
			FOR(S,0,pw[m+1]-1){
				int l = S/pw[m]%3,u = S/pw[j]%3,nxt = S-l*pw[m]-u*pw[j];
				// int ii,jj;
				// if(j == m-1) ii = i+1,jj = 0;
				// else ii = i,jj = j+1;
				// int l = S/pw[j]%3,u = S/pw[m]%3,nxt = S-l*pw[j]-u*pw[m];
				if(str[i][j] == '*'){
					if(!l && !u) add(f[now^1][nxt],f[now][S]); // ?? -> 00 注意了:这里必须要限制没有插头 草
					continue;
				}
				if(!l && !u){ // 00
					if(i != n-1 && j != m-1) add(f[now^1][nxt+2*pw[j]+2*pw[m]],f[now][S]); // 00 -> 22
					if(i != n-1) add(f[now^1][nxt+pw[j]],f[now][S]); // 00 -> 10
					if(j != m-1) add(f[now^1][nxt+pw[m]],f[now][S]);// 00 -> 01
				}
				if(!l && u == 1){ // 01
					if(i != n-1) add(f[now^1][nxt+pw[j]],f[now][S]); // 01 -> 10
					if(j != m-1) add(f[now^1][nxt+2*pw[m]],f[now][S]); // 01 -> 02
				}
				if(!l && u == 2){ // 02
					if(i != n-1) add(f[now^1][nxt+pw[j]*2],f[now][S]);// 02 -> 20
					add(f[now^1][nxt],f[now][S]);// 02 -> 00
				}
				if(l == 1 && !u){ // 10
					if(j != m-1) add(f[now^1][nxt+pw[m]],f[now][S]);// 10 -> 01
					if(i != n-1) add(f[now^1][nxt+pw[j]*2],f[now][S]);// 10 -> 20
				}
				if(l == 1 && u == 1){ // 11
					add(f[now^1][nxt],f[now][S]); // 11 -> 00
				}
				if(l == 1 && u == 2){ // 12
					continue;
				}
				if(l == 2 && !u){ // 20
					add(f[now^1][nxt],f[now][S]);// 20 -> 00
					if(j != m-1) add(f[now^1][nxt+2*pw[m]],f[now][S]);// 20 -> 02
				}
				if(l == 2 && u == 1){ // 21
					continue;
				}
				if(l == 2 && u == 2){ // 22
					continue;
				} 
			}
			CLR(f[now],0);now ^= 1;
			// DEBUG(i);DEBUG(j);DEBUG(f[now][0]);
			// if(i == n && j == 0) break;
		}
	}
	printf("%d\n",f[now][0]);
	return 0;
}
/*
插头 dp:状态:
0. 无插头
1. 还没有被连成 L 形的插头(允许拐弯)
2. 已经被连成 L 形的插头(不允许拐弯)
要注意 2 状态可以终止
*/