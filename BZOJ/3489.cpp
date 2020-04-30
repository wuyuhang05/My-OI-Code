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

const int MAXN = 200000+5;
int dir;
struct Node{
	int pos[3],val;	
	
	bool operator < (const Node &t) const {
		return pos[dir] < t.pos[dir];
	}
}v[MAXN];

int mx[MAXN][3],mn[MAXN][3],sm[MAXN];
int ch[MAXN][2];
#define lc (ch[x][0])
#define rc (ch[x][1])

inline void pushup(int x){
	sm[x] = v[x].val;//DEBUG(sm[x]);
	FOR(i,0,2) mx[x][i] = mn[x][i] = v[x].pos[i];
	FOR(i,0,1){
		int p = ch[x][i];
		if(p){
			FOR(i,0,2) mx[x][i] = std::max(mx[x][i],mx[p][i]),
			mn[x][i] = std::min(mn[x][i],mn[p][i]);
			sm[x] = std::max(sm[x],sm[p]);
		}
	}
}

inline int build(int l,int r,int dir){
	::dir = dir;
	if(l > r) return 0;
	if(l == r){pushup(l);return l;}
	int mid = (l + r) >> 1;
	std::nth_element(v+l,v+mid,v+r+1);
	ch[mid][0] = build(l,mid-1,(dir+1)%3);
	ch[mid][1] = build(mid+1,r,(dir+1)%3);
	pushup(mid);return mid;
}
// (i,pre[i],suf[i])
int ans;// kdtree 剪枝必备
inline void query(int x,int l,int r){
//	DEBUG(x);
	if(!x) return;
	if(mx[x][0] < l || mn[x][0] > r || mn[x][1] >= l || mx[x][2] <= r || sm[x] <= ans) return;
	if(mn[x][0] >= l && mx[x][0] <= r && mx[x][1] < l && mn[x][2] > r)
		{ans = std::max(ans,sm[x]);return;}
	if(v[x].pos[0] >= l && v[x].pos[0] <= r && v[x].pos[1] < l && v[x].pos[2] > r)
		ans = std::max(ans,v[x].val);// 注意统计每个点
	query(lc,l,r);query(rc,l,r);
}
int a[MAXN],pre[MAXN],suf[MAXN],t[MAXN];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",a+i);
		pre[i] = t[a[i]];t[a[i]] = i;
	}
	std::fill(t,t+n+1,n+1);
	ROF(i,n,1) suf[i] = t[a[i]],t[a[i]] = i;
	FOR(i,1,n) v[i].pos[0] = i,v[i].pos[1] = pre[i],v[i].pos[2] = suf[i],v[i].val = a[i];
	int rt = build(1,n,0);
	FOR(i,1,m){
		int l,r;scanf("%d%d",&l,&r);
		l = (l+ans)%n+1;r = (r+ans)%n+1;
		if(l > r) std::swap(l,r);
		ans = 0;query(rt,l,r);
		printf("%d\n",ans);
	}
	return 0;
}
/*
l <= i <= r
pre[i] < l
suf[i] > r
*/
/*
10 10
6 4 9 10 9 10 9 4 10 4 
3 8
10 1
3 4
9 4
8 1
7 8
2 9
1 1
7 3
9 9
*/