贪婪很可能不是全局最优的，但有些时候他的部分解可以扩展到全局最优，这个需要数学归纳法，或者在每一步证明贪婪算法不比其他算法的选择差，或者基于算法的最终结果而不是过程证明它结果已经最优
prime和kruskal完整实现参考https://blog.csdn.net/wr132/article/details/43373991 （里面的邻接链表用了循环数组代替链表实现）
# Prim算法
生成最小生成树的算法;最小生成树是一个图上的边权重总和最小的树（包含所有的点）,这里我们只考虑连通图并且认为每条边的权重都不同，保证最小生成树的唯一性
## 树的基本性质
1.用一条边连接树的任意两个顶点会产生一个新的环
2.从树中删去一条边会得到两棵独立的树
## 切分定理
图的一种切分是将图的所有顶点分为两个非空且不重叠的集合。横切边是一条连接两个属于不同集合的顶点的边；在一幅加权图中，给定任意的切分，它的横切边中权重最小的必然属于图的最小生成树。
### 证明
今e为最小的横切边，T为最小生成树，如果T中不包含e，那么我们把e加入T,则必然得到一个环，这个环必然存在另外一个横切边f,而f>e,则我们如果把f换成e,则发现了一个权重更小的树，产生了矛盾
## 最小生成树的贪心算法
初始所有边都是灰色，对于任意的切分，其横切边都是灰色时，将最小的变为黑色，直到找到了|V|-1条黑色边
### prim算法
Prim算法是上述贪心算法的一种具体实现。从上述算法直接出发，则可以如下述生成最小生成树，找到目前横切边优先队列中最短的e，将其出队，加入最小生成树的边集E_t,然后对于e的两个顶点相连的另一个顶点未被mark的边加入优先队列,并mark这些点，然后再重复进行，直到优先队列为空(对于那些失效的边，会在最后出队但不是做任何操作)；
所以对
```cpp
vector<node> V;
int E[100][100];//该图的输入,该图务必是连通图
v=V.front();//任意一点作为初始顶点
V.pop();
priority_queue< node, vector<node>, less<node> > V_remained(V.begin(),V.end()); //优先队列，其中元素node按照node.weight排列,一开始node.weight= INT_MAX,node.prev= null;剩余元素集合，node的<需要重载，每个node的prev代表它离树最近的点
vector<pair<node,node>> E_tree; //表示prim树的边集，即为最后的结果
for(int i=0;i<V.size()-1;i++)//每次选出一个顶点加入最小生成树，∣V∣-1即可走完，不需要检查V_div是否为空{
    for (auto v_remained:E[v]){//这步操作时间复杂度为O(|V|),如果换成邻接链表，只需要遍历v相关的链表的成员，更新在remain中的标记即可，时间复杂度为O(|E|))
    if(v.isMarked()) continue;//排除已经在树中的点，否则V_div最小边可能不更新  
    if(E[v][v_remained.id]<v_remained.weight){
            //更新权重
            v_remained.weight=E[v][v_remained.id];//V_remained会自动排序
            v_remianed.prev=v;
            V_div.push_back(v_remained);
        }
    }
    v=V_div.front();
    V_div.pop();
    v.mark();
    E_tree.emplace_back(v.prev,v);
}
```
时间效率属于O(|E|log|V|),log|V|是堆内部（优先队列）更新操作
因为优先队列中的顶点数最多为 ∣V∣。算法会进行 V次插入 操作,V-1次删除最小元素操作以及E次验证操作验证是否一个端点在在灰色集中另一个在白色集中(这是按书上最保守的方法做的),故效率为(E+V-1)*logV为ElogV
# Kruskal算法
最小生成树的另一个算法
第二种最小生成树算法的主要思想是按照边的权重顺序（从小到大）处理它们，将边加入最小生成树中（图中的黑色边），
加入的边不会与已经加入的边构成环，直到树中含有V-1条边为止。
这些黑色的边逐渐由一片森林合并为一棵树，也就是图的最小生成树。
这种计算方法被称为 Kruskal 算法 。
证明Kruskal 算法能够计算任意加权连通图的最小生成树。
如果下一条将被加入最小生成树中的边不会和已有的黑色边构成环，那么它就跨越了由所有和树顶点相邻的顶点组成的集合以及它们的补集所构成的一个切分。因为加入的这条边不会形成环、它是目前已知的唯一一条横切边且是按照权重顺序选择的边，所以它必然是权重最小的横切边。因此，该算法能够连续选择权重最小的横切边，和贪心算法一致。
```cpp
V,E;//该图的输入,该图务必是连通图，V是个优先队列，其中元素node按照node.distance排列,一开始node.distance= INT_MAX,node.prev= null;
把E中的边按照长度进行排序；
E_tree; //表示prim树的边集E_tree为空
k=0；
while(valid_edge_num<V.size()-1)//每次选出一个除初始顶点外的顶点{
    k=k+1;
    if(E_tree与E[k]无回路）{//并查集可以省去该检查
        valid_edge_num++;
        E_tree.push_back(E[k]);
    }
}
return E_tree;
```
引入并查集进行优化
```cpp
//quick-union算法
V,E;//该图的输入,该图务必是连通图
把E中的边按照长度进行排序；
G_tree={V_tree,E_tree}; //表示prim树的边集E_tree为空,这里的E_tree为孤立的各点，
k=0；
while(valid_edge_num<V.size()-1)//每次选出一个除初始顶点外的顶点{
    k=k+1;
    v=E[k].first;
    u=E[k].second;
    tree_v=find(G_tree,v);//实际的实现应该是find((u,v)),
并不存在G_tree这个东西只有链表，找到了则不做任何事没找到再find(u) find(v)
当然这只是一个思路；也可已只记住点然后标记另一端的点
    tree_u=find(G_tree,u);
    if(tree_v!=tree_u) {
    union(tree_v,tree_u,(v,u),G_tree);
    valid_edge++;
    }//这就省去了查找是否是回路的操作
}
return E_tree;
```
也可以用一个数组set就可以完成并查问题，这个叫做quick-find算法
```cpp
//quick-find算法
V,E;//该图的输入,该图务必是连通图，E是边的vector
E_tree;//输出
把E中的边按照长度进行排序； 
k=0；
set[V.size()];
for(int i=0;i<V.size();i++){
    set[i]=i;
}//set里存的是根的位置，即点的下标
while(valid_edge_num<V.size()-1)//每次选出一个除初始顶点外的顶点{
    k=k+1;
    v=E[k].first;
    u=E[k].second;    
    if(set[v]!=set[u]) {
        //find操作，比较昂贵，需要遍历所有数字
        for(auto vv:V){
           if(set[vv]==set[u]) set[vv]=set[u];
        }
        set[v]=set[u];//合并操作
        E_tree.push_back(E[k]);
        valid_edge++;
    }//这就省去了查找是否形成回路的操作
}
return E_tree;
```
## 并查集
首先所有算法都把每个点都作为自己的根节点，有N个集，然后再进行find,union等操作直到把所有点进行了合适的归类
### quick-find
Quickfind 每个节点都指向根节点，find非常快，但union的时候需要遍历所有节点;每次find只需要访问数组一次，而uinion操作会调用两次find并检查所有N个元素并改变需要改变的元素（每次改变最多需要两次访问两次，读一次，改一次），因而访问数组的次数在N+3和2N+1之间
### quick-union
每个节点不必指向根节点而是指向另一个同属于一个分量的节点，直到指向根节点,union时只需要将一个节点的根节点指向另一个节点的根节点；该算法中find方法访问次数为节点深度加1，而union需要两次find;quick-union最坏的情况是长链的根节点一直向一个单节点上uinion
### 加权quick-union
它比一般的Quick-union好在小树往大树上添加，小树深度加1大树不动，整体深度不变，反过来大树深度加1整体加1,可以证明该算法生成的深度不超过log_2 K,K为节点总数, 这里需要用一个数组维护每个点的深度
### 加权quick union的最差情况
![](https://github.com/wangree/lc-practice/blob/master/algorithm-design/09.%E8%B4%AA%E5%A9%AA%E6%8A%80%E6%9C%AF/Screenshot_20211222_142657_com.flyersoft.moonreaderp.png)
### 压缩路权的quick union算法
对find方法进行修改，把find循环经过的每个点最后都链接到根上；但是这对于上面的情况可能无效，所以在每次union后，对深度大于1的点要进行find(但这里也引入了很大的复杂度，所以加权quick union其实已经足够好)
# Dijkstra算法
和prim算法有很大的相似性
单起点最短路径,起点s到所有其他点的最短路径及距离
用贪婪的策略去寻找，但保证全局最优主要靠更新,首先这个算法是基于bfs/dfs的,但是它pop的顺序比较特别，按照距离pop,这样可以保证pop点距离最短，因为如果已经遍历的点里有距离更短的点那么不会是该点pop
那会不会有没被遍历的点有更短的距离？也不会，因为这个点存在则它要么和起点直接相连，那一定会在目前出队列点之前被pop,如果从已遍历的其他点相连也是一样的;最终可以看成它是一种按照距离分层pop的遍历方法，更像bfs
```cpp
V,E,起点s;//输入，如果两点不相连，E为无穷
s.distance=0;
s.prev=null;
Q;//优先队列为空,按distance排序
for(auto vv:V){
    vv.distance= INT_MAX;
    vv.prev=null;
    Q.push(vv);
}
Vt=V;//
for (int i=0;i<V.size()-1;i++){
    u=Q.front();  //u是优先级最小的元素
    Q.pop();
    vt.erase(u);
    for (auto vv:Vt){
        if (E[vv][u]<INT_MAX){
            if (u.distance+E[vv][u]<vv.distance){ //这句就是中转点更新，路径更优的意思，也是该算法的精髓
                vv.distance=u.distance+E[vv][u];
                vv.prev=u;
                update(Q);
        }
    
}
 //类似算法有open close的区分 open指的是待更新 close表示已经找到最短距离 已经出队列 这里我们并没有采用类似思路 中途入队

```
# 哈夫曼树及其编码
也很简单思想，概率小的放的越深，编码长度越长
char字符按照使用概率排序后，取出前两个，其概率总和为其父节点，该节点又和其他字符一起排序，后面又取出前两个结点，生出一个新的第二层结点，如此往复，最后形成树后，左子树编码为0，右子树编码为1
