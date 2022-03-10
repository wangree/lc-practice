# 基本型
注意对于区间有左闭右开，双闭两种可能；
注意在书写的时候，target和mid对应值有三种情况：大于等于和小于，在退出循环后正常找到target情况下mid的值对应的指针，假如是left,则检查left有没有越界或者对应在序列中是否等于target才是最终用来判断有没有找到的依据,而且我们只关心这个值:这个值由于要么是left,要么是right,而在一个确定顺序的序列，这个指针只能朝一个方向移动，比如说在寻找右边界的时候，最终可能等于target的是right指针，不论什么代码right指针只会向左移动，因此异常的情况只能是要么right越界小于0（即所有值都大于target），要么是target不存在于后面的序列中，即right指针对应的值不等于target.
## lc69 x的平方根
###暴力法
```cpp
class Solution {
public:
    int mySqrt(int x) {
        int res=0;
        while((long)res*res<=x){
            res++;
        }
        return --res;
    }
};
```
###二分法
####二分法写法1
标准形式
```cpp
class Solution {
public:
    int mySqrt(int x) {
        if(x<2) return x;
        int left=2;
        int right=x/2;
        int mid=0;
        int tw=0; 
        while(left<=right){
            mid=(left+right)/2;
            long tw=(long)mid*mid;
            if(tw==x) return mid;
            else if(tw>x) right=mid-1;
            else left=mid+1;
        }
        return right;
    }
};
```
注意这里不加mid-1,mid+1直接用mid，那么循环不会停下来，由于没有+-1的写法最终肯定是left与right相差1，所以mid会赋值给left如此循环；所以这里用了mid-1,mid+1,一个是匹配了循环结束的条件，另一个是由于mid明显不是要找的数，+1与-1会加速进程；但是需要注意的是循环结束的条件变得复杂：可能是给mid加1加过头，left==right均大于mid然后再求一次mid,这时right会减1；也可能是mid减1过头，导致相反的情况，那这体现出return right的必要性了；
如果递归条件写成（left<right）,那么由于都是连续的整数，循环终止的情况一定是left==right,这时候f(left)的值到底是比要找的值大还是小就很难判断了，而代码中的写法一定有该值介于f(left) f(right）之间
#### 二分法写法2
```cpp
class Solution {
 public:
    int mySqrt(int x) {
        if(x<2) return x;
        int left=2;
        int right=x/2;
        int mid=(left+right)/2;
        int tw=0;
        while(left!=mid){
            long tw=(long)mid*mid;
            if(tw==x) return mid;
            else if(tw>x) right=mid;
            else left=mid;
            mid=(left+right)/2;
        }
        return mid;
    }
};
####二分写法3 递归二分
```cpp
class Solution {
 public:
    int mySqrt(int x) {
       if(x<2) return x;
       int left=2;
       int right=x/2;
       return dfs_binary(left,right,x);
    }
    
    int dfs_binary(int left,int right,int x){
        if(left>right) return right;
        int mid=(left+right)/2;
        if((long)mid*mid==x) return mid;
        else if((long)mid*mid>x) return dfs_binary(left,mid-1,x);
        else return dfs_binary(mid+1,right,x);
    }

};

```
```
二分法写法2，比较好理解，但注意mid的初始化和在循环中的位置，注意循环条件；还有要注意在本题中x<2分支处理了0，1，初值left==mid或者上一个方法中left>ight的处理处理了3或者3，4，后面才进入二分的逻辑
### 牛顿下山法
```cpp
class Solution {
 public:
    int mySqrt(int x) {
        if(x<2) return x;
        double x0=x;
        double x1=(x0+x/x0)/2;;
        while(abs(x0-x1)>=1){
            x0=x1;
            x1=(x0+x/x0)/2;
        }
        return x1;
    }
};
注意数据类型用double,float精确度不够；另外最精确的是x1不是x0
```
### 非二分递归
```cpp
class Solution {
 public:
    int mySqrt(int x) {
        if(x<2) return x;
        int left = mySqrt(x>>2)<<1;
        int right=left+1;
        return (long)right*right>x?left:right;
    }
    

};
```
注意最后一句的处理,由于计算机语言向下取整所以用right来补足1;位运算大幅度提升乘除法速度
## lc278 [第一个错误的版本](https://leetcode-cn.com/problems/first-bad-version/)
```cpp
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        unsigned int low=1;
        if(isBadVersion(low)) return low;
        unsigned int high=n;
        unsigned int mid=0;
        while(low<=high){
            mid=(low+high)/2;
            if(isBadVersion(mid)!=isBadVersion(mid-1)) return mid;
            if(isBadVersion(mid)) high=mid-1;
            else low=mid+1;
        }
        return mid;
    }
};
```
官方解法如下，说明我对二分的本质理解得并不透彻，二分的本质是使得if else两极越来越接近；另外在二分查找中，选取mid的方法一般为 \

mid=1/2* (left+right)。如果使用的编程语言会有整数溢出的情况（例如 C++，Java），那么可用mid = left + (right - left) / 2代替前者。

```cpp
public int firstBadVersion(int n) {
    int left = 1;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (isBadVersion(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
```
# 二分思想的延申
## 加减法 lc29 两数相除
```cpp
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend==0) return 0;
        if(divisor==1) return dividend;
        if(divisor==-1) {
            if(dividend==INT_MIN) return INT_MAX;
            else return -dividend;  
        }
        long A=dividend;
        long B=divisor;
        int sign=(A>0) != (B>0)?-1:1;
        if(A<0) A=-A;
        if(B<0) B=-B;
        return div(A,B)*sign;        
    }

    int div(long A, long B){
        if(A<B) return 0;
        long x_B=B;
        int res=1;
        while(x_B+x_B<=A){
            x_B+=x_B;
            res=res+res;
        }
        return res+div(A-x_B,B);    
    }
};
二分思想（翻倍）以及递归的应用，不是十分贴切可能；另外对负数，INA_MIN的处理

