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

const int MAXN = 3e5 + 5;
const int MAXM = 29;
int a[MAXN],n;
std::vector<int> G[MAXM+1];
bool del[MAXN];

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i),del[i] = 0;
	FOR(i,1,n){
		ROF(j,MAXM,0){
			if((a[i]>>j)&1){
				G[j].pb(i);
				break;
			}
		}
	}
	int sz = n;
	ROF(j,MAXM,0){
		int s = 0;LL g = 0;
		FOR(i,1,n){
			if(del[i]) continue;
			if((a[i]>>j)&1) ++s,del[i] = 1;
			else g += s; 
		}
		LL all = sz*(sz-1)/2;
		if(g >= all-g) continue;
	}
	return 0;
}