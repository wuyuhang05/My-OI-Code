/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-18 09:23:34
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

const int MAXN = 2e5 + 5;

struct BIT{
    int tree[(MAXN<<1)+1];
    #define lowbit(x) ((x)&(-(x)))

    inline void clear(){
        CLR(tree,0);
    }

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
    int a,b,c,cnt,ans;

    bool operator < (const Node &t) const {
        return a == t.a ? (b == t.b ? c < t.c : b < t.b) : a < t.a;
    }

    bool operator == (const Node &t) const {
        return a == t.a && b == t.b && c == t.c;
    }

    inline void print(){
        printf("%d %d %d\n",a,b,c);
    }
}a[MAXN],A[MAXN],tmp[MAXN];

int n,k,N;
int ans[MAXN];

inline void solve(int l,int r){
    if(l == r){
        A[l].ans += A[l].cnt-1;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l,mid);
    solve(mid+1,r);
//    FOR(i,l,r) A[i].print();puts("");
    int p1 = l,p2 = mid+1;//bit.clear();
    int sz = l-1;
    while(p1 <= mid && p2 <= r){
        if(A[p1].b <= A[p2].b){
            bit.add(A[p1].c,A[p1].cnt);
//            DEBUG(A[p1].c);
//            DEBUG(A[p1].cnt);
            tmp[++sz] = A[p1];p1++;
        }
        else{
            A[p2].ans += bit.query(A[p2].c);
//            DEBUG(bit.query(A[p2].c));
//            DEBUG(bit.query(2));
            tmp[++sz] = A[p2];p2++;
        }
    }
    FOR(i,p1,mid) tmp[++sz] = A[i];
    FOR(i,p2,r) A[i].ans += bit.query(A[i].c),tmp[++sz] = A[i];
    FOR(i,l,r) A[i] = tmp[i];
    FOR(i,l,r) bit.del(A[i].c);
//    FOR(i,l,r) A[i].print();
//    puts("---------------");
}

int main(){
//    freopen("testdata.in","r",stdin);
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c);
    std::sort(a+1,a+n+1);
    int cnt = 1;
    FOR(i,2,n){
        if(a[i] == a[i-1]) cnt++;
        else{
            A[++N] = a[i-1];
            A[N].cnt = cnt;
            cnt = 1;
        }
    }
    A[++N] = a[n],A[N].cnt = cnt;
    solve(1,N);
    FOR(i,1,N) ans[A[i].ans] += A[i].cnt;
    FOR(i,0,n-1) printf("%d\n",ans[i]);
    return 0;
}
