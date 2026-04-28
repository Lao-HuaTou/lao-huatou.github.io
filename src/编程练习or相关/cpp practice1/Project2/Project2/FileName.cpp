#include <stdio.h>
#include <string.h>

#define ll long long

typedef struct {
    int key;
    char value[20];
} IntToStringMap;

typedef struct {
    char key[20];
    int value;
} StringToIntMap;

IntToStringMap mp1[5];
StringToIntMap mp2[5];
int map_size = 5;

// 初始化映射表
void init() {
    // mp1: int -> string
    mp1[0].key = 1; strcpy(mp1[0].value, "Monday");
    mp1[1].key = 2; strcpy(mp1[1].value, "Tuesday");
    mp1[2].key = 3; strcpy(mp1[2].value, "Wednesday");
    mp1[3].key = 4; strcpy(mp1[3].value, "Thursday");
    mp1[4].key = 0; strcpy(mp1[4].value, "Friday"); // 注意：周五是0，不是5

    // mp2: string -> int
    strcpy(mp2[0].key, "Monday"); mp2[0].value = 1;
    strcpy(mp2[1].key, "Tuesday"); mp2[1].value = 2;
    strcpy(mp2[2].key, "Wednesday"); mp2[2].value = 3;
    strcpy(mp2[3].key, "Thursday"); mp2[3].value = 4;
    strcpy(mp2[4].key, "Friday"); mp2[4].value = 5;
}

// 根据int查找string
char* find_by_int(int key) {
    for (int i = 0; i < map_size; i++) {
        if (mp1[i].key == key) {
            return mp1[i].value;
        }
    }
    return "Unknown";
}

// 根据string查找int
int find_by_string(char* key) {
    for (int i = 0; i < map_size; i++) {
        if (strcmp(mp2[i].key, key) == 0) {
            return mp2[i].value;
        }
    }
    return -1;
}

int main() {
    init();
    ll T, a, b, c, d, e, f;
    char day[20];

    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%lld%lld", &a, &b, &c);
        scanf("%s", day);
        scanf("%lld%lld%lld", &d, &e, &f);

        ll tm1 = 360 * a + 30 * b + c;
        ll tm2 = 360 * d + 30 * e + f;

        // 虽然年份和月份需要-1，但实际上不-1也不影响结果
        // 因为所有时间都加上了360*1+30的基数，不影响变化量
        int day_index = find_by_string(day);
        ll result_index = ((tm2 - tm1) % 5 + day_index + 5) % 5;

        // 处理结果索引，确保在0-4范围内
        if (result_index == 0) {
            printf("Friday\n");
        }
        else {
            printf("%s\n", find_by_int(result_index));
        }
    }
    return 0;
}