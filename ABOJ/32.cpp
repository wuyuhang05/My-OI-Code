#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
int a[MAXN],n,top=1;
int t[MAXN],l,r,min[MAXN];
std::vector<int> ans;

int main(){
//	freopen("stack.in","r",stdin);
//	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	min[n] = a[n];ROF(i,n-1,1) min[i] = std::min(min[i+1],a[i]);
	l = top = 1;
	while(l <= r || top <= n){
		if(top > n){
			while(l <= r){
				if(t[l] < t[r]) ans.push_back(t[l++]);
				else ans.push_back(t[r--]);
			}
			break;
		}
		if(l > r || (min[top] <= t[l] && min[top] <= t[r])){
			int k = min[top];
			while(a[top] != k) t[++r] = a[top++];
			ans.push_back(k);top++;
		}
		else{
			if(t[l] < t[r]) ans.push_back(t[l++]);
			else ans.push_back(t[r--]);
		}
	}
	FOR(i,0,(int)ans.size()-1) printf("%d%c",ans[i],(i == ans.size()-1) ? '\n' : ' ');
	return 0;
}
