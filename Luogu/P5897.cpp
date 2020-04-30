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

const int MAXN = 5000+5;
const int MAXM = 205+5;
const int BLO = 16;
int R[MAXN][MAXM],D[MAXN][MAXM];
int n,m;
int blo[MAXN];

struct Matrix{
	int a[MAXM][MAXM];
	
	friend Matrix operator * (const Matrix &A,const Matrix &B){
		Matrix C;
		static int s[MAXM][MAXM];
		FOR(i,0,m+1) FOR(j,0,m+1) s[i][j] = -1;
		FOR(i,1,m){
			ROF(j,m,1){
				int l = 1,r = m;
				if(s[i-1][j] != -1) l = std::max(l,s[i-1][j]);
				if(s[i][j+1] != -1) r = std::min(r,s[i][j+1]);
				C.a[i][j] = 1e9;
//				DEBUG(l);DEBUG(r);
				FOR(k,l,r){
					if(C.a[i][j] > A.a[i][k]+B.a[k][j]){
						C.a[i][j] = A.a[i][k]+B.a[k][j];
						s[i][j] = k;
					}
				}
			}
		}
		return C;
	}
	
	inline void debug(){
		puts("--- NEW MESSAGE ---");
		FOR(i,1,m) FOR(j,1,m) printf("%d%c",a[i][j]," \n"[j==m]);
		puts("--- END MESSAGE ---");
	}
}sm[(MAXN/BLO)<<2];

inline Matrix gen(int x){// 生成第 x 行的矩阵
	Matrix res;
	FOR(i,1,m){
		int sm = 0;
		FOR(j,i,m){
			res.a[i][j] = sm+D[x][j];
			sm += R[x][j];
		}
		sm = 0;
		ROF(j,i-1,1){
			sm += R[x][j];
			res.a[i][j] = sm+D[x][j];
		}
	}
	return res;
}

inline Matrix rebuild(int x){// 重构第 x 块
	int l = (x-1)*BLO+1,r = std::min(n,BLO*x);
	Matrix res = gen(l);
//	res.debug();
	FOR(i,l+1,r){
		res = res*gen(i);
//		exit(0);
//		res.debug();
	}
//	res.debug();
	return res;
}

#define lc ((x)<<1)
#define rc ((x)<<1|1)
inline void build(int x,int l,int r){
	if(l == r){
		sm[x] = rebuild(l);
		return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	sm[x] = sm[lc]*sm[rc];
}

inline void update(int x,int l,int r,int p){
	if(l == r){
		sm[x] = rebuild(l);
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc,l,mid,p);
	else update(rc,mid+1,r,p);
	sm[x] = sm[lc]*sm[rc];
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) blo[i] = 1+((i-1)/BLO);
	FOR(i,1,n) FOR(j,1,m-1) scanf("%d",&R[i][j]);
	FOR(i,1,n-1) FOR(j,1,m) scanf("%d",&D[i][j]);
	build(1,1,blo[n]);
//	sm[1].debug();
	int q;scanf("%d",&q);
	while(q--){
		int opt;scanf("%d",&opt);
		if(opt == 1){
			int x,y,w;scanf("%d%d%d",&x,&y,&w);++x;++y;
			R[x][y] = w;update(1,1,blo[n],blo[x]);
		}
		if(opt == 2){
			int x,y,w;scanf("%d%d%d",&x,&y,&w);++x;++y;
			D[x][y] = w;update(1,1,blo[n],blo[x]);
		}
		if(opt == 3){
			int x,y;scanf("%d%d",&x,&y);
			++x;++y;
			printf("%d\n",sm[1].a[x][y]);
		}
	}
	return 0;
}
/*
3 4
0 2 5
7 1 1
0 4 0
0 0 0 2
0 3 4 7
1
3 2 1
*/