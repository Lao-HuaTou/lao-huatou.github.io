#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
//二维前缀和
//给定一个二维矩阵，求出任意子矩阵的和
//给矩阵加边 免去判断边界
vector<vector<int>>ma;
vector<vector<int>>prefixSum;
void buildPrefixSum(int n, int m){
	//先把prefixSum数组初始化ma 原矩阵加边
	prefixSum.resize(n+1, vector<int>(m+1, 0));
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			prefixSum[i][j] = prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1];
		}
	}
}
//查询子矩阵和
int query(int x1, int y1, int x2, int y2){
	return prefixSum[x2][y2] - prefixSum[x1-1][y2] - prefixSum[x2][y1-1] + prefixSum[x1-1][y1-1];
}