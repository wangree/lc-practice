## bfs记录路径的方法
可以通过倒着从特定终点进行一次bfs的方式，加上条件cur_dis=prev_dis+1,就可以找到要的那条特定终点特定长度的路径，具体可见
[bfs路径记录](https://www.cnblogs.com/astonc/p/10639091.html)
算法书中建议的回溯法，需要队列能加label(pre)，并且进行递归回溯：[回溯法](https://www.jianshu.com/p/7570ce8aa833)
比较耗费空间，但不需要再来一次的方法参考：[正向记录](https://blog.csdn.net/lanshan1111/article/details/90243923)
