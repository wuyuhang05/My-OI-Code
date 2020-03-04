/*
* Author: RainAir
* File Name: P5056.cpp
* Date: 2020-02-26 11:21:45
* Last Modified time: 2020-02-26 16:24:30
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

const int MAXN = 20 + 1;
const int MAXM = 1e6 + 5;

int pw[MAXN];
// 0: 0 1: left 2: right
int n,m;
int ID[MAXM],rID[MAXM],tot;
char str[MAXN][MAXN];
LL f[2][MAXM];int now;
int trans[MAXM][20],tmp[20],st[20],tp;

inline void chk(int S){
	int now = 0;
	FOR(i,0,m){
		int t = S/pw[i]%3;tmp[i] = t;
		now += t == 1 ? 1 : (t == 2 ? -1 : 0);
		if(now < 0) return;
	}
	if(now) return;
	ID[S] = ++tot;rID[tot] = S;tp = 0;
	FOR(i,0,m){
		if(tmp[i] == 1) st[++tp] = i;
		if(tmp[i] == 2) trans[tot][i] = st[tp],trans[tot][st[tp]] = i,tp--;
	}
}

int epx=-1,epy=-1;

int main(){
	pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 1ll*pw[i-1]*3;
	scanf("%d%d",&n,&m);
	FOR(i,0,n-1) scanf("%s",str[i]);
	ROF(i,n-1,0){
		ROF(j,m-1,0){
			if(str[i][j] == '.'){
				epx = i;epy = j;break;
			}
		}
		if(epx != -1) break;
	}
	FOR(S,0,pw[m+1]-1) chk(S);
	f[now][ID[0]] = 1;
	FOR(i,0,n-1){
		FOR(j,0,m-1){
			FOR(k,1,tot){
				int S = rID[k];
				int l = S/pw[j]%3,u = S/pw[j+1]%3,nxt = S-pw[j]*l-pw[j+1]*u;
				if(str[i][j] == '*'){
					if(!l && !u) f[now^1][ID[nxt]] += f[now][k];
					continue;
				}
				if(!l && !u){ // ##
					f[now^1][ID[nxt+pw[j]+2*pw[j+1]]] += f[now][k]; // ## -> ()
					continue;
				}
				if(l && u){ // 
					if(l == 1 && u == 2){
						if(i == epx && j == epy) f[now^1][ID[nxt]] += f[now][k];
						continue;
					}
					int ll = trans[k][j],rr = trans[k][j+1];
					nxt -= (S/pw[ll]%3)*pw[ll];nxt -= (S/pw[rr]%3)*pw[rr];
					if(ll > rr) std::swap(ll,rr);
					nxt += pw[ll];nxt += 2*pw[rr];
					f[now^1][ID[nxt]] += f[now][k];
					continue;
				}
				if(l || u){
					f[now^1][k] += f[now][k];// 拐个弯
					f[now^1][ID[nxt+l*pw[j+1]+u*pw[j]]] += f[now][k];
				}
			}
			CLR(f[now],0);
			now ^= 1;
		}
		FOR(k,1,tot) if(rID[k] < pw[m]) f[now^1][ID[rID[k]*3]] += f[now][k];
		CLR(f[now],0);now ^= 1;
	}
	printf("%lld\n",f[now][ID[0]]);
	return 0;
}