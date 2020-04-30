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

const int MAXN = 2e5 + 5;

struct Node{
	LL x;int y;
	Node(LL x=-1e16,int y=0) : x(x),y(y) {}
	friend Node operator + (const Node &a,const Node &b){
		return a.x > b.x ? a : b;
	}
}sm[MAXN<<5];
LL tag[MAXN<<5];int lc[MAXN<<5],rc[MAXN<<5],tot;

inline void modify(int prev,int &v,int l,int r,int L,int R,int d){
	sm[v=++tot] = sm[prev];tag[v] = tag[prev];lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == L && r == R){
		tag[v] += d;sm[v].x += d;
		return;
	}
	int mid = (l + r) >> 1;
	if(R <= mid) modify(lc[prev],lc[v],l,mid,L,R,d);
	else if(L > mid) modify(rc[prev],rc[v],mid+1,r,L,R,d);
	else modify(lc[prev],lc[v],l,mid,L,mid,d),modify(rc[prev],rc[v],mid+1,r,mid+1,R,d);
	sm[v] = sm[lc[v]]+sm[rc[v]];sm[v].x += tag[v];
}

inline Node query(int x,int l,int r,int L,int R){
	if(l == L && r == R) return sm[x];
	int mid = (l + r) >> 1;
	Node ret;
	if(R <= mid) ret = ret+query(lc[x],l,mid,L,R);
	else if(L > mid) ret = ret+query(rc[x],mid+1,r,L,R);
	else ret = ret+query(lc[x],l,mid,L,mid)+query(rc[x],mid+1,r,mid+1,R);
	ret.x += tag[x];
	return ret;
}

inline void build(int &x,int l,int r){
	x = ++tot;sm[x] = Node(0,l);tag[x] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lc[x],l,mid);build(rc[x],mid+1,r);
}

int n;
int a[MAXN],pre[MAXN],root[MAXN];
std::map<int,int> S;

struct node{
	int p,l,r,a;LL s;// [[l,r],p] maxpos=a  maxans=s
	node(int p=0,int l=0,int r=0) : p(p),l(l),r(r) {
		Node t = query(root[p],1,n,l,r);
		a = t.y;s = t.x;
	}
	
	bool operator < (const node &t) const {
		return s < t.s;
	}
};
std::priority_queue<node> q;

int main(){
//	freopen("../TestData/1.in","r",stdin);
	int k;scanf("%d%d",&n,&k);
	build(root[0],1,n);
	FOR(i,1,n){
		scanf("%d",a+i);
		pre[i] = S[a[i]];S[a[i]] = i;
		modify(root[i-1],root[i],1,n,pre[i]+1,i,a[i]);
		q.push(node(i,1,i));
	}
	LL ans=-1;
	while(k--){
		node v = q.top();q.pop();ans = v.s;
		if(v.l < v.a){
			q.push(node(v.p,v.l,v.a-1));
		}
		if(v.a < v.r){
			q.push(node(v.p,v.a+1,v.r));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*
7 5
3 -2 1 2 2 1 3 -2
*/