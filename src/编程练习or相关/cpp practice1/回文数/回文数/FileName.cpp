#include<iostream>
#include<string>
using namespace std;
bool isPal(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++; right--;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    string ans = "";  // 用于保存当前最大的回文数（以字符串形式存储）
    while (n--) {
        string s;
        cin >> s;
        if (isPal(s)) {
            // 如果 ans 为空，或者 s 长度更长（位数更多），或者长度相同但字典序更大
            if (ans == "" || s.size() > ans.size() || (s.size() == ans.size() && s > ans)) {
                ans = s;
            }
        }
    }
    cout << ans << endl;
    return 0;
}