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
#define P std::pair<double,Node *>
#define MP std::make_pair
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

struct Node{
	int pos,len;
	bool operator < (const Node &other) const {
		if(len/2 == other.len/2) return pos < other.pos;
		return len/2 > other.len/2;
	}
};

const int MAXN = 1000000 + 5;

std::set<Node> S;
std::set<int> b;
int p[MAXN];
int L=-1,R=-1;
#define read(x) std::cin >> x
int N,M;

int main(){
	read(N);read(M);
	while(M--){
		int opt,x;
		read(opt);read(x);
		if(opt & 1){
			int len=0,pos=0;
			if(L == -1){
				len = 1;pos = 1;
				p[x] = pos;
				L = R = 1;
			}
			else{
				if(L >= N-R+1) len = L,pos = 1;
				else len = N-R+1,pos = N;
				if(S.empty()){
					p[x] = pos;
					if(pos < L) S.insert((Node){pos,L-pos}),L = pos;
					else S.insert((Node){L,pos-L}),R = pos;
				}
				else{
					Node v = *S.begin();
					int mid = v.pos + v.len/2;
					int dist = mid - v.pos + 1;
					if(len < dist || len == dist && pos >= mid) len = dist,pos = mid;
					p[x] = pos;
					if(pos == 1){
						S.insert((Node){pos,L-pos});
						L = pos;
					} 
					else if(pos == N){
						S.insert((Node){R,pos-R});
						R = pos;
					}
					else{
						S.erase(S.begin());
						int l = v.pos,r=v.pos+v.len;
						S.insert((Node){l,pos-l}); 
						S.insert((Node){pos,r-pos});
					}
				}
			}
			printf("%d\n",p[x]);
			b.insert(p[x]);
		}
		else{
			int pos = p[x];
			p[x] = 0;
			std::set<int>::iterator it = b.find(pos);
			if(S.empty()) L = -1,R = -1;
			else if(pos == L){
				L = *(++it);
				S.erase((Node){pos,L-pos});
			}
			else if(pos == R){
				R = *(--it);
				S.erase((Node){R,pos-R});
			}
			else{
				int next = *(++it);
				it--;int pre = *(--it);
				S.erase((Node){pre,pos-pre});
				S.erase((Node){pos,next-pos});
				S.insert((Node){pre,next-pre});
			}
			b.erase(pos);
		}
	}
	return 0;
}


