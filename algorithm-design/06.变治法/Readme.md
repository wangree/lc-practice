# 变治法
实例化简和改变表现的不同之处在于实例化简相当于预处理了一步，数据与之形式没有发生改变，比如高斯消元法处理前后还都是矩阵，avl树变换然后都是二叉查找树，所谓同一问题的另一个实例，改变表现是改变了数据或者更宽泛来说实例的组织形式，同一个实例的另一个表现形式，而问题化简是转换成了另一个问题
## 实例化简（instance simplification)
预排序是在查找元素，处理点集问题（快包，最近对），有向无环图（先进行拓扑排序），贪婪算法,高斯消元法(求逆,高斯若尔当消元（在消去主元下面的元素后还消去其上面的元素）等等）中大量应用的
预排序,同样问题的一个更简单的实例，将具体实例经过一定的处理
### 电话账单匹配问题
如果有N个电话账单，m个已支付支票(每个支票只能对应于一个账单，并且一次性全部付清),设计算法得出哪些电话还没有被支付
#### 算法
类似于Merge sort的思路，电话账单和支票都按电话号码排序,电话账单对应的电话号码是so,支票是bj,如果$ a_i<b_j $则I++,如果$ a_i>bj $则j++, 如果两者相则记录都++,直到有一个为空，则另外一个为unpaid list
### 区间重叠个数算法
有一堆区间左端点为Ai，右端点为Bi，设计算法计算最大重叠区间个数
#### 算法
初始化Res为0
先把所有端点排序，然后从左到右扫描，如果碰到ai则加1，碰到bj则减1，记录整个过程中最大的res
另外一种算法是对A和b分别进行排序，然后用类似于合并排序的算法，如果AI<=bj则认为遇到一个区间开始则res加1,如果Ai>bj则认为遇到了一个区间结束则减1,j++，最后得到res的最大值作为结果
### 寻找最大点
对于二维平面上的点集，最大点定义为没有比其x大而且y大的点，设计算法求点集的最大点
#### 算法
所有点按照x从小到大进行预排序，如果x相等则根据y从小到大排序;这时候从右向左进行扫描，如果到某一步，得到y是目前最大的，则这个点是一个最大点，然后继续扫描到头，得到所有最大的点
### 矩阵模拟开关灯
n*n的面板，如果打开或者关闭其中一个面板也会打开和关闭其领接的4个面板，现在已知初始面板的开闭情况为矩阵s,求全闭应该怎么关面板
$$ s = \sum_{i,j=0}^n x_{ij} *A_{ij} * F + S = 0$$
根据二进制，这等价于$$\sum_{i,j=0}^n A_{ij} * F = 0 $$
$A_{ij}$是开关或者关闭（i,j）上的面板的影响，$x_{ij}$是要不要打开这个位置的面板
## 改变表现（representation change)
结合实例化简的例子是,查找树（AVL,23树，红黑树），霍纳算法，乘方问题,变换为同样实例的不同表现，化简形式
## AVL树
在二叉树进行插入时如果导致某个子树的不平衡度绝对值变为2，则要进行旋转以保证不平衡度绝对值小于1,有左单转，右单转，左右双转三种旋转方式，需要注意的是旋转导致有三个子节点时选择节点的问题，比如右转时会有两个右节点，要选择新的右节点，把原右节点变为新右节点的左节点；注意旋转的是最近的不平衡的节点为根的树；
AVL树的最小和最大节点并不总是位于最后或者倒数第二层
## 23树
插入的时候如果原来是两节点则插入即可，如果原来是3节点需要分裂，左侧节点作为一个其父的左子节点，中间节点向上融合到父节点，右节点作为其父节点；作为红黑树的原型它是完美平衡的。在节点数比较少时，23树的查找并不比二叉树快
## 红黑树
将2-3树的3节点变为一条链接两个节点的左链接，并且变为红链接，其中间结点变为其左子节点的右节点便可以成为红黑树；红黑树必须遵守的规则是：1.红链接只能是左链接；2.两个红链接不可相连；3.该树是黑色链接完美平衡的。红黑树的旋转操作和avl树大体相似，不同主要体现在其旋转并不是由不平衡度触发的，而是由颜色相关特性触发的：对于一个节点，插入新键（默认为红链接）时有三种情况会触发旋转：1.左侧为黑链接，右侧为红色链接，这时候需要左旋，新键为子树的根节点 2.左右均为红色链接，这时候需要翻转颜色，两个子节点颜色变黑，父节点变红 3.右侧为黑链接但左侧有连续的红链接，这时候需要右旋，中间节点作为子树的根节点（2，3和2-3树向上分裂的操作等效，1是错误的红链接位置进行的调整不对应2-3树的操作
删除算法：未直接实现红黑树的删除，这里是23树的删除，首先和删二叉树的方法一样找到该节点，然后找到该节点右子树中最小节点，顶替它，并且最小节点右节点变为删除最小节点；删除最小节点的方法与二叉树不同：
首先查找该键过程中，如果最小键所在点为3节点则直接删除，为2节点时如果和其兄弟节点均为2节点可以向上融合为一个4节点，如果其兄弟节点为3节点，则可以通过父节点向其借键，也将其变为4节点
### 红黑树效率
插入查找删除都是对数级别，大小为N的红黑树最高不会超过2lgN,平均高度为lgN,是第一个能保证最差也是对数的算法
### 堆的构造和堆内元素的删除，堆排序
#### 堆的构造
首先是堆的一般表示方法，并不会表示成真正的树结构, 而是用数组来表示，0位置用一个intmax作为限位器，其他其他位置对于I,2i和2i+1为其子节点；以下算法都针对最大堆  
自底向上的构造方法，对于无序数组，从最右侧的父节点k_0开始，记录其值为v,检查它与其子节点中最大的哪个大,如果它更大，则继续检查左侧相邻节点，如果它小，则把最大子节点的值赋给它，检查最大子节点的子节点和v的大小，如此循环，直到满足要求或者父节点已经是叶节点，再把v赋给这个节点，然后再去检查k_0左侧父节点；而自顶向下的算法是先将K放在堆的最后一个元素，再不断交换它与父节点的位置直到满足要求或者到达根节点  
自底向上和自顶向下的构造堆的方法产生的堆不一定相同比如初始元素为123的堆，自底向上算法效率为O(2n),自顶向下算法每次插入效率为O(logn)
#### 堆中元素的删除
交换该元素和最后一个元素，并检查原最后一个元素元素应该放置的位置(向上检查或者向下检查，只能有一个方向)
#### 堆排序
堆排就是先构造好堆，每次删除根(即把根放在最后一个元素)，直到删完就自然排好序了;堆排序并不稳定，两个相等的1会被调换顺序 (效率为O(n)+O(nlogn))
#### 一些结论
堆中查找并没有特别好的方法，就是线性查找；最小元素总在叶节点中，最后一半元素恰好对应于叶节点；堆总是完全二叉树，完全二叉树是指所有元素和满二叉树位置相同的树；  
另外，堆最常用的实现是下沉最大元素(这里只针对最小堆),自底向上的构造堆，删除最小元素都是依靠这个操作，而删除普通元素两个方向可能都有，自顶向下的插入就是上升了
### 霍纳法则
多项式的求值可以简化为$ x(a_n*x+a_{n-1})+a_{n-2}.. $,$a_n$是指n次项的系数；此外，霍纳法则还有一个副产品，那就是在$x=x_0$时每次产生的中间结果作为系数的多项式f(x)是原p(x)除以x-x_0的值,p(x_0)为余数，这一点的证明可以由余数定理p(x)=(x-x_0)f(x)+p(x_0)，再分别展开f(x)和p(x)带入到上式左右通过系数对比可以求出f(x)的各次项
### 霍纳法则的推广
在要求A^x时，我们可以首先得到x的二进制表示，有$x=2^{i}*1... $ 根据霍纳法则可以从高位开始$A^(2*b_i+b_{i-1})$,由这个公式可以明显得到，如果上一步结果为p,则计算到二进制位i时有$ p=p^2*p^(b_i) $,依次递推,此方法可以进一步优化为每次除2查看余数来得到b_i；此外，还有一种算法是得到二进制表示后每次累乘A得到第i位的二进制对应的基础值，然后根据这位是不是1决定要不要累乘进去
霍纳法则是普通的多项式计算的2／3，只算乘法是原来次数的0.5倍
## 问题化简（problem reduction)
变换为另一个问题的实例，数学建模，线性规划，求最小公倍数，计算图中的路径数，函数优化问题的化简，简化为图的问题（农夫与狼，三壶问题）
### 通过邻接链表求路径长度为k的路径个数
如果邻接矩阵为A，则A^k的值中 a_{ij}为从i到j的路径的个数，这个将问题化简为了求矩阵乘积.另外求最小公倍数可以化简为求最大公约数
### bfs生成状态空间树
也是一种问题化简的例子
## 多米诺骨牌环
边可以代表一张牌，边两侧节点是牌上的两个数字，所有牌的邻接矩阵对应的图，如果存在欧拉回路，则可以成环
## 吃醋丈夫谜题
有N对夫妻，一艘仅能容纳两人的船，要求无论在船上还是岸上不能有除了配对夫妇外落单的女人，问怎样到达对岸

这图是N为2的情况；图2为3对情况，两个黑框状态互为始终状态；在n>3时候，按照图3进行到第6步时n-1对在原本的岸边，船也在这边，一对在对岸，这时候无法让两个丈夫上船执行第7步因为这时候会有女人落单，只能上一对夫妇，这时候就又回到了前面的状态，因此问题无解
