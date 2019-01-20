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

#define ll LL
#define qwq std
#define fi first
#define se second
#define U unsigned
#define Re register
#define LL long long
#define MP qwq::make_pair
#define read(x) scanf("%d",&x)
#define P qwq::pair<double,int>
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = (a);i <= (b);++i)
#define ROF(i,a,b) for(Re int i = (a);i >= (b);--i)
#define EFOR(v) for(Re int i = hd[v];i;i = nx[i])
#define SFOR(i,a,b,step) for(Re int i = (a);i <= (b);i += c)
#define SROF(i,a,b,step) for(Re int i = (a);i >= (b);i -= c)
#define DEBUG(x) qwq::cerr << #x << '=' << (x) << std::endl
#define ll long long
#define N 200005
#define M 600005
using namespace std;
int n,m,k,cnt=1,tot,rt;
int nxt[N*6],num[N*6],q[N],fa[N*2];
ll ans1,ans2;
ll s[N*2],s2[N*2];
bool vst[N*2],flg[N*6];
struct P{
	ll x,y;
	friend P operator +(const P &a,const P &b){return (P){a.x+b.x,a.y+b.y};}
	friend P operator -(const P &a,const P &b){return (P){a.x-b.x,a.y-b.y};}
	friend ll operator *(const P &a,const P &b){return a.x*b.y-a.y*b.x;}
}p[N];
struct edge
{
	int x,y,id;double angle;
	edge(int xx=0,int yy=0,int idd=0)
	{
		x=xx;y=yy;id=idd;
		angle=atan2((double)(p[y].y-p[x].y),(double)(p[y].x-p[x].x));
	}
	friend bool operator <(const edge &a,const edge &b){return a.angle<b.angle;}
}e[N*6];
vector<edge> E[N],G[N*2];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline int find(int x,const edge &tmp)
{
	return lower_bound(E[x].begin(),E[x].end(),tmp)-E[x].begin();
}
inline ll gcd(ll x,ll y)
{
	return y?gcd(y,x%y):x;
}
void solve()//平面图转对偶图 
{
	int now,tmp,st;ll area;
	F(i,2,cnt) if (!num[i])
	{
		area=0;now=i;st=e[i].x;num[i]=++tot;
		while (1)
		{
			int tmp=nxt[now];num[tmp]=tot;
			if (e[tmp].y==st) break;
			area+=(p[e[tmp].x]-p[st])*(p[e[tmp].y]-p[st]);
			now=tmp;
		}
		s[tot]=area;s2[tot]=area*area;
		if (area<=0) rt=tot;
	}
	F(i,2,cnt) G[num[i]].push_back(edge(num[i],num[i^1],i));
}

bool vis[N];
int ans[N];
double dis[N];

inline void spfa(){
    qwq::priority_queue<P> q;
    CLR(dis,0x7f);dis[1] = 0;
    q.push(MP(0.0,1));
    while(!q.empty){

    }
}

int main()
{
	n=read();m=read();k=read();
	F(i,1,n) p[i].x=read(),p[i].y=read();
	F(i,1,m)
	{
		int x=read(),y=read();
		cnt++;e[cnt]=edge(x,y,cnt);E[x].push_back(e[cnt]);
		cnt++;e[cnt]=edge(y,x,cnt);E[y].push_back(e[cnt]);
	}
	F(i,1,n) sort(E[i].begin(),E[i].end());
	F(i,2,cnt)
	{
		int tmp=find(e[i].y,e[i^1])-1;
		if (tmp<0) tmp+=E[e[i].y].size();
		nxt[i]=E[e[i].y][tmp].id;
	}
	solve();
	return 0;
}
