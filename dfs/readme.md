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
