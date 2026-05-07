void dfs(int u, int f) :
    deep[u] = deep[f] + 1;
    stjump[u][0] = f;
    for (int p = 1; p <= power; p++) :
        stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
    for (int e = head[u]; e != 0; e = nxt[e]) :
        if (to[e] != f) :  dfs(to[e], u);
int lca(int a, int b) :
    if (deep[a] < deep[b]) : swap(a, b);

    for (int p = power; p >= 0; p--) :
        if (deep[stjump[a][p]] >= deep[b]) :
            a = stjump[a][p];
    if (a == b) :
        return a;
    // 2. a和b一起向上跳，直到跳到LCA的下一层
    for (int p = power; p >= 0; p--) :
        if (stjump[a][p] != stjump[b][p]) :
            a = stjump[a][p];
            b = stjump[b][p];
    // 返回他们的父节点即为LCA
    return stjump[a][0];
}