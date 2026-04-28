#include<stdio.h>
#include<stdlib.h>
struct TEACHER {
    char name[20];
    int gender;
    int age;
};
int main()
{
    int n;
    scanf_s("%d", &n);
    struct TEACHER* teacher = (struct TEACHER*)malloc(n * sizeof(struct TEACHER));
    for (int i = 0; i < n; i++)
    {
        scanf_s("%s", teacher[i].name,20);
        scanf_s("%d %d", &teacher[i].gender, &teacher[i].age);
    }
    fputs(teacher[n / 2].name,stdout);
    if (teacher[n / 2].gender == 1) printf(" Male");
    else printf(" Female");
    printf(" %d", teacher[n / 2].age);
    free(teacher);
    return 0;
}