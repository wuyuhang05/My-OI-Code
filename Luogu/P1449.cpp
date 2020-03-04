#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

std::stack<LL> s;

int main(){
    char ch = ' ';
    LL num = 0;
    while(ch != '@'){
        ch = getchar();
        int x,y;
        switch (ch){
            case '.':
                s.push(num);
                num = 0;
                break;
            case '+':
                    x = s.top();s.pop();
                    y = s.top();s.pop();
                    s.push(x+y);break;
                case '-':
                    x = s.top();s.pop();
                    y = s.top();s.pop();
                    s.push(y-x);break;
                case '*':
                    x = s.top();s.pop();
                    y = s.top();s.pop();
                    s.push(x*y);break;
                case '/':
                    x = s.top();s.pop();
                    y = s.top();s.pop();
                    s.push(y/x);break;
                default:
                    num = num*10 + (ch ^ '0');
                    break;
            }
    }
    printf("%lld\n",s.top());
    return 0;
}
