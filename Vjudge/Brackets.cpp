#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

using std::stack;
using std::pair;
using std::string;

const int MAXN = 100000 + 5;

string str;
bool p[MAXN];
int N;
stack<pair<char,int> > s;

int cmd(char ch){
	if(s.empty()){
		if(ch == '(' || ch == '[') return 1;
		return 0;
	}
	if(s.top().first == '['){
		if(ch == ']') return 2;
		if(ch == ')') return 0;
		return 1;
	}
	if(s.top().first == '('){
		if(ch == ']') return 0;
		if(ch == ')') return 2;
		return 1;
	}

}

void judge(){
	for(int i = 0;i < N;i++){
		int opt = cmd(str[i]);
		if(opt == 0){
			while(!s.empty()) s.pop();
		}
		else if(opt == 1)
			s.push(std::make_pair(str[i],i));
		else if(opt == 2){
			p[s.top().second] = p[i] = true;
			s.pop();
		}
	}
}

inline void de(){
	for(int i = 0;i < N;i++) 
		printf("%d\n",p[i] ? 1 : 0);
}

int main(){
	freopen("brackets.in","r",stdin);
	freopen("brackets.out","w",stdout);
	std::cin >> str;
	N = str.length();
	//DEBUG(N);
	judge();
	//de();
	int num = 0,len = 0,ansnum=0,anslen=0;
	for(int i = 0;i < N;i++){
		if(!p[i]){
			num = i + 1;
			len = 0;
		}
		else len++;
		if(len > anslen){
			ansnum = num;
			anslen = len;
		}
	}
	//DEBUG(ansnum);DEBUG(anslen);DEBUG(strlen(str));
	for(int i = ansnum;i < ansnum + anslen;i++)
		printf("%c",str[i]);
	//getchar();getchar();
	return 0;
}