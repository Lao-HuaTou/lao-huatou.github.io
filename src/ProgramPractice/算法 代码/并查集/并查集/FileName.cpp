//int p[5000000];
//int h[5000000];//记录高度
//int s[5000000];//size
//void init(int n) {
//	for (int i = 0; i < n; i++) {
//		p[i] = i;
//		h[i] = 1;
//		s[i] = 1;
//	}
//}
//int find(int x) {
//	if (p[x] == x) return x;
//	else return p[x] = find(p[x]);//优化版 路径压缩
//	//else return find(p[x]);    
//
//}
////把low所在的集合并到hihg所在的集合
////高度相同 +1；否则取最高
//void union1(int x, int y) {
//	int rootx = find(x);
//	int rooty = find(y);
//	if (rootx != rooty) {
//		if (h[rootx] < h[rooty]) {
//			p[rootx] = rooty;
//
//		}
//		else if (h[rootx] > h[rooty]) {
//			p[rooty] = rootx;
//		}
//		else {
//			p[rooty] = rootx;
//			h[rootx]++;
//		}
//	}
//	return;
//}
//void union2(int x, int y)
//{
//	int rootx = find(x);
//	int rooty = find(y);
//	if (rootx != rooty) {
//		if (s[rootx] < s[rooty]) {
//			p[rootx] = rooty;
//			s[rooty] += s[rootx];
//		}
//		else {
//			p[rooty] = rootx;
//			s[rootx] += s[rooty];
//		}
//	}
//	return;
//}
////用负值代表根节点并记录大小or高度 
//int p1[5000000];
//void init1(int n) {
//	for (int i = 0; i < n; i++) {
//		p1[i] = -1;
//	}
//}
//int find1(int x) {
//	if (p1[x] < 0) return x;
//	else return p1[x] = find1(p1[x]);
//}
//void union3(int x, int y) {
//	int rootx = find1(x);
//	int rooty = find1(y);
//	if (rootx != rooty) {
//		if (p1[rootx] < p1[rooty]) {//rootx集合更大
//			p1[rootx] += p1[rooty];
//			p1[rooty] = rootx;
//		}
//		else {
//			p1[rooty] += p1[rootx];
//			p1[rootx] = rooty;
//		}
//	}
//	return;
//}