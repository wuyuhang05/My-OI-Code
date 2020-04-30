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
	int f,id,sz;
	Node(int f=0,int id=0,int sz=1) : f(f),id(id),sz(sz) {}
}sm[MAXN<<5];
int lc[MAXN<<5],rc[MAXN<<5],n,tot;

inline void build(int &v,int l,int r){
	v = ++tot;
	if(l == r) {sm[v] = Node(l,l);return;}
	int mid = (l + r) >> 1;
	build(lc[v],l,mid);build(rc[v],mid+1,r);
}

inline void insert(int prev,int &v,int l,int r,int p,Node d){
	sm[v = ++tot] = sm[prev];lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == r){
		sm[v] = d;return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) insert(lc[prev],lc[v],l,mid,p,d);
	else insert(rc[prev],rc[v],mid+1,r,p,d);
}

inline Node get(int x,int l,int r,int p){
	if(l == r) return sm[x];
	int mid = (l + r) >> 1;
	if(p <= mid) return get(lc[x],l,mid,p);
	else return get(rc[x],mid+1,r,p);
}

int now,root[MAXN];

inline int find(int x){
	int fx = get(root[now],1,n,x).f;
	return fx == x ? x : find(fx);
}

int main(){
	int m;scanf("%d%d",&n,&m);
	build(root[0],1,n);int las = 0;
	FOR(i,1,m){
		int opt;scanf("%d",&opt);
		if(opt == 1){
			int u,v;scanf("%d%d",&u,&v);u ^= las;v ^= las;
			Node x = get(root[now],1,n,find(u)),y = get(root[now],1,n,find(v));
			if(x.sz > y.sz) std::swap(x,y);
			insert(root[i-1],root[i],1,n,x.id,Node(y.id,x.id,x.sz));
			insert(root[i],root[i],1,n,y.id,Node(y.f,y.id,y.sz+x.sz));
			now = i;
		}
		if(opt == 2){
			int k;scanf("%d",&k);k ^= las;
			root[i] = root[k];now = i;
		}
		if(opt == 3){
			now = i;
			root[i] = root[i-1];
			int u,v;scanf("%d%d",&u,&v);u ^= las;v ^= las;
			u = find(u);v = find(v);
			printf("%d\n",las=(int)(u==v));
		} 
	}
	return 0;
}
/*
5 6
1 1 2
3 1 2
2 1
3 0 3
2 1
3 1 2
*/