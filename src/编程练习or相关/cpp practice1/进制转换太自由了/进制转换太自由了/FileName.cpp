#include<iostream>
#include<string>
using namespace std;
int n, R;
void print(int n) {
	if (n == 0) return;
	int shang, yu;
	shang = n / R;
	yu = n % R;
	if (yu < 0) {
		shang++;
		yu += R;
	}
	char m;
	if (yu < 10) m = '0' + yu;
	else m = 'A' + yu - 10;
	print(shang);
	cout << m;
}
int main()
{
	cin >> n >> R;
	cout << n << "=";
	print(n);
	cout << "(base" << R << ")" << endl;
	return 0;
}