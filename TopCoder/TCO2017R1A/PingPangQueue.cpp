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
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

class PingPongQueue{
    public:
    std::deque<int> q;
    std::vector <int> whoPlaysNext(std::vector <int> skills, int N, int K){
		int sz = skills.size();
        FOR(i,0,sz-1) q.push_back(skills[i]);
        int cnt = 0,peo = -1;
        std::pair<int,int> ans;
        FOR(i,1,K){
            int win,lose;
            win = q.front();q.pop_front();
            lose = q.front();q.pop_front();
            if(win < lose) std::swap(win,lose);
            q.push_back(lose);ans = MP(win,lose);
            if(peo != win){
                peo = win;
                cnt = 1;
            }
            else{
                cnt++;
            }
            if(cnt >= N){
                peo = -1;
                q.push_back(win);
            }
            else q.push_front(win);
        }
        std::vector<int> res;res.pb(ans.se);res.pb(ans.fi);
        return res;
	}
};

// BEGIN CUT HERE
//this is for test
int main(void){
	PingPongQueue test;
    std::vector<int> a;a.pb(30);a.pb(12);
    std::vector<int> res = test.whoPlaysNext(a,34,80);
	DEBUG(res[0]);DEBUG(res[1]);
    return 0;
}
//test end
// END CUR HERE


