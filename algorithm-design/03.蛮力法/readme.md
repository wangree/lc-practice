## 3.1选择排序与冒泡排序
冒泡排序需要一直交换，选择排序是最终再发生交换
### 习题3.1
#### 二进制位数所描述的效率：
线性算法 基本操作数为N n≈2^b 那么如果用b来描述 则算法每增加一位二进制 则需要的时间是指数级别的
也就是这个跨步是比较大的 比N一步一步的跨要大很多
#### 对于a^n mod m如何更快的进行处理？
可以使用递归的思想 拆成 ((a^n-1 mod m)*(a mod m))mod m
#### 计算二项式的值的优化
笨办法是在计算每一项时进行单独的计算 优化的办法是算出一项后在下一项乘以底数

## 3.2顺序查找与蛮力字符串匹配
### 习题3.2
### 两个仪器 测试使其坏的最高楼层 一个坏了以后可以用另一个 最佳方法是：
√n查找法 以√n为步长进行测试 具体到某步中 再以1为单位进行测试 效率不会低于2√n 无法使用二分 因为只有两个仪器 二分只能查找两次
### 为什么从右向左字符串匹配更好
Comparing pairs of the pattern and text characters righ-to-left can allow
farther pattern shifts after a mismatch
### 蛮力算法查找以a开头 以b结尾的子串线性改进版
存储a的个数A 和 要求的子串数目sub,初始值均为0,从左到右碰到一个a则为增加a的数目，碰到一个b，则sub加当前A，最后返回sub

## 3.3最近对和凸包问题的蛮力算法
### 最近对问题
典型的蛮力法解决的问题，蛮力法也有技巧进行优化，比如不要重复计数等等
更进一步的优化是 按照X Y的顺序分别排序 计算相邻点的距离 注意是两次排序 
### 凸包问题
N^3的算法 检测两点连线 是否把其他所有点隔在一侧 如果是 则该两点算凸包内 凸包上的点是极点
### 线性时间内找出一对极点
X最小的点(如果有x相同的则取Y最小的) 和最大的点
### 奇数派问题
每个人手里有一块蛋糕 会扔给他最近的人 证明如果是奇数个人 则一定会有人没有被扔到
#### 解决的思路是最近对和数学归纳法，考虑3个人的情况，最近对会互相仍蛋糕，那么第3个人不会被扔到
考虑n个人的情况 最近对互相扔 如果没有其他人扔蛋糕给最近对 则回归到n-2的情况，按照归纳法的假设，这n-2中会有人没有被扔到；如果有人扔给最近对 剩下的n-2个人的蛋糕显然已经不能满足扔给他们中每个人蛋糕 因为有一块已经扔出去了
## 3.4 穷举查找
## 旅行商问题
最短哈密顿回路问题 哈密顿回路：由一点开始 不重复的遍历到所有点再回到起点的回路 一般蛮力方法是先生成排列 再进行检查是否中间有断连的情况
### 欧拉回路
欧拉回路是由一点开始 不重复的遍历到所有路径再回到起点的回路 判断一个图是否具有欧拉回路就是判断每个点的度是否为偶数 对于n×n的邻接矩阵 显然时间线效率为O(n^2)
### 全排列的生成
在手动生成排列时有一个重复的动作，就是选择下一个子节点，这个就是实现递归的基础，对于点I,我们可以用I到n之间的点，与I互换，即I的位置是代表实际的下一个节点，递归调用结束后，再换回来，供下一个排列使用；复制法,初始是只有一个set,vector的pair组成的vector,每次从set里拿出去一个，这个放到记录的vector里，剩下的set复制给内层循环，比较费事的是每次都必须复制，vector和set都要，比较消耗空间；   
另外也可以使用Stack,每次拿到栈顶的序列，记录序列中剩下的元素，同时需要记录路径;另外递归也有一种思路是dfs递归访问，记录visit值，从非visit开始进行下一层的访问，内层调用访问完毕后将visit置0；栈版本也可以借鉴该思路，到叶节点时对该元素的visit进行置0,则不需要进行visit的复制，只需用指针   
非递归字典序的实现：
首先需要输出字典序最小的序列，即从左到右都是按照字典序从小到大排列，然后从右至左依次扫描到某个元素j大于其下一个元素j+1，在j+1和n之间从n到j+1扫描到第一个大于j的元素k，即j+1到n之间大于j的最小元素,将k与j互换，再将现在的j+1到n之间由大到小的顺序变为由小到大
全排列算法总结：
https://blog.csdn.net/yoer77/article/details/53458612
### 有重复元素的全排列生成
有重复元素时，会生成多余的结果；因而在递归交换时，要检查交换两者之间又没有等于后者的，有的话不做递归访问；
对于dfs递归版本，要剪掉在同一层之间相同的节点，即用一个临时变量记录同一层的节点，有相同的则不再进行递归访问；  
对于字典序就没有这个问题

## 背包问题
首先穷举出所有的组合（物品数目种类是有限的)，再check是否背包背得下，然后再得出一个价值，进行比较
## 分配问题
## dfs
完整的dfs/bfs给每个节点记录距离/访问次数,借此标记已访问，以防止出现回边/交叉边访问，由于router这种代码没有环状路线，并且有向，所以并没有考虑这种情况；另外，标准的dfs/bfs要求访问每一个点，所以每一个点都要作为起点
## bfs
除了和dfs一样检查无环性和连通性，还可以用来求最短路径
### bfs记录路径的方法
可以通过倒着从特定终点进行一次bfs的方式，加上条件cur_dis=prev_dis+1,就可以找到要的那条特定终点特定长度的路径，具体可见
[bfs路径记录](https://www.cnblogs.com/astonc/p/10639091.html)
算法书中建议的回溯法，需要队列能加label(pre)，并且进行递归回溯：[回溯法](https://www.jianshu.com/p/7570ce8aa833)
比较耗费空间，但不需要再来一次的方法参考：[正向记录](https://blog.csdn.net/lanshan1111/article/details/90243923)
[两种bfs路径记录的思路](https://www.cnblogs.com/Lis-/p/10572619.html)，是以上方法的体现,但记录前序使用了循环数组
除了进行两边bfs的方法，其他方法均要在经过的每个点都记录pre或者整个正向路径，比较耗费空间
dfs应该也是用相同的思路来记录路径
### 标准形式
对于dfs/bfs,入队/栈和出队/栈的时机都可以做访问或者check，没有明显的区别，根据需要来做
### 习题3.5
#### 证明对于无向图bfs树的交叉边，要么是连接同层的顶点，要么是链接bfs树相邻层的顶点
反证法：如果交叉边连接两层及其以上的顶点u和v，则对于距离d(u)和d(v)，d(u)>=d(v)+2,而如果有交叉边，d(u)=d(v)+1,显然矛盾
#### 三壶问题
最先要做的是生成下一个状态的函数，注意其中的指针问题；这个状态指的是3个水壶之间一个是倒入的水壶，一个是接收的水壶，c 3 2种可能产生的状态进行bfs遍历
```cpp
vector<int*> new_state(int state[3]){//vector<int[3]>是不允许的
    vector<int*> res;
    for (int i = 0; i <3 ; ++i) {
        if(state[i]>0) {
            for (int j = 0; j < 3; ++j) {
                if (j != i) {
                    int* tmp=new int[3];//如果在这里使用int tmp[3],这种在栈区的使用方法，函数结束后指向的内存会被释放，因而会res里的结果会是乱码
                    tmp[0]=state[0];//tmp[3]放在外面更不对，因此使用new,堆区内存不会自动释放
                    tmp[1]=state[1];
                    tmp[2]=state[2];
                    if(full[j]-state[j]>state[i]) {
                       tmp[j]+=state[i];
                       tmp[i]=0;
                   } else{
                       tmp[j]=full[j];
                       tmp[i]-=full[j]-state[j];
                   }
                    res.push_back(tmp);
                }
            }
        }
    }
    return res;
}
```
与本文无关的加一条：https://www.cnblogs.com/bookdrip/articles/9844675.html
数组指针指向的内存和该指针本身地址是一个位置，猜想这是因为其地址是一个二维数组首地址，数组不管几个维度，首地址都在一起。
方便起见，最后还是使用了array,完整代码如下：
```cpp
#include "common.h"
array<int,3> state;
int full[3];
struct node{
    array<int,3> state;
    vector<array<int,3>> road;
};
vector<array<int,3>> visited;
vector<array<int,3>> new_state(array<int,3> state){
    vector<array<int,3>> res;
    for (int i = 0; i <3 ; ++i) {
        if(state[i]>0) {
            for (int j = 0; j < 3; ++j) {
                if (j != i) {
                    array<int,3> tmp=state;
                    if(full[j]-state[j]>state[i]) {
                       tmp[j]+=state[i];
                       tmp[i]=0;
                   } else{
                       tmp[j]=full[j];
                       tmp[i]-=full[j]-state[j];
                   }
                    if(find(visited.begin(),visited.end(),tmp)==visited.end())
                    {
                        res.push_back(tmp);
                        visited.push_back(tmp);
                    }
                }
            }
        }
    }
    return res;
}
vector<array<int,3>> bfs(array<int,3> state){
    queue<node> qs;
    node tmp_node,ttmp_node;
    tmp_node.state=state;
    qs.push(tmp_node);
    vector<array<int,3>>nState;
    while (!qs.empty()){
        tmp_node=qs.front();
        qs.pop();
        nState=new_state(tmp_node.state);
        for (auto tmp_state:nState ) {
            ttmp_node.state=tmp_state;
            ttmp_node.road=tmp_node.road;
            ttmp_node.road.push_back(tmp_state);
            for (int i = 0; i <3 ; ++i) {
                if(tmp_state[i]==4) return ttmp_node.road;
            }
            qs.push(ttmp_node);
        }
    }
    ttmp_node.road.clear();
    return ttmp_node.road;

}
int main(){
    //state[1]=3;
    state[2]=8;
    full[0]=3;
    full[1]=5;
    full[2]=8;
    vector<array<int,3>>res=bfs(state);
    return 0;
}
```
