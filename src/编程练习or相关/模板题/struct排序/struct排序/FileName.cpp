#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct bang {
    char name[35];
    char po[10];
    int go;
    int level;
    int index;  // 添加索引记录原始顺序
}s[120];

int get_position_value(char* po) {
    if (strcmp(po, "BangZhu") == 0) return 7;
    if (strcmp(po, "FuBangZhu") == 0) return 6;
    if (strcmp(po, "HuFa") == 0) return 5;
    if (strcmp(po, "ZhangLao") == 0) return 4;
    if (strcmp(po, "TangZhu") == 0) return 3;
    if (strcmp(po, "JingYing") == 0) return 2;
    if (strcmp(po, "BangZhong") == 0) return 1;
    return 0;
}

int cmp(const void* a, const void* b)
{
    struct bang* pa = (struct bang*)a;
    struct bang* pb = (struct bang*)b;
    return pb->go - pa->go;
}

int cmp2(const void* a, const void* b)
{
    struct bang* pa = (struct bang*)a;
    struct bang* pb = (struct bang*)b;
    int pos_compare = get_position_value(pb->po) - get_position_value(pa->po);
    if (pos_compare) return pos_compare;
    if (pb->level != pa->level) return pb->level - pa->level;
    return pa->index - pb->index;  // 添加第三关键字
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s %s %d %d", s[i].name, s[i].po, &s[i].go, &s[i].level);
        s[i].index = i;  // 记录原始顺序
    }

    // 先输出特殊职位（按原始顺序）
    for (int i = 0; i < n; i++)
        if (strcmp(s[i].po, "BangZhu") == 0)
            printf("%s %s %d\n", s[i].name, s[i].po, s[i].level);

    for (int i = 0; i < n; i++)
        if (strcmp(s[i].po, "FuBangZhu") == 0)
            printf("%s %s %d\n", s[i].name, s[i].po, s[i].level);

    // 按功劳排序
    qsort(s, n, sizeof(struct bang), cmp);

    // 重新分配职位
    int count = 1;
    for (int i = 0; i < n; i++)
    {
        // 跳过特殊职位
        if (strcmp(s[i].po, "BangZhu") == 0 || strcmp(s[i].po, "FuBangZhu") == 0)
            continue;

        if (count <= 2) strcpy(s[i].po, "HuFa");
        else if (count <= 6) strcpy(s[i].po, "ZhangLao");      // 2+4=6
        else if (count <= 13) strcpy(s[i].po, "TangZhu");      // 6+7=13
        else if (count <= 38) strcpy(s[i].po, "JingYing");     // 13+25=38
        else strcpy(s[i].po, "BangZhong");
        count++;
    }

    // 按职位和等级排序
    qsort(s, n, sizeof(struct bang), cmp2);

    // 输出非特殊职位成员
    for (int i = 0; i < n; i++)
        if (strcmp(s[i].po, "BangZhu") != 0 && strcmp(s[i].po, "FuBangZhu") != 0)
            printf("%s %s %d\n", s[i].name, s[i].po, s[i].level);

    return 0;
}




#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ll long long

struct pe {
    char name[35];
    ll bg;
    ll lev;
    ll zw;
    ll num;
}a[1000010];

// 比较函数1：按功劳降序，输入顺序升序
int cmp1(const void* a, const void* b) {
    struct pe* pa = (struct pe*)a;
    struct pe* pb = (struct pe*)b;
    if (pa->bg != pb->bg) return (pa->bg > pb->bg) ? -1 : 1;
    else return (pa->num < pb->num) ? -1 : 1;
}

// 比较函数2：按职位降序，等级降序，输入顺序升序
int cmp2(const void* a, const void* b) {
    struct pe* pa = (struct pe*)a;
    struct pe* pb = (struct pe*)b;
    if (pa->zw != pb->zw) return (pa->zw > pb->zw) ? -1 : 1;
    else {
        if (pa->lev != pb->lev) return (pa->lev > pb->lev) ? -1 : 1;
        else return (pa->num < pb->num) ? -1 : 1;
    }
}

// 获取职位对应的数值
ll get_zw_value(char* s) {
    if (strcmp(s, "BangZhu") == 0) return 10;
    if (strcmp(s, "FuBangZhu") == 0) return 9;
    if (strcmp(s, "HuFa") == 0) return 8;
    if (strcmp(s, "ZhangLao") == 0) return 7;
    if (strcmp(s, "TangZhu") == 0) return 6;
    if (strcmp(s, "JingYing") == 0) return 5;
    if (strcmp(s, "BangZhong") == 0) return 4;
    return 0;
}

// 根据数值获取职位名称
const char* get_zw_name(ll zw) {

    switch (zw) {
    case 10: return "BangZhu";
    case 9: return "FuBangZhu";
    case 8: return "HuFa";
    case 7: return "ZhangLao";
    case 6: return "TangZhu";
    case 5: return "JingYing";
    case 4: return "BangZhong";
    default: return "BangZhong";
    }
}

int main() {
    ll n;
    scanf("%lld", &n);

    for (ll i = 1; i <= n; i++) {
        char s[20];
        scanf("%s %s %lld %lld", a[i].name, s, &a[i].bg, &a[i].lev);
        a[i].num = i;
        a[i].zw = get_zw_value(s);
    }

    // 第一次排序：按功劳降序
    qsort(a + 1, n, sizeof(struct pe), cmp1);

    ll q = 1;
    // 重新分配职位
    for (ll i = 1; i <= n; i++) {
        if (a[i].zw > 8) continue;  // 跳过BangZhu和FuBangZhu

        if (q <= 2) a[i].zw = 8;        // HuFa
        else if (q <= 6) a[i].zw = 7;   // ZhangLao
        else if (q <= 13) a[i].zw = 6;  // TangZhu
        else if (q <= 38) a[i].zw = 5;  // JingYing
        else a[i].zw = 4;              // BangZhong
        q++;
    }

    // 第二次排序：按职位、等级排序
    qsort(a + 1, n, sizeof(struct pe), cmp2);

    // 输出结果
    for (ll i = 1; i <= n; i++) {
        printf("%s %s %lld\n", a[i].name, get_zw_name(a[i].zw), a[i].lev);
    }

    return 0;
}