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
