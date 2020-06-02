#include "messy.h"
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
int n;

inline void build(int l,int r){
	if(l == r) return;
	int mid = (l + r) >> 1;
	std::string str(n+1,'0');
	FOR(i,l,r) str[i] = '1';
	FOR(i,l,mid) str[i] = '0',add_element(str),str[i] = '1';
	build(l,mid);build(mid+1,r);
}

std::vector<int> ans;
inline void query(int l,int r,std::string &str){
	if(l == r){
		FOR(i,0,n) if(str[i] == '1') ans[i] = l;//,DEBUG(l);
		return;
	}
	int mid = (l + r) >> 1;
	std::string toL(str),toR(str);
	int tot = 0;
	FOR(i,0,n){
		if(str[i] == '1'){
			str[i] = '0';
			int t = check_element(str);
			str[i] = '1';
			if(t) toR[i] = '0';
			else toL[i] = '0';
		}
	}
	// DEBUG(l);DEBUG(r);DEBUG(tot);
	query(l,mid,toL);query(mid+1,r,toR);
}

std::vector<int> restore_permutation(int n,int w,int r){
	build(0,::n=n-1);ans.resize(n);
	compile_set();
	std::string str(n,'1');
	query(0,::n,str);
	return ans;
}