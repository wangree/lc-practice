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
