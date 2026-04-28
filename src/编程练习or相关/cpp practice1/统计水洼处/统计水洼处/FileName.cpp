#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int a;
	cin >> a;
	int up = 0, down = 0;
	int ckup = 0, ckdown = 0;
	for (int i = 1; i < n; i++)
	{
		int b;
		cin >> b;
		if (b > a && ckup == 0) {
			up++;
			ckup = 1;
			ckdown = 0;
		}
		else if (b < a && ckdown == 0) {
			down++;
			ckup = 0;
			ckdown = 1;
		}
		a = b;

	}
	cout << (up > down ? down - 1 : up - 1);
	return 0;
}
