#include"head.cpp"
int f1() {
	string s;
	int mod;
	int cnt[26] = { 0 };
	int all = 1, newadd;//1为空集
	for (char c : s) {
		newadd = (all - cnt[c - 'a'] + mod) % mod;
		//新增等于当前的全加一个x  
		//去重，等于上次以x结尾的个数
		all = (all + newadd) % mod;
		cnt[c - 'a'] = (cnt[c - 'a'] + newadd) % mod;//更新以x结尾的个数


		//0
		//0 a
		//0 a b ab
		//0 a b ab  a aa ba aba 上次以a结尾个数为1
		//0 a b ab  aa ba aba
	    //0 a b ab  aa ba aba 
		//a aa ba aba aaa baa abaa	
	}
	return (all-1+mod)%mod;//减去空集
}