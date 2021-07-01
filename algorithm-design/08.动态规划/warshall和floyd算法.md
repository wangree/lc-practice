# warshall算法
该算法目的是计算起点i到j的连通性，对整个图的邻接矩阵来说就是求传递闭包，这里其实是有n个R的，但可以合并，注意这种R0到Rn的承接才有了算法的合理性
伪代码如下（类c)
```cpp
R=C;//C是邻接矩阵
for(int k=1;k<=n;k++){
   for(int i=1;i<=n;i++){
       for(int j=1;j<=n;j++){
           R[i][j]=R[i][j]||(R[i][k]&&R[k][j]);
       }
   }
}
```
#floyd算法
与warshall算法十分类似，动态规划的思想贯穿其中
```cpp
D=C;//C是距离矩阵
for(int k=1;k<=n;k++){
   for(int i=1;i<=n;i++){
       for(int j=1;j<=n;j++){
           D[i][j]=min(D[i][j]，D[i][k]+D[k][j]);
       }
   }
}

```
需要注意的是Floyd是图上每两个点的距离 没有起终点概念
