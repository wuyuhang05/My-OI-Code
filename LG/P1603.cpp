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

std::map<std::string,int> S;

inline void pre(){
    S.insert(std::make_pair("one",1));
    S.insert(std::make_pair("two",2));
    S.insert(std::make_pair("three",3));
    S.insert(std::make_pair("four",4));
    S.insert(std::make_pair("five",5));
    S.insert(std::make_pair("six",6));
    S.insert(std::make_pair("seven",7));
    S.insert(std::make_pair("eight",8));
    S.insert(std::make_pair("nine",9));
    S.insert(std::make_pair("ten",10));
    S.insert(std::make_pair("eleven",11));
    S.insert(std::make_pair("twelve",12));
    S.insert(std::make_pair("thirteen",13));
    S.insert(std::make_pair("fourteen",14));
    S.insert(std::make_pair("fifteen",15));
    S.insert(std::make_pair("sixteen",16));
    S.insert(std::make_pair("seventeen",17));
    S.insert(std::make_pair("eighteen",18));
    S.insert(std::make_pair("nineteen",19));
    S.insert(std::make_pair("twenty",20));
    S.insert(std::make_pair("a",1));
    S.insert(std::make_pair("both",2));
    S.insert(std::make_pair("another",2));
    S.insert(std::make_pair("first",1));
    S.insert(std::make_pair("second",2));
    S.insert(std::make_pair("third",3));
    S.insert(std::make_pair("zero",0));
}

int num[200 + 5],top = 0;
const int ha = 100;

int main(){
    pre();
    std::string str;
    while(std::cin >> str){
        DEBUG(str);DEBUG(S[str]);
        if(!S[str]) continue;
        num[++top] = S[str];
    }
    if(!top){
        puts("0");
        return 0;
    }
    FOR(i,1,top){
        num[i] = (num[i]*num[i])%ha;
        DEBUG(num[i]);
    }
    std::sort(num + 1,num + top + 1);
    printf("%d",num[1]);
    FOR(i,2,top){
        printf("%.2d",num[i]);
    }
    return 0;
}
