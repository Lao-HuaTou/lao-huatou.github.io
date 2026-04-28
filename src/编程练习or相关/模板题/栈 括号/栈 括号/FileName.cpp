#include<cstdio>
#include<cstring>//便于使用strlen();
using namespace std;
const int maxn = 100010;
char str[maxn];
int ans, ls, num;//ls即str字符串的长度,num就是个假栈顶,说明现在已经有num个括号未匹配成功
int main() {
	scanf("%s", &str);
	ls = strlen(str);
	for (int i = 0; i < ls; i++) {
		if (str[i] == '(')  num++;//等待匹配右括号
		else if (str[i] == ')' && num == 0) {//num==0即为现在str[i]之前所有括号都能匹配，凭空出现个右括号,ans自加,并将该括号转为左括号等待匹配
			ans++; num++;
		}
		else num--;//匹配成功后要减少一个待匹配的数量
	}
	ans += num / 2;//还有num个左括号没有匹配,便将其中的一半转为右括号
	if (num % 2 != 0)  ans++;//如果num是单数,则有一个括号必须进行一次删除修改
	printf("%d", ans);
	return 0;
}
