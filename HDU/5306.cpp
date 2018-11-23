#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000000+5;

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
	int l,r,max,se,cnt;
	LL sum;
	SegmentTree *lc,*rc;
	
	static SegmentTree *build(int l,int r){
		int mid = (l + r) >> 1;
		return l == r ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
	}
	
	void pushup(){
		if(lc->max > rc->max){
			max = lc->max;
			se = std::max(lc->se,rc->max);
			cnt = lc->cnt;
		}
		if(lc->max == rc->max){
			max = lc->max;
			se = std::max(lc->se,rc->se);
			cnt = lc->cnt + rc->cnt;
		}
		if(lc->max < rc->max){
			max = rc->max;
			se = std::max(lc->max,rc->se);
			cnt = rc->cnt;
		}
		sum = lc->sum + rc->sum;
	}
	
	void cover(int delta){
		if(max <= delta) return;
		sum += 1ll*cnt*(delta-max);
		max = delta;
	}
	
	void pushdown(){
		lc->cover(max);
		rc->cover(max);
	}
	
	void update(int pos,int x){
		if(l == r){
			max = sum = x;
			se = -1;cnt = 1;
			return;
		}
		int mid = (l + r) >> 1;
		if(pos <= mid) lc->update(pos,x);
		else rc->update(pos,x);
		pushup();
	}
	
	void modify(int L,int R,int x){
		if(x >= max) return;
		if(L == l && R == r && x > se){
			cover(x);
			return;
		}
		pushdown();
		int mid = (l + r) >> 1;
		if(R <= mid) lc->modify(L,R,x);
		else if(L > mid) rc->modify(L,R,x);
		else lc->modify(L,mid,x),rc->modify(mid+1,R,x);
		pushup();
	}
	
	int qmax(int L,int R){
		if(L == l && R == r) return max;
		pushdown();
		int mid = (l + r) >> 1;
		if(R <= mid) return lc->qmax(L,R);
		if(L > mid) return rc->qmax(L,R);
		return std::max(lc->qmax(L,mid),rc->qmax(mid+1,R));
	}
	
	LL qsum(int L,int R){
		if(L == l && R == r) return sum;
		pushdown();
		int mid = (l + r) >> 1;
		if(R <= mid) return lc->qsum(L,R);
		if(L > mid) return rc->qsum(L,R);
		return lc->qsum(L,mid) + rc->qsum(mid+1,R);
	}
}pool[MAXN<<2],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
	SegmentTree *ret = ++frog;
	ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
	ret->max = ret->se = -1;ret->cnt = ret->sum = 0;
	return ret;
}

inline void Solve(){
	frog = pool;//CLR(pool,0);
	int N,M;scanf("%d%d",&N,&M);
	segt = SegmentTree::build(1,N);
	FOR(i,1,N){
		int x;scanf("%d",&x);
		segt->update(i,x);
	}
	while(M--){
		int opt,l,r;
		scanf("%d%d%d",&opt,&l,&r);
		if(opt == 0){
			int t;scanf("%d",&t);
			segt->modify(l,r,t);
		}
		if(opt == 1){
			printf("%d\n",segt->qmax(l,r));
		}
		if(opt == 2){
			printf("%lld\n",segt->qsum(l,r));
		}
	}
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}