//#include <iostream>
//#include <vector>
//#include <algorithm>
//    using namespace std;
//    typedef long long ll;
//    struct Station {
//        ll s;
//        int t;
//    };
//    bool cmp(const Station & a, const Station & b) {
//        return a.s < b.s;
//    }
//    ll solve() {
//        int n, m;
//        if (!(cin >> n >> m)) return 0;
//        ll total = 0;
//        vector<ll> bat(n + 1);
//        for (int i = 1; i <= n; i++) {
//            cin >> bat[i];
//            total += bat[i];
//        }
//        vector<Station> stations(m);
//        for (int i = 0; i < m; i++) {
//            cin >> stations[i].s >> stations[i].t;
//        }
//        sort(stations.begin(), stations.end(), cmp);
//        ll ex = 0;
//        ll ans = total;
//        bool failed = false;
//
//        for (int i = 0; i < m; i++) {
//            ll s = stations[i].s;
//            int t = stations[i].t;
//            if (total + ex < s) {
//                ans = total + ex;
//                failed = true;
//                break;
//            }
//            ll g = min(bat[t], s - ex);
//            ex += g;
//        }
//        if (!failed) {
//            ans = total + ex;
//        }
//        return ans;
//    }
//
//    int main() {
//        ios::sync_with_stdio(false);
//        cin.tie(nullptr);
//
//        int T;
//        if (!(cin >> T)) return 0;
//        vector<ll> results;
//        results.reserve(T);
//        while (T--) {
//            results.push_back(solve());
//        }
//        for (const auto& res : results) {
//            cout << res << "\n";
//        }
//        return 0;
//    }

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

struct Station {
    ll s;
    int t;
};

bool cmp(const Station& a, const Station& b) {
    return a.s < b.s;
}

ll solve() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<ll> bat(n + 1);
    ll total_dist = 0;
    for (int i = 1; i <= n; i++) {
        cin >> bat[i];
        total_dist += bat[i]; // 初始总电量即为初始行驶里程
    }

    vector<Station> stations(m);
    for (int i = 0; i < m; i++) {
        cin >> stations[i].s >> stations[i].t;
    }

    // 题目保证 x 递增，但手动 sort 更稳妥
    sort(stations.begin(), stations.end(), cmp);

    // diff[t] 记录第 t 个电瓶上一次充电时的车行位置
    vector<ll> diff(n + 1, 0);

    for (int i = 0; i < m; i++) {
        ll s = stations[i].s;
        int t = stations[i].t;

        // 如果当前电量无法到达当前充电站，行驶结束
        if (total_dist < s) break;

        // 核心逻辑：电瓶 t 在 [diff[t], s] 这一段路程中分配到的消耗量
        // 最多不能超过电瓶本身的容量 bat[t]
        ll refill = min(bat[t], s - diff[t]);

        total_dist += refill;
        diff[t] = s; // 更新该电瓶的最后充电坐标
    }

    return total_dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    vector<ll> results;
    results.reserve(T);
    while (T--) {
        results.push_back(solve());
    }
    for (const auto& res : results) {
        cout << res << "\n";
    }
    return 0;
}


//#include <iostream>
//#include <vector>
//#include <algorithm>
//    using namespace std;
//    typedef long long ll;
//    struct Station {
//        ll s;
//        int t;
//    };
//    bool cmp(const Station& a, const Station& b) { 
//        return a.s < b.s;
//    }
//    ll solve() {
//        int n, m;
//        if (!(cin >> n >> m)) return 0;
//        ll total = 0;
//        vector<ll> bat(n + 1);
//        vector<ll> bat_init(n + 1);
//        for (int i = 1; i <= n; i++) {
//            cin >> bat[i];
//            bat_init[i] = bat[i]; 
//            total += bat[i];       
//        }
//        vector<Station> stations(m);
//        for (int i = 0; i < m; i++) {
//            cin >> stations[i].s >> stations[i].t;
//        }
//        sort(stations.begin(), stations.end(), cmp);
//
//        ll ex = 0; 
//        ll ans = 0; 
//        bool failed = false;
//        vector<bool> has_charge(n + 1, false);
//        for (auto& st : stations) has_charge[st.t] = true;
//        for (int i = 0; i < m; i++) {
//            ll s = stations[i].s;
//            int t = stations[i].t;
//            ll d = s - ex;     
//            if (d > 0 && total < d) {
//                ans = ex + total;
//                failed = true;
//                break;
//            }
//            if (d > 0) {
//                ll need = d; 
//                while (need > 0) {
//                    for (int j = 1; j <= n && need > 0; j++) {
//                        if (has_charge[j] && bat[j] > 0) {
//                            ll sub = min(bat[j], need); 
//                            bat[j] -= sub;
//                            total -= sub;
//                            need -= sub;
//                        }
//                    }
//                    for (int j = 1; j <= n && need > 0; j++) {
//                        if (!has_charge[j] && bat[j] > 0) {
//                            ll sub = min(bat[j], need);
//                            bat[j] -= sub;
//                            total -= sub;
//                            need -= sub;
//                        }
//                    }
//                }
//                ex = s;
//            }
//            total = total - bat[t] + bat_init[t]; 
//            bat[t] = bat_init[t];               
//        }
//
//        if (!failed) {
//            ans = ex + total; 
//        }
//        return ans;
//    }
//    int main() {
//        ios::sync_with_stdio(false);
//        cin.tie(nullptr);
//        int T;
//        cin >> T;
//        vector<ll> results;
//        results.reserve(T);
//        while (T--) {
//            results.push_back(solve());
//        }
//        for (const auto& res : results) {
//            cout << res << "\n";
//        }
//        return 0;
//    }


//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <queue>
//
//    using namespace std;
//    typedef long long ll;
//
//    struct Station {
//        ll s;
//        int t;
//    };
//
//    bool cmp(const Station& a, const Station& b) {
//        return a.s < b.s;
//    }
//
//    ll solve() {
//        int n, m;
//        if (!(cin >> n >> m)) return 0;
//
//        vector<ll> bat(n + 1);
//        for (int i = 1; i <= n; i++) {
//            cin >> bat[i];
//        }
//
//        vector<Station> stations(m);
//        for (int i = 0; i < m; i++) {
//            cin >> stations[i].s >> stations[i].t;
//        }
//
//        sort(stations.begin(), stations.end(), cmp);
//
//        priority_queue<ll> pq;
//        ll current_dist = 0;
//        // 初始总电量即为初始能走的最远距离
//        for (int i = 1; i <= n; i++) {
//            current_dist += bat[i];
//        }
//
//        int idx = 0;
//        // 遍历所有充电站，看能否通过它们增加 current_dist
//        while (idx < m) {
//            // 如果当前能走到的范围覆盖了当前充电站，先把它存入备选堆
//            if (current_dist >= stations[idx].s) {
//                pq.push(bat[stations[idx].t]);
//                idx++;
//            }
//            else {
//                // 如果走不到下一个站了，从堆里拿出一个最大的电池换上
//                if (pq.empty()) break;
//                current_dist += pq.top();
//                pq.pop();
//            }
//        }
//
//        // 走完所有站后，如果堆里还有电池，理论上可以在最远点继续换（取决于题目规则）
//        // 如果题目允许在终点前把所有机会用完：
//        while (!pq.empty()) {
//            current_dist += pq.top();
//            pq.pop();
//        }
//
//        return current_dist;
//    }
//
//    int main() {
//        ios::sync_with_stdio(false);
//        cin.tie(nullptr);
//
//        int T;
//        if (!(cin >> T)) return 0;
//        vector<ll> results;
//        results.reserve(T);
//        while (T--) {
//            results.push_back(solve());
//        }
//        for (const auto& res : results) {
//            cout << res << "\n";
//        }
//        return 0;
//    }

#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;
int main()
{
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        ll total = 0;
        vector<ll>bat(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> bat[i];
            total += bat[i];
        }
        bool flag = false;//?????m?? true ??
        ll ex = 0;
        ll ans;
        vector<ll>diff(n + 1, 0);//?m??????????
        for (int i = 0; i < m; i++) {
            ll s, t; cin >> s >> t;
            if (!flag && ex + total < (ll)s) {
                ans = total + ex;
                flag = true;
            }
            if (!flag) {
                ll g = min(bat[t], min(s - diff[t], s - ex));//s-ex??????????
                ex += g;
                diff[t] = s;
            }
        }
        if (!flag) ans = total + ex;
        cout << ans << "\n";
    }
    return 0;
}