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
const int MAXN = 2e6 + 5;
inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

int b[233],c[555];
int n,q;
std::unordered_map<int,int> S;
int ts[MAXN],a[MAXN],sz;

inline void insert(int x,int tm){
	// DEBUG(tm);
	ROF(i,n-1,0){
		if((x>>i)&1){
			if(!b[i]){
				b[i] = x;c[i] = tm;++sz;return;
			}
			if(tm > c[i]){
				std::swap(tm,c[i]);std::swap(x,b[i]);
			}
			x ^= b[i];
		}
	}
}

inline void del(int tm){
	FOR(i,0,n-1) if(c[i] == tm){b[i]=c[i]=0;--sz;return;}
}

int main(){
	read(n);read(q);
	std::fill(ts+1,ts+q+1,q+1);
	FOR(i,1,q){
		int opt,x;read(opt);read(x);
		if(opt == 1){
			S[x] = i;a[i] = x;
		}
		else{
			ts[S[x]] = i;//DEBUG(S[x]);
			ts[i] = 0;
		}
	}
	int res = 0;
	FOR(i,1,q){
		// printf("%d\n",ts[i]);
		if(ts[i]) insert(a[i],ts[i]);
		else del(i);
		// DEBUG(sz);
		res ^= (1<<(n-sz));
	}
	printf("%d\n",res);
	return 0;
}