// BEGIN CUT HERE

// END CUT HERE
#line 5 "problem.cpp"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define P std::pair<double,double>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const double EPS = 1e-9;
const double pi = acos(-1);

class PolygonRotation{
public:

    inline double ds(P p1,P p2,double y){
        if(p1.se == p2.se) return abs(std::max(p1.fi,p2.fi));
        return std::abs(p1.fi+1.0*(p2.fi-p1.fi)/(p2.se-p1.se)*(y-p1.se));
    }

    int n;
    
    double f(double y,const std::vector<int> &X,const std::vector<int> &Y){
        double max = 0.0;
        FOR(i,0,n-1){
            if(std::abs(Y[i]-y) <= EPS) max = std::max(max,1.0*X[i]);
            int nxt = i < n-1 ? i+1 : 0;
            if(std::min(Y[i],Y[nxt]) > y) continue;
            if(std::max(Y[i],Y[nxt]) < y) continue;
            double t = ds(MP(X[i],Y[i]),MP(X[nxt],Y[nxt]),y);
            max = std::max(max,t);
        }
        //DEBUG(max);
        return pi*max*max;
    }

    double getVolume(std::vector <int> X, std::vector <int> Y){
		double a = *std::min_element(all(Y)),b = *std::max_element(all(Y));
        n = X.size();
        const int N = 1e6;
        double sum = 0.0;
        double h = (b-a)/N;
        FOR(i,0,N){
            double y = a+h*i;
            sum += f(y,X,Y) * (((i == 0) || (i == N)) ? 1 : ((i&1) ? 4 : 2));
        }
        sum *= h;sum /= 3.0;
        return sum;
	}
};
// BEGIN CUT HERE
// test
int main(void){
	PolygonRotation test;
    std::vector<int> a,b;
    a.pb(0);a.pb(1);a.pb(1);a.pb(0);
    b.pb(1);b.pb(1);b.pb(0);b.pb(0);
	printf("%.10f\n",test.getVolume(a,b));
	return 0;
}
// test end
// END CUT HERE


