#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int t; cin >> t;
	while (t--)
	{
		int n, r;
		cin >> n >> r;
		vector<vector<long long>>diff;
		vector<long long>first(n);
		for (int i = 0; i < n; i++)cin >> first[i];
		diff.push_back(first);
		for (int i = 0; i < n; i++) {		//´ò±í
			int zero = 1;
			vector<long long>current;
			for (int j = 0; j < diff[i].size()-1; j++)
			{
				long long tem = diff[i][j +1] - diff[i][j];
				current.push_back(tem);
				if (tem != 0) zero = 0;
			}
			diff.push_back(current);
			if (zero) break;
		}
		for (int i = 0; i < r; i++)
		{
			diff.back().push_back(0);		//²¹0
			for (int j = diff.size() - 1; j > 0; j--)
			{
				diff[j - 1].push_back(diff[j].back() + diff[j - 1].back());
			}
		}
		for (int i = 0; i < r; i++)
		{
			cout << diff[0][n + i] << " ";
		}
		cout << endl;
	}
	return 0;
}



