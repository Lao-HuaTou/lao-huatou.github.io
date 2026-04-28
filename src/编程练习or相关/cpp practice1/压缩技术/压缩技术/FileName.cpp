#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a, b;
	cin >> b;
	int n = b.size();
	cout << n << " ";
	while (cin >> a)
	{
		b += a;
	}

	if (b[0] != '0') cout << "0";
	for (int i = 1; i <= n * n; i++)
	{
		int t = 1;
		if (b[i] == b[i - 1])
		{
			t++;
		}
		else {
			cout<<t<<" ";
			t = 1;
		}
	}
	return 0;
}
