# 基本型
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
####二分法写法2
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
```
二分法写法2，比较好理解，但注意mid的初始化和在循环中的位置，注意循环条件；还有要注意在本题中x<2分支处理了0，1，初值left==mid或者上一个方法中left>ight的处理处理了3或者3，4，后面才进入二分的逻辑
### 牛顿下山法

