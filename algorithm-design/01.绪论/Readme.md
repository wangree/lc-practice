## 习题1.1
11.扩展的欧几里得算法与丢番图方程的求解：
https://blog.csdn.net/marukoheart/article/details/78090296
### 扩展的欧几里德算法
原理阐述：
如果有ma+nb=gcd(a,b),由于gcd(a,b)=gcd(b,a%b)
则也有m1*a+n1*(a%b)=ma+nb
化简得到m=n1,n=m1-a/b*n1
所以就能够得到递推公式
```cpp
int gcd(int a,int b,int* x,int* y){
    if(b==0) {
        *x = 1;
        *y = 0;
        return  a;
    }
    int prevx =0;
    int prevy =0;
    int res = gcd(b,a%b,&prevx,&prevy);
    *x=prevy;
    *y=prevx-a/b*prevy;
    return res;    
}
```
### 丢番图方程
丢番图方程只需要将扩展的欧几里德得到的两个系数再乘以c/gcd(a,b)即可
## 习题1.4
###指出如何用下列数据结构实现优先对列
1。无序数组：可把new item放在数组较大成员之后，把所有比它大的成员向后移动一格，类似与插入排序的操作；出队列时，删除最后一个元素，再resize即可；答案给的实现方法是每次把新元素放在最后一个元素之后，每次出队时需要查找最大成员，交换最后一个成员和最大成员
2. 有序数组：插入排序 
3. 二叉查找树:  
###实现一个相对较小，长度为n的字典
由于相对较小，所以可能使用空间占用相对大的方法，而且不需要删除增加Key的话，线性数组是最好的，如array,大小固定为n,其值可以是键值或者1/0这种
###实现一个计算算术表达式的计算器

