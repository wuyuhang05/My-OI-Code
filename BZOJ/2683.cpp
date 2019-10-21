/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-18 10:42:49
 */
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

const int MAXN = 500000+5;

struct BIT{
    int tree[MAXN];
    #define lowbit(x) ((x)&(-(x)))

    inline void add(int pos,int d){
        while(pos < MAXN){
            tree[pos] += d;
            pos += lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos){
            res += tree[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

    inline void del(int pos){
        while(pos < MAXN){
            tree[pos] = 0;
            pos += lowbit(pos);
        }
    }
}bit;

struct Node{
    int opt,x,y,id,d,ans;

    Node(int opt=0,int x=0,int y=0,int id=0,int d=0) : opt(opt),x(x),y(y),id(id),d(d) {}

    inline void print(){
        printf("%d %d %d\n",opt,x,y);
    }
}q[MAXN<<2],tmp[MAXN<<2];

int n,N;
int ans[MAXN];
bool tag[MAXN];

inline void solve(int l,int r){
    if(l == r) return;
    int mid = (l + r) >> 1;
    solve(l,mid);solve(mid+1,r);
    // x
    int p1 = l,p2 = mid+1,sz = l-1;
    std::vector<int> opts;
//    FOR(i,l,r) q[i].print();
//    puts("");
    while(p1 <= mid && p2 <= r){
        if(q[p1].x <= q[p2].x){
            if(q[p1].opt == 1) bit.add(q[p1].y,q[p1].d),opts.pb(q[p1].y);
            tmp[++sz] = q[p1];p1++;
        }
        else{
            if(q[p2].opt == 2) q[p2].ans += bit.query(q[p2].y);
            tmp[++sz] = q[p2];p2++;
        }
    }
    FOR(i,p1,mid) tmp[++sz] = q[i];
    FOR(i,p2,r) q[i].ans += bit.query(q[i].y),tmp[++sz] = q[i];
    FOR(i,l,r) q[i] = tmp[i];
//    FOR(i,l,r) q[i].print();
 //   puts("-----------------------");
    FOR(i,0,(int)opts.size()-1) bit.del(opts[i]);
}

int main(){
//    freopen("5.in","r",stdin);
    scanf("%d",&n);
    int tot = 0;int m;
    FOR(i,1,2000000){
        int opt;scanf("%d",&opt);
        if(opt == 1){
            int x,y,d;scanf("%d%d%d",&x,&y,&d);
            ++x;++y;
            q[++N] = Node(opt,x,y,i,d);
        }
        else if(opt == 2){
            tag[i] = true;++tot;
            int x1,y1,x2,y2;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            x1++;y1++;x2++;y2++;
            q[++N] = Node(opt,x2,y2,i,1);
            q[++N] = Node(opt,x1-1,y2,i,-1);
            q[++N] = Node(opt,x2,y1-1,i,-1);
            q[++N] = Node(opt,x1-1,y1-1,i,1);
        }
        else break;
        m = i;
    }
    solve(1,N);
    int cnt = 0;
    FOR(i,1,N) if(q[i].opt == 2) ans[q[i].id] += q[i].d*q[i].ans;
    FOR(i,1,m) if(tag[i]) printf("%d\n",ans[i]),++cnt;
    return 0;
}
