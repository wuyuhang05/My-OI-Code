#include<bits/stdc++.h>

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

const int MAXN = 5e5 + 5;
int n,a[MAXN];

int st[MAXN],tp;
LL pre[MAXN],suf[MAXN],sm[MAXN],t[MAXN];
#define X(i) (i)
#define Y(i) (t[i]+sm[i]+(1ll*i*i-i)/2.0)

inline double slope(int x,int y){ // x-y
	return (Y(x)-Y(y))/(X(x)-X(y));
}

inline void dp(){
	FOR(i,1,n) sm[i] = sm[i-1]+a[i];st[tp = 1] = 0;
	FOR(i,1,n){
		while(tp > 1 && slope(st[tp-1],st[tp]) <= i) tp--;
		int j = st[tp];
		// if(i == 2) DEBUG(j),DEBUG(t[j]+(i-j)*(i-j+1)/2-sm[i]+sm[j]);
		t[i] = std::max(t[i-1],t[j]+1ll*(i-j)*(i-j+1)/2-sm[i]+sm[j]);
		while(tp > 1 && slope(st[tp-1],st[tp]) < slope(st[tp],i)) tp--;
		st[++tp] = i;
	}
}

LL f[MAXN],ans[MAXN],tmp[MAXN];

inline void cdq(int l,int r){
	if(l == r){
		f[l] = std::max(f[l],pre[l-1]+suf[r+1]+1-a[l]);
		return;
	}
	int mid = (l + r) >> 1;
	st[tp = 1] = l-1;
	FOR(i,l,mid-1){
		while(tp > 1 && slope(st[tp-1],st[tp]) < slope(st[tp],i)) tp--;
		st[++tp] = i;
	}
	FOR(i,mid,r){
		while(tp > 1 && slope(st[tp-1],st[tp]) <= i) tp--;
		int j = st[tp];
		tmp[i] = t[j]+1ll*(i-j)*(i-j+1)/2-sm[i]+sm[j]+suf[i+1];
	}
	ROF(i,r-1,mid) tmp[i] = std::max(tmp[i+1],tmp[i]);
	FOR(i,mid,r) f[i] = std::max(f[i],tmp[i]);
	cdq(l,mid);cdq(mid+1,r);
}

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	dp();FOR(i,1,n) pre[i] = t[i],t[i] = 0;
	std::reverse(a+1,a+n+1);dp();std::reverse(t+1,t+n+1);std::reverse(a+1,a+n+1);
	FOR(i,1,n) suf[i] = t[i],t[i] = 0,ans[i] = -1e18;

	FOR(i,1,n) t[i] = pre[i],sm[i] = sm[i-1]+a[i],f[i] = -1e18;cdq(1,n);
	FOR(i,1,n) ans[i] = std::max(ans[i],f[i]);

	std::reverse(a+1,a+n+1);std::reverse(pre+1,pre+n+1);std::reverse(suf+1,suf+n+1);
	std::swap(pre,suf);
	FOR(i,1,n) t[i] = pre[i],sm[i] = sm[i-1]+a[i],f[i] = -1e18;cdq(1,n);
	std::reverse(f+1,f+n+1);
	FOR(i,1,n) ans[i] = std::max(ans[i],f[i]);
	std::reverse(a+1,a+n+1);std::reverse(pre+1,pre+n+1);std::reverse(suf+1,suf+n+1);
	std::swap(pre,suf);

	// FOR(i,1,n) DEBUG(ans[i]);

	int q;scanf("%d",&q);
	while(q--){
		int x,y;scanf("%d%d",&x,&y);
		printf("%lld\n",std::max(pre[x-1]+suf[x+1],ans[x]+a[x]-y));
	}
	return 0;
}