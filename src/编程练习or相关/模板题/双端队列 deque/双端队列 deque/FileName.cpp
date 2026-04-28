#include <iostream>
#include <deque>
using namespace std;
deque < int > Q;
int main() {
    int n, c = 1, k;
    char a, b;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        if (a == 'A' && b == 'L') Q.push_front(c++); else
            if (a == 'A') Q.push_back(c++);  else
                if (b == 'L') {
                    cin >> k;
                    for (int j = 1; j <= k; j++) Q.pop_front();
                }
                else {
                    cin >> k;
                    for (int j = 1; j <= k; j++) Q.pop_back();
                }
    }
    while (!Q.empty()) cout << Q.front() << endl, Q.pop_front();
    return 0;
}


a.push_front(x);//在队首添加一个元素，时间复杂度为O(1)
a.push_back(x);//同理，在队尾添加一个元素
a.front();//返回队首的数值，时间复杂度为O(1)
a.back();//同理，返回队尾的数值
a.pop_front();//删除队首元素，时间复杂度为O(1)
a.pop_back();//同理，删除队尾元素
a.size();//返回队列内元素个数，时间复杂度为O(1)
a.clear();//删除队列内所有元素，时间复杂度为O(n)
