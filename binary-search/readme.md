# 基本型
### lc69 x的平方根
####暴力法
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
