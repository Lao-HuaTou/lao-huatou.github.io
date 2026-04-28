#include<iostream>
#include<map>
#include<vector>
using namespace std;
map<string, string>same;//记录同义词
map<string, vector<string>>m1, m2;
int n, m;
string a[5010], b[5010], s;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		m1[a[i]].push_back(b[i]);
		m2[b[i]].push_back(a[i]);
	}
	for (int i = 1; i <= n; i++) {
		same[a[i]] = a[i];
		for (auto s : m1[a[i]])
			for (auto t : m2[s])
				if (t != a[i])same[a[i]] = t;
	}
	cin >> m;
	while (m--) {
		cin >> s;
		cout << same[s] << ' ';
	}
	return 0;
}


**********************************************************************************************






#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 5010
#define MAX_WORD_LEN 100

// 存储同义词映射关系
typedef struct {
    char key[MAX_WORD_LEN];
    char value[MAX_WORD_LEN];
} SameEntry;

// 存储单词列表
typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

SameEntry same[MAX_WORDS];  // 同义词映射表
int same_count = 0;

WordList m1[MAX_WORDS];     // 正向映射: a->b[]
WordList m2[MAX_WORDS];     // 反向映射: b->a[]
int m1_count = 0, m2_count = 0;

char a[MAX_WORDS][MAX_WORD_LEN];  // 输入的a单词
char b[MAX_WORDS][MAX_WORD_LEN];  // 输入的b单词
int n, m;

// 在WordList中查找单词索引
int find_word_index(WordList* list, const char* word, int list_size) {
    for (int i = 0; i < list_size; i++) {
        if (strcmp(list[i].words[0], word) == 0) {
            return i;
        }
    }
    return -1;
}

// 添加单词到WordList
void add_to_wordlist(WordList* list, int* list_size, const char* key, const char* value) {
    int index = find_word_index(list, key, *list_size);

    if (index == -1) {
        // 新建条目
        strcpy(list[*list_size].words[0], key);
        list[*list_size].count = 1;
        if (value != NULL) {
            strcpy(list[*list_size].words[1], value);
            list[*list_size].count = 2;
        }
        (*list_size)++;
    }
    else {
        // 添加到现有条目
        if (value != NULL && list[index].count < MAX_WORDS) {
            strcpy(list[index].words[list[index].count], value);
            list[index].count++;
        }
    }
}

// 在same数组中查找条目
int find_same_index(const char* key) {
    for (int i = 0; i < same_count; i++) {
        if (strcmp(same[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

// 获取WordList中指定key的列表
WordList* get_wordlist(WordList* list, int list_size, const char* key) {
    int index = find_word_index(list, key, list_size);
    if (index != -1) {
        return &list[index];
    }
    return NULL;
}

int main() {
    // 读取单词对数量
    scanf("%d", &n);

    // 读取所有单词对并构建映射关系
    for (int i = 0; i < n; i++) {
        scanf("%s %s", a[i], b[i]);

        // 构建正向映射 a->b
        add_to_wordlist(m1, &m1_count, a[i], b[i]);
        // 构建反向映射 b->a  
        add_to_wordlist(m2, &m2_count, b[i], a[i]);
    }

    // 构建同义词关系
    for (int i = 0; i < n; i++) {
        // 初始设置自己为自己的同义词
        int same_index = find_same_index(a[i]);
        if (same_index == -1) {
            strcpy(same[same_count].key, a[i]);
            strcpy(same[same_count].value, a[i]);
            same_count++;
            same_index = same_count - 1;
        }

        // 获取a[i]的所有b单词
        WordList* b_list = get_wordlist(m1, m1_count, a[i]);
        if (b_list != NULL) {
            // 遍历所有b单词
            for (int j = 1; j < b_list->count; j++) {
                // 获取b单词对应的所有a单词
                WordList* a_list2 = get_wordlist(m2, m2_count, b_list->words[j]);
                if (a_list2 != NULL) {
                    // 遍历所有相关的a单词
                    for (int k = 1; k < a_list2->count; k++) {
                        // 如果不是自己，则设置为同义词
                        if (strcmp(a_list2->words[k], a[i]) != 0) {
                            strcpy(same[same_index].value, a_list2->words[k]);
                        }
                    }
                }
            }
        }
    }

    // 处理查询
    scanf("%d", &m);
    char s[MAX_WORD_LEN];

    while (m--) {
        scanf("%s", s);
        int index = find_same_index(s);
        if (index != -1) {
            printf("%s ", same[index].value);
        }
        else {
            printf("%s ", s);  // 如果没有找到，输出原单词
        }
    }
    printf("\n");

    return 0;
}