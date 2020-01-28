#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)
int tag[MAXN<<2],rev[MAXN<<2],val[MAXN<<2];

inline void cover(int x,int d){
	val[x] = tag[x] = d;rev[x] = 0;
}

inline void reverse(int x){
	rev[x] ^= 1;val[x] ^= 1;
}

inline void pushdown(int x){
	if(tag[x] != -1){
		cover(lc,tag[x]);
		cover(rc,tag[x]);
		tag[x] = -1;
	}
	if(rev[x]){
		reverse(lc);
		reverse(rc);
		rev[x] = 0;
	}
}

inline void modify(int x,int l,int r,int L,int R,int d){
	if(l == L && r == R){
		d <= 1 ? cover(x,d) : reverse(x);
		return;
	}
	pushdown(x);
	int mid = (l + r) >> 1;
	if(R <= mid) modify(lc,l,mid,L,R,d);
	else if(L > mid) modify(rc,mid+1,r,L,R,d);
	else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
}

inline int query(int x,int l,int r,int p){
	if(l == r) return val[x];
	int mid = (l + r) >> 1;
	pushdown(x);
	if(p <= mid) return query(lc,l,mid,p);
	else return query(rc,mid+1,r,p);
}

inline void build(int x,int l,int r){
	tag[x] = -1;rev[x] = val[x] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
}

char opt[MAXN],str[MAXN];
const int MAX = 150000;

int main(){
	build(1,1,MAX);
	while(~scanf("%s",opt)){
		scanf("%s",str);
		int l = 0,r = 0,tot = 1;
		while(str[tot] != ',') l = l*10+str[tot++]-'0';
		++tot;
		while(isdigit(str[tot])) r = r*10+str[tot++]-'0';
		++l;++r;
		l *= 2;r *= 2;
		if(str[0] == '(') l++;
		if(str[tot] == ')') r--;
		// DEBUG(l);DEBUG(r);
		if(opt[0] == 'U'){
			if(l <= r) modify(1,1,MAX,l,r,1);
		}
		if(opt[0] == 'I'){
			modify(1,1,MAX,1,l-1,0);
			modify(1,1,MAX,r+1,MAX,0);
		}
		if(opt[0] == 'D'){
			if(l <= r) modify(1,1,MAX,l,r,0);
		}
		if(opt[0] == 'C'){
			modify(1,1,MAX,1,l-1,0);
			modify(1,1,MAX,r+1,MAX,0);
			if(l <= r) modify(1,1,MAX,l,r,2);
		}
		if(opt[0] == 'S'){
			if(l <= r) modify(1,1,MAX,l,r,2);
		}
	}
	int l = -1;bool flag = 0;
	FOR(r,1,MAX){
		int t = query(1,1,MAX,r);
		if(t){
			if(l != -1) continue;
			else l = r;
		}
		else{
			if(l == -1) continue;
			else{
				printf("%c%d,%d%c ",(l&1?'(':'['),l/2-1,r/2-1,(!(r&1)?')':']'));
				l = -1;flag = true;
			}
		}
	}
	if(!flag) puts("empty set");
	return 0;
}