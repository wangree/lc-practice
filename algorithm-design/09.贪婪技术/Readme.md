贪婪很可能不是全局最优的，但有些时候他的部分解可以扩展到全局最优，这个需要数学归纳法，或者在每一步证明贪婪算法不比其他算法的选择差，或者基于算法的最终结果而不是过程证明它结果已经最优
prime和kruskal完整实现参考https://blog.csdn.net/wr132/article/details/43373991 （里面的邻接链表用了循环数组代替链表实现）
# Prime算法
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
priority_queue< node, vector<node>, less<node> > V_remained(V.begin(),V.end()); //优先队列，其中元素node按照node.weight排列,一开始node.weight= INT_MAX,node.prev= null;剩余元素集合，node的<需要重载
vector<pair<node,node>> E_tree; //表示prim树的边集，即为最后的结果
for(int i=0;i<V.size()-1;i++)//每次选出一个除初始顶点外的顶点{
    for (auto v_remained:V_remained){//这步操作时间复杂度为O(|V|),如果换成邻接链表，只需要遍历v相关的链表的成员，更新在remain中的标记即可，时间复杂度为O(|E|))
        if(E[v][v_remained]<v_remained.weight){
            //更新权重
            v_remained.weight=E[v][v_remained];//V_remained会自动排序
            v_remianed.prev=v;
        }
    }
    v=V_remained.front();
    V_remained.pop();
    E_tree.emplace_back(v.prev,v);
}
```
时间效率属于O(|E|log|V|),log|V|是堆内部（优先队列）删除及更新操作
## prim算法正确性的证明

# Kruskal算法
最小生成树的另一个算法
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
以上的实现较为初始，实际实现可以说完全不是这样，用一个数组set就可以完成并查问题，而返回的树另选一个vecotr记录
```cpp
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
如果实现快速并查则效率主要取决于排序
## 由此引出的不相交子集和并查问题
子集的代表很重要 find(x)是在找代表，事实上并不存在树，而是会维护x的相关链接，从而利用链表形成树， 而合并的主要耗时也是在更新代表上
一种并查集已经在上面实现，查找快，直接set[i],但是合并要慢；另外一种链表型合并很快，但是查找慢
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
