#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include<string>
using namespace std;
struct STUDENT {
    int id;
    double gr;
};
bool compare(const STUDENT& a, const STUDENT& b)
{
    return a.gr > b.gr;
}
int main()
{
    int n, k;
    cin >> n >> k;
    vector<STUDENT>students(n);
    for (int i = 0; i < n; i++)
    {
        cin >> students[i].id >> students[i].gr;
    }
    sort(students.begin(), students.end(), compare);
    cout << students[k - 1].id << ' ' << students[k - 1].gr;
    return 0;
}
