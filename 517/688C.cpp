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

const int MAXN = 1e5 + 5;
char str[MAXN];
int a[MAXN],n;

inline void work(int l,int r){
	if(l >= r) return;
	int mid = (l + r) >> 1;
}

int main(){
	scanf("%s",str+1);n = strlen(str+1);
	FOR(i,1,n) a[i] = str[i]-'a'+1;
	work(1,n);
	return 0;
}