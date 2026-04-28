#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef vector<int> VI;
VI move_zero(VI A) {
    while (A.size() > 1 && A.back() == 0) A.pop_back();
    return A;
}
VI add(VI& A, VI& B) {
    if (A.size() < B.size()) return add(B, A);
    VI C;
    int t = 0;
    for (int i = 0; i < A.size() || t; i++) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    return C;
}
VI mul(VI& A, VI& B) {
    VI C(A.size() + B.size(), 0);
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < B.size(); j++)
            C[i + j] += A[i] * B[j];
    int t = 0;
    for (int i = 0; i < C.size() || t; i++) {
        if (i < C.size()) t += C[i];
        if (i < C.size()) C[i] = t % 10;
        else C.push_back(t % 10);
        t /= 10;
    }
    return move_zero(C);
}
VI read(string s) {
    VI A;
    for (int i = s.size() - 1; i >= 0; i--) A.push_back(s[i] - '0');
    return move_zero(A);
}
void print(VI A) {
    for (int i = A.size() - 1; i >= 0; i--) cout << A[i];
    cout << endl;
}
int main() {
    string s1, s2;
    cin >> s1 >> s2;
    VI A = read(s1), B = read(s2);
    print(add(A, B));
    print(mul(A, B));
    return 0;
}