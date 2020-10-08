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

const int MAXN = 1e6 + 5;
int n,k;

inline void f(char str[],char res[],int &tp){
	static int len[MAXN],t[MAXN];
	tp = 0;t[0] = -1;len[0] = 0;
	FOR(i,1,n){
		++tp;res[tp] = str[i];
		if(str[i]-'a' == t[tp-1]){
			len[tp] = len[tp-1]+1;
			t[tp] = t[tp-1];
		}
		else{
			len[tp] = 1;
			t[tp] = str[i]-'a';
		}
		while(tp > 0 && len[tp] == k) tp -= k;
	}
	// DEBUG(tp);
}

char s[MAXN],t[MAXN];
char ts[MAXN],tt[MAXN];

inline void Solve(){
	scanf("%d%d",&n,&k);
	scanf("%s%s",s+1,t+1);
	int t1=0,t2=0;
	f(s,ts,t1);f(t,tt,t2);
	bool flag = t1==t2;
	FOR(i,1,t1) flag &= (ts[i]==tt[i]);
	puts(flag?"Yes":"No");
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}