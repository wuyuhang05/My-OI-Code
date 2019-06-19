#include <iostream>
using namespace std;
const long long M = 998244353;
const int N = 100007;
int pa[N];
long long w, p1[N];
long long fpow(long long a, long long p)
{
	long long ans = 1;
	while (p)
	{
		if (p & 1)
			ans = ans * a % M;
		a = a * a % M;
		p >>= 1;
	}
	return ans;
}
long long arc(long long a)
{
	return fpow(a, M - 2);
}
int n;
long long a, b;
long long ans;
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	p1[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		cin >> w >> a >> b >> pa[i];
		p1[i] = ((b - a) * arc(b) % M) * p1[pa[i]] % M;
		ans = (ans + p1[i] * w % M) % M;
	}
	cout << ans << " " << p1[n] << endl;
}