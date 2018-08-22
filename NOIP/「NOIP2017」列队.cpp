#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define LL long long

const int MAXN = 300000 + 5;
const int MAXM = 10000000 + 5;

LL N,M,Q,M_N;

inline void Read(LL &x){
	x = 0;char ch = getchar();
	LL flag = 1;
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-') flag = -1;
	for(;isdigit(ch);ch = getchar())
		x = (x << 1) + (x << 3) + ch - '0';
	x *= flag;
}

struct SegmentTree {
	LL val;
	SegmentTree *lc,*rc;

	void pushup(){
		val = 0;
		if(lc) val += lc->val;
		if(rc) val += rc->val;
	}
}pool[MAXM],*frog = pool;

SegmentTree *New(){
	SegmentTree *ret = ++frog;
	ret->lc = ret->rc = NULL;
	ret->val = 1;
	return ret;
}

SegmentTree *root[MAXN];
std::vector<LL> v[MAXN];

LL query(SegmentTree *v,LL l,LL r,LL x){
	if(!v) return l + x - 1;
	if(l == r) return l;
	int mid = (l + r) >> 1,val = (v->lc == NULL ? 0 : v->lc->val);
	int h = mid - l + 1 - val;
	if(h >= x) return query(v->lc,l,mid,x);
	return query(v->rc,mid + 1,r,x-h);
}

void del(SegmentTree* &v,LL l,LL r,LL x){
	if(!v) v = New();
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) del(v->lc,l,mid,x);
	else del(v->rc,mid + 1,r,x);
	v->pushup();
}

LL del_row(LL x){
	LL id = query(root[N + 1],1,M_N,x);
	del(root[N + 1],1,M_N,id);
	if(id > N) return v[N+1][id-N-1];
	return id*M;
}

LL del_line(LL x,LL y){
	LL id = query(root[x],1,M_N,y);
	del(root[x],1,M_N,id);
	if(id >= M) return v[x][id-M];
	return (x-1)*M+id;
}

int main(){
	Read(N);Read(M);Read(Q);
	M_N = std::max(N,M) + Q;
	for(int i = 1;i <= N + 1;i++) root[i] = NULL;
	while(Q--){
		LL x,y;
		Read(x);Read(y);
		if(y == M){
			LL id = del_row(x);
			v[N + 1].push_back(id);
			printf("%lld\n",id);
		}
		else{
			LL id1 = del_line(x,y),id2 = del_row(x);
			v[x].push_back(id2);v[N + 1].push_back(id1);
			printf("%lld\n",id1);
		}
	}
	//getchar();getchar();
	return 0;
}