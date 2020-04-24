## bfs记录路径的方法
可以通过倒着从特定终点进行一次bfs的方式，加上条件cur_dis=prev_dis+1,就可以找到要的那条特定终点特定长度的路径，具体可见
[bfs路径记录](https://www.cnblogs.com/astonc/p/10639091.html)
算法书中建议的回溯法，需要队列能加label(pre)，并且进行递归回溯：[回溯法](https://www.jianshu.com/p/7570ce8aa833)
比较耗费空间，但不需要再来一次的方法参考：[正向记录](https://blog.csdn.net/lanshan1111/article/details/90243923)
[两种bfs路径记录的思路](https://www.cnblogs.com/Lis-/p/10572619.html)，是以上方法的体现,但记录前序使用了循环数组
除了进行两边bfs的方法，其他方法均要在经过的每个点都记录pre或者整个正向路径，比较耗费空间
dfs应该也是用相同的思路来记录路径
## 标准形式
入队即为访问
出队是问了下一层级的加入 和访问没关系
