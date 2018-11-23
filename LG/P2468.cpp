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

int N,M,Q;

namespace Subtask1{
    #define SIZE 200+5
    #define MAXVAL 1000+5
    int p[SIZE][SIZE];
    int f1[SIZE][SIZE][MAXVAL],f2[SIZE][SIZE][MAXVAL];

    inline int calc(int x1,int y1,int x2,int y2,int k,int f){
        if(f == 1) return f1[x2][y2][k] - f1[x2][y1-1][k] - f1[x1-1][y2][k] + f1[x1-1][y1-1][k];
        return f2[x2][y2][k] - f2[x2][y1-1][k] - f2[x1-1][y2][k] + f2[x1-1][y1-1][k];
    }

    inline void Solve(){
        int max = INT_MIN;
        FOR(i,1,N) FOR(j,1,M) scanf("%d",&p[i][j]),max = std::max(max,p[i][j]);
        FOR(k,1,max){
            FOR(i,1,N){
                FOR(j,1,M){
                    f1[i][j][k] = f1[i-1][j][k] + f1[i][j-1][k] - f1[i-1][j-1][k] + (p[i][j] >= k) * p[i][j];
                    f2[i][j][k] = f2[i-1][j][k] + f2[i][j-1][k] - f2[i-1][j-1][k] + (p[i][j] >= k);
                }
            }
        }
        while(Q--){
            int x1,x2,y1,y2,h;
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&h);
            if(calc(x1,y1,x2,y2,1,1) < h){
                puts("Poor QLW");continue;
            }
            int L = 1,R = max,ans;
            while(L <= R){
                int mid = (L + R) >> 1;
                if(calc(x1,y1,x2,y2,mid,1) >= h) ans = mid,L = mid+1;
                else R = mid - 1;
            }
            printf("%d\n",calc(x1,y1,x2,y2,ans,2) - (calc(x1,y1,x2,y2,ans,1)-h)/ans);
        }
    }
    #undef SIZE
    #undef MAXVAL
}

namespace Subtask2{
    #define SIZE (500000+5)

    struct Node{
        int sum,size;
        Node *lc,*rc;
    }pool[(SIZE<<4)+1],*frog = pool,*root[SIZE];

    inline void pushup(Node *v){
        if(!v) return;
        v->sum = v->lc ? v->lc->sum : 0 + v->rc ? v->rc->sum : 0;
    }

    Node *New(Node *lc=NULL,Node *rc=NULL,int sum=0,int size=1){
        Node *ret = ++frog;
        ret->sum = sum;ret->size = size;
        ret->lc = lc;ret->rc = rc;
        return ret;
    }

    Node *insert(Node *prev,int L,int R,int w){
        Node *v = New();
		v->size = prev->size + 1;v->sum = prev->sum + w;v->lc = prev->lc;v->rc = prev->rc;
		if(L == R) return v;
		int mid = (L + R) >> 1;
		if(w <= mid) v->lc = insert(v->lc,L,mid,w);
		else v->rc = insert(v->rc,mid+1,R,w);
		return v;
    }

    int query(Node *L,Node *R,int l,int r,int k){
        int t = ((R && R->rc) ? R->rc->sum : 0) - ((L && L->rc) ? L->rc->sum : 0);
        if(l == r) return ceil((double)k/(double)l);
        int mid = (l + r) >> 1;
        if(k > t) return (R && R->rc ? R->rc->size : 0) - ((L && L->rc) ? L->rc->size : 0) + query(L ? L->lc : NULL,R ? R->lc : NULL,l,mid,k-t);
        return query(L ? L->rc : NULL,R ? R->rc : NULL,mid+1,r,k);
    }

    int p[SIZE],sum[SIZE];

    inline void Solve(){
        int max = INT_MIN;
        FOR(i,1,M){
            scanf("%d",p+i);
            sum[i] = sum[i-1]+p[i];
            max = std::max(max,p[i]);
        }
        FOR(i,1,M) root[i] = insert(root[i-1],1,max,p[i]);
        while(Q--){
            int y1,y2,h;scanf("%*d%d%*d%d%d",&y1,&y2,&h);
            if((root[y2] ? root[y2]->sum : 0) - (root[y1-1] ? root[y1-1]->sum : 0) < h) puts("Poor QLW");
            else printf("%d\n",query(root[y1-1],root[y2],1,max,h));
        }
    }
    #undef SIZE
}

signed main(){
    freopen("2.in","r",stdin);
    freopen("main.out","w",stdout);
    scanf("%d%d%d",&N,&M,&Q);
    if(N == 1) Subtask2::Solve();
    else Subtask1::Solve();
    //system("pause");
    return 0;
}