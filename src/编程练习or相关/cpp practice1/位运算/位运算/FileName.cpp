#include<iostream>
using namespace std;
#define int long long
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
        cout << s[i];
    }
    cout << endl;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1] && s[i] == 's') {
            for (int j = 0; j < i - 1; j++) cout << s[j];
            cout << 'B';
            for (int j = i + 1; j < s.size(); j++) cout << s[j];
            cout << endl;
        }
    }
    return 0;
}


************************************************************************



#define QwQ return 0;
#define ll long long
#define endl '\n'
using namespace std;
string s1[200]; //保存答案
int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        s[i] = s[i] + 32; //将字符转换成小写
    }
    int len = s.size();
    int k = 0;
    for (int i = 0; i < (1 << len); i++) {
        string word = "";
        for (int j = 0; j < len;) {
            //判断是否转换成“B”
            if ((i & (1 << j)) && s[j] == 's' && s[j + 1] == 's' && j + 1 < len) {
                word += 'B'; //将连续的“SS”转换成“B”
                j += 2;
            }
            else {
                word += s[j];
                j += 1;
            }
        }
        bool flag = true; //去重操作
        for (int i = 1; i <= k; i++) {
            if (s1[i] == word) {
                flag = false;
                break;
            }
        }
        if (flag) { //如果没出现过就加进去
            k++;
            s1[k] = word;
        }
    }
    for (int i = 1; i <= k; i++) {
        cout << s1[i] << endl;
    }
    QwQ;
}
