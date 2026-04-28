#include <iostream>
#include <string>
using namespace std;

bool is_valid_char(char c) {
    return c == '0' || c == '1' || c == '2' || c == '5' ||
        c == '8' || c == '6' || c == '9';
}

char rotate_char(char c) {
    if (c == '6') return '9';
    if (c == '9') return '6';
    return c;  // 0,1,2,5,8 不变
}

bool is_good_pair(char a, char b) {
    if (!is_valid_char(a) || !is_valid_char(b)) {
        return false;
    }
    return rotate_char(a) == b && rotate_char(b) == a;
}

int main() {
    int n;
    string s;
    cin >> n >> s;

    int changes = 0;
    for (int i = 0; i <= (n - 1) / 2; i++) {
        if (i == n - 1 - i) {
            // 中间字符
            if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '5' && s[i] != '8') {
                changes++;
            }
        }
        else {
            char a = s[i], b = s[n - 1 - i];
            if (!is_good_pair(a, b)) {
                if (!is_valid_char(a) && !is_valid_char(b)) {
                    changes += 2;
                }
                else {
                    changes += 1;
                }
            }
        }
    }

    cout << changes << endl;
    return 0;
}