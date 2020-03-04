/*
* Author: RainAir
* File Name: P3886.cpp
* Date: 2020-02-26 20:36:21
* Last Modified time: 2020-02-27 08:28:31
*/
#pragma GCC optimize("Ofast")
#include <unordered_map>
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
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10+1;
const int MAXM = 37486 + 1;
const int BASE = 9;

int f[2][MAXM],tot,now;
std::vector<int> rid[MAXM];
// std::unordered_map<int,int> id;
unsigned short int id[21913087+2];
// std::map<std::vector<int>,int> id;
int n,ans = -1e9;

int a[MAXN][MAXN];
int t[MAXN];

inline std::vector<int> trans(std::vector<int> a,int x){
	CLR(t,0);int cnt = 0;
	FOR(i,0,n-1){
		if(!a[i]) continue;
		if(!t[a[i]]) t[a[i]] = ++cnt;
		a[i] = t[a[i]];
	}
	if(cnt == 1) ans = std::max(ans,x);
	return a;
}
int mx = 0;
inline int encode(const std::vector<int> &a){
	int res = 0;
	for(auto x:a) res = (res<<3)|x;
	// for(auto x:a) res = 1ll*res*BASE+x+1;
	mx = std::max(mx,res);
	return res;
}

inline int ID(const std::vector<int> &a){
	int x = encode(a);
	if(!id[x]) id[x] = ++tot,rid[tot] = a;
	return id[x];
}

int main(){
	scanf("%d",&n);
	FOR(i,0,n-1) FOR(j,0,n-1) scanf("%d",&a[i][j]),ans = std::max(ans,a[i][j]);
	id[0] = tot = 1;
	rid[tot] = std::vector<int>(n,0);
	CLR(f,-0x3f);f[now][tot] = 0;
	FOR(i,0,n-1){
		FOR(j,0,n-1){
			int up = tot;
			FOR(k,1,up){
				std::vector<int> S = rid[k];
				//DEBUG(ans);//DEBUG(i);DEBUG(j);
				// for(auto x:S) printf("%d ",x);puts("");
				int l = !j ? 0 : S[j-1],u = S[j];S[j] = 0;
				// 不填
				int cnt = 0;
				for(auto x:S) if(x == u) cnt++;
				if(cnt || !u){
					int t = ID(trans(S,f[now][k]));
					f[now^1][t] = std::max(f[now^1][t],f[now][k]);
				}
				if(!l && !u){ // 填,成为新的连通分量
					S[j] = 10;
				}
				else{ // 填,连接之前的
					S[j] = std::max(l,u);
					for(auto &x:S) if(x && x == std::min(l,u)) x = std::max(l,u);
				}
				S = trans(S,f[now][k]+a[i][j]);
				int t = ID(S);
				f[now^1][t] = std::max(f[now^1][t],f[now][k]+a[i][j]);
			}
			// DEBUG(tot);
			CLR(f[now],-0x3f);now ^= 1;
		}
	}
	// DEBUG(mx);
	printf("%d\n",ans);
	return 0;
}
/*
9
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
*/