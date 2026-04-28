#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct ill {
	char id[11];
	int age;
}ren[110];
int issenior(int age)
{
	return age >= 60;
}
int mycmp(const void* a, const void* b)
{
	const struct ill* pa = (struct ill*)a;
	const struct ill* pb = (struct ill*)b;
	int sa = issenior(pa->age);
	int sb = issenior(pb->age);
	if (sa && sb) {
		if (pa->age != pb->age) return pb->age - pa->age;//降序
		return strcmp(pa->id, pb->id);//升序
	}
	if (sa && !sb) return -1;//负值表示a在前
	if (!sa && sb) return 1;//正数
	if (!sa && !sb) return strcmp(pa->id, pb->id);//升序
}
int main() {
    int n;
    scanf_s("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf_s("%s %d", ren[i].id,sizeof(ren[i].id), &ren[i].age);
    }

    qsort(ren, n, sizeof(struct ill), mycmp);

    printf("排序结果:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", ren[i].id, ren[i].age);
    }

    return 0;
}
int cmp(const void* a, const void* b)
{
    return *(char*)a - *(char*)b;
}
void quchong(char word[])
{
    int len = strlen(word);
    int j = 1;
    for (int i = 1; i < len; i++)
    {
        if (word[i] != word[j - 1])
        {
            word[j] = word[i];
            j++;
        }

    }
    word[j] = '\0';
}