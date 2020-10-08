#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 100 + 5;
const int ha = 1e9 + 7;
const int prime[] = {0,11,13,17,19,23,29,31,37,41,43,47};
const int lcm = 32*27*25*49;

char str[MAXN][MAXN];int len[MAXN],n;
int ans[12][MAXN],t[12][MAXN],b[12][MAXN];
int cnt[2000000+5];
int res[MAXN];

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%s",str[i]+1),len[i] = strlen(str[i]+1);
	FOR(i,1,n){
		if(lcm%len[i]) continue;
		FOR(j,1,lcm) cnt[j] += (str[i][(j-1)%len[i]+1] == '1');
	}
	FOR(i,1,lcm) ans[(i-1)%12][cnt[i]]++;
	FOR(i,1,11){
		int p = prime[i];CLR(cnt,0);CLR(b,0);
		FOR(j,1,n){
			if(len[j]%p) continue;
			FOR(k,1,p*12){
				cnt[k] += (str[j][(k-1)%len[j]+1] == '1');
			}
		}
		FOR(j,1,p*12) b[(j-1)%12][cnt[j]]++;
		FOR(j,0,11) FOR(k,0,n) t[j][k] = ans[j][k],ans[j][k] = 0;
		// DEBUG(b[0][0]);
		FOR(j,0,11){
			FOR(x,0,n){
				FOR(y,0,n){
					// if(j == 0 && x == 2 && y == 0){
						// DEBUG(t[j][x]);DEBUG(b[j][y]);
						// DEBUG(t[j][x]*b[j][y]);
					// }
					if(x+y <= n) add(ans[j][x+y],1ll*t[j][x]*b[j][y]%ha);
				}
			}
		}
	// DEBUG(ans[0][2]);
	}
	FOR(i,0,11) FOR(j,0,n) add(res[j],ans[i][j]);
	int coe = 1;
	FOR(i,2,50){
		if(i == 32 || i == 27 || i == 25 || i == 49) continue;
		bool flag = 0;
		FOR(j,1,11) if(i == prime[j]){flag = 1;break;}
		if(flag) continue;
		coe = 1ll*coe*i%ha;
	}
	FOR(i,0,n) res[i] = 1ll*res[i]*coe%ha;
	FOR(i,0,n) printf("%d\n",res[i]);
	return 0;
}