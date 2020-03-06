### lc [最小高度树](https://leetcode-cn.com/problems/minimum-height-tree-lcci/)
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return dfs(0,nums.size()-1,nums);
        
    }
    TreeNode* dfs(int left,int right,vector<int>& nums){
        if(left>right) return NULL;
        int mid=(left+right)/2;
        TreeNode* p=new TreeNode(nums[mid]);
        p->left=dfs(left,mid-1, nums);
        p->right=dfs(mid+1,right,nums);
        return p;


    }
};
```
注意递归思路和结束条件，以及为何要返回p.

另外以下这样写是错的，temp作为局部变量（栈区）其地址在函数结束后会被收回，无法return p
```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return dfs(0,nums.size(),nums);
        
    }
    TreeNode* dfs(int left,int right,vector<int>& nums){
        if(left>=right) return NULL;
        int mid=(left+right)/2;
        TreeNode temp(nums[mid]);
        TreeNode* p=&temp;
        p->left=dfs(left,mid, nums);
        p->right=dfs(mid+1,right,nums);
        return p;


    }
};
```
c语言版（c++使用malloc会报错做链表，所以最好使用new)
```c
    struct TreeNode* dfs(int left,int right,int* nums){
        if(left>=right) return NULL;
        int mid=(left+right)/2;
        struct TreeNode* p=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        p->val=nums[mid];
        p->left=NULL;
        p->right=NULL;
        p->left=dfs(left,mid, nums);
        p->right=dfs(mid+1,right,nums);
        return p;


    }



    struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
        return dfs(0,numsSize,nums);
        
    }
```
用栈做的迭代写法
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return NULL;
        int mid=(nums.size()-1)/2;
        TreeNode* root=new TreeNode(nums[mid]);
        TreeNode* p=NULL;

        stack<nodeinfo> s;
        nodeinfo start(0,nums.size()-1);
        start.node=root;
        s.push(start);
        
        nodeinfo temp(0,0);
        nodeinfo child(0,0);
        int left,right,val;
        while(!s.empty()){
            temp=s.top();
            s.pop();
            mid=(temp.prevleft+temp.prevright)/2;
            p=temp.node;
        
            
            left=temp.prevleft;
            right=mid-1;
            if(left<=right){
                val=(left+right)/2;
                p->left=new TreeNode(nums[val]);
                child.prevleft=left;
                child.prevright=right;
                child.node=p->left;
                s.push(child);
            }/*else{
                p->left=NULL;
            }*/;

            left=mid+1;
            right=temp.prevright;
            if(left<=right){
                val=(left+right)/2;
                p->right=new TreeNode(nums[val]);
                child.prevleft=left;
                child.prevright=right;
                child.node=p->right;
                s.push(child); 
            }/*else{
                p->right=NULL;
                }*/


            }
        return root;
}
        

private:
    struct nodeinfo{
        int prevleft;
        int prevright;
        TreeNode* node;
        nodeinfo(int x,int y):prevleft(x),prevright(y),node(NULL){};
    };
};
```
1.栈是一种工具，所以要看怎么用，出入栈的顺序由人掌控，本题并不是传统意义上的dfs创建二叉树形式，每一层在入栈时就做了访问，所以可能用队列也可以；而传统意义的dfs访问，一条路走到黑，而对一般问题而言入栈顺序是基本随着题目自然的结构而定的，但出栈顺序可以由自己掌控，所以一般问题一定是要在出栈时做访问的

2.发现迭代比递归还是要快：
递归与迭代的效率比较

我们知道，递归调用实际上是函数自己在调用自己，而函数的调用开销是很大的，系统要为每次函数调用分配存储空间，并将调用点压栈予以记录。而在函数调用结束后，还要释放空间，弹栈恢复断点。所以说，函数调用不仅浪费空间，还浪费时间。

这样，我们发现，同一个问题，如果递归解决方案的复杂度不明显优于其它解决方案的话，那么使用递归是不划算的。因为它的很多时间浪费在对函数调用的处理上。在C++中引入了内联函数的概念，其实就是为了避免简单函数内部语句的执行时间小于函数调用的时间而造成效率降低的情况出现。在这里也是一个道理，如果过多的时间用于了函数调用的处理，那么效率显然高不起来。

