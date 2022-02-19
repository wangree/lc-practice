# 双指针
滑动窗口：一般是left right是左闭右开，右指针每向前滑动一次便形成一个候选解，滑动到某个程度构成一个可行解，在此基础上左指针开始滑动，以进行优化以得到最终解
滑动窗口中单调队列的实现：由于一般滑动窗口只关心最大或者最小值，比如这里假设是最大值，那么在加入一个元素的时候，队列中在他之前的元素且比它小的元素都是不可能再成为最大值的了，所以这里可以直接不要这些值，把新元素放在队尾；而删除元素的时候，仅仅在该元素最大时才删除，因为在其他情况下它都不会影响最大元素的产生，而那些在它之前比它小的元素之前都已经删掉了

## 去重移动类（快慢指针）
### lc26
删除排序数组中的重复项,这是非常经典的去重双指针算法；
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int num   = 0;
        int count = 0;
        int j   = 0;
        int len = nums.size();
        while (j<len) {
            if (j >0 && nums[j] == nums[j-1]){
                j++;
                continue;
            }
            nums[count++] = nums[j];
            j++;
        }
        return count;
    }
};
```
### lc80 删除排序数组中的重复项||
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i=0;
        for(int x:nums){
            if(i<2||x!=nums[i-2]){
                nums[i]=x;
                i++;
            }
        }
        return i;
    }
};
```
可以借鉴别人的思路

### lc27
与lc26的算法几乎如出一辙
```cpp
class Solution {
public:
    int removeElement(vector<int> &nums, int val) {
        int j = 0;
        for (int i = 0; i <nums.size() ; ++i) {
            if (nums[i]!=val){
                nums[j++]=nums[i];
            }
        }
        return j;
    }
};
```
### lc283 移动零
```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j =0;
        int len = nums.size();
        for(int i=0;i<len;i++){
            if (nums[i]!=0) nums[j++]=nums[i];
        }
        while(j<len){
            nums[j]=0;
            j++;
        }
        
    }
};
```
## 合并类(打带法）
### lc88 合并有序数组
```cpp
class Solution {
 public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums3(nums1.begin(),nums1.end()-n);
        int i = 0;
        int j = 0;
        int p = 0;
        while(i<m && j<n){
            nums1[p++]=nums3[i]<nums2[j]?nums3[i++]:nums2[j++];
        }
        if(j==n){
            while (i<m){
                nums1[p++] =nums3[i++]; 
            }
        }else{
            while (j<n){
                nums1[p++] =nums2[j++];
            }
        }
    }
};
```
这是非常经典的双指针算法，注意的一点是要copy出一个nums3来；使用的是while(i<len1 && j<len2)的双字符串型双指针
### lc977 有序数组的平方
双指针的话，类似于两个有序数组的拼接算法，该算法比较两个数组某位置上的数字大小，小的压入结果数组，并移动指针，大的指针不挪动，再进行比较，如此循环直到其中一个数组指针遍历结束，再把未结束的末尾部分放进结果数组中去；这里的区别主要是这个例子需要找出第一个大于0的位置把正负数分成两个数组。
体会到双指针的核心就是怎么挪指针。
使用的是i<j型的相遇型双指针，也是非常经典
### lc349 两个数组的交集
```cpp
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        int i = 0;
        int j = 0;
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<int> res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        while(i<len1 && j< len2)
        {
            if (nums1[i] == nums2[j] && find(res.begin(), res.end(), nums1[i]) == res.end())
            {
                res.push_back(nums1[i]);
                i++;
                j++;
            }
            else if (nums1[i] < nums2[j])
            {
                i++;
            }
            else if (nums1[i] > nums2[j])
            {
                j++;
            }
            else
            {
                i++;
                j++;
            }
        }
        return res;
    }
};
```
同合并有序数组的思想很相近
```cpp
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> res;
        set<int> set1(nums1.begin(),nums1.end());
        set<int> set2(nums2.begin(),nums2.end());
        set_intersection(set1.begin(),set1.end(),set2.begin(),set2.end(),insert_iterator<vector<int>>(res,res.begin()));
        return res;
    }
};
```
采用求set求交集的方法，效率较低
### lc350 两个数组的交集||
```cpp
class Solution
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        int i = 0;
        int j = 0;
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<int> res;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        while(i<len1 && j< len2)
        {
            if (nums1[i] == nums2[j] )
            {
                res.push_back(nums1[i]);
                i++;
                j++;
            }
            else if (nums1[i] < nums2[j])
            {
                i++;
            }
            else if (nums1[i] > nums2[j])
            {
                j++;
            }
            else
            {
                i++;
                j++;
            }
        }
    return res;
    }
};
```
注意与lc349的区别
### lc524 通过删除字母匹配到字典里的最长单词
```cpp
class Solution {
public:
    static bool compare(const string&a, const string&b){
        if(a.size()>b.size()) return true;
        else if(a.size()==b.size()) return a[0]<b[0];
        else return false;
    }
    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(),d.end(),compare);
        int lenj = s.size();
        int i=0;
        int j=0;
        int leni=0;
        for(auto word:d){
            i=0;
            j=0;
            leni=word.size();
            while(i<leni && j<lenj){
                 if(word[i]==s[j]) i++;
                 j++;
            }
            if(i==leni) return word;
        }   
        return "";
       
        
    }
};
```
也是典型的打带法
## 链表类 快慢指针型
### lc141 环形链表
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* temp=head;
        ListNode* slow=head;
        if(head) temp=temp->next;//错开一步
        while( temp && temp->next){
             if(temp==slow ) return true;
             slow = slow->next;
             temp = temp->next->next;
        }
        return false;
    }
};
```
链表中快慢指针的使用非常经典
### lc142 环形链表||
```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        //phase1
        ListNode* fast;
        ListNode* slow;
        if(head && head->next){
            fast=head->next->next;
            slow=head->next;
            }else{
                return NULL;
            }
        while(fast && fast->next){
            if(slow==fast) break;
            fast=fast->next->next;
            slow=slow->next;
        }
        if(fast==NULL||fast->next==NULL) return NULL;
        //pahse2
        ListNode* temp=head;
        while(temp!=fast){
            temp=temp->next;
            fast=fast->next;    
        } 
        return fast;


    }
};
```
快慢指针追及问题，快指针速度为2v,慢指针为v,相遇的条件为
(2v-v)*T=L(L为环长)
可知两者相遇的位置是慢指针走到距离头指针环长位置处，因而第二阶段，指针temp从头指针出发和fast以相同速度前进,两者相遇应在环入口处
### lc287 lc142在中数组中的应用
```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow=0;
        int fast=0;
        while(true){
            slow = nums[slow];
            fast = nums[nums[fast]];
            if(slow==fast){
                break;
            }            
        }
        int finder=0;
        while(true){
            fast=nums[fast];
            finder=nums[finder];
            if(fast==finder) break;
        }
        return finder;    
    }
};
```
完全借鉴了lc142的思路，把数组当作环形链表处理；具体分析可见：
[快慢指针的解释](https://leetcode-cn.com/problems/find-the-duplicate-number/solution/kuai-man-zhi-zhen-de-jie-shi-cong-damien_undoxie-d/)
### lc457 环形数组循环
```cpp
class Solution {
public:
    void setZero(vector<int>& nums,int i){
        //nums[i]=0;
        int len = nums.size();
        int j = 0;
        while(true){
            j = (i+nums[i]+500*len)%len;
            
            if(nums[j]==0||nums[i]*nums[j]<0) {
                nums[i]=0;
                break;}
            nums[i]=0;
            i=j;
            
        }
    }
    bool circularArrayLoop(vector<int>& nums) {
        int slow=0;
        int fast=0;
        int len=nums.size();
        int last_slow=0;
        int last_fast=0;
        if(len<=1) return false;
        for(int i=0;i<len;i++){
        if(nums[i]==0) continue;
        slow=i;
        fast=i;
        
        while (true){
            last_slow=slow;
            slow=(slow+nums[slow]+500*len)%len;
            if(last_slow==slow||nums[last_slow]*nums[slow]<0||nums[slow]==0) {
                setZero(nums,i);
                break ;}
            last_fast=fast;
            fast=(fast+nums[fast]+500*len)%len;
            if(last_fast==fast||nums[last_fast]*nums[fast]<0||nums[fast]==0) {
                    setZero(nums,i);
                break ;}
            last_fast=fast;
            fast=(fast+nums[fast]+500*len)%len;
            if(last_fast==fast||nums[last_fast]*nums[fast]<0||nums[fast]==0) {
                setZero(nums,i);
                break ;}
            if(slow==fast) return true;
        }
        
        }
      return false;
    }
};
```
此题需要注意的地方很多：500*len为了防止有狠大的负数出现，对于数组环形的认识正确的应该是不是从0开始走时所有的元素都能遍历到，所以需要有外层for循环，另外也不是一开始就能进入循环（比如1，1，1，2）；所以只能是通过置0来剪枝，如果碰到不符合要求的nums[j],从i出发置0，直到碰到已经置0的点或者异号的位置。
### lc19 删除链表的倒数第N个节点
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
        dummy->next=head;
        dummy->val=0;
        ListNode* fast = dummy;
        ListNode* slow = dummy;
        while(fast!=NULL){
           fast=fast->next;
           if(n>=0) {
               n--;
               continue;}
               slow=slow->next;
        }
        slow->next=slow->next->next;
        return dummy->next;    
    }
};
```
快慢指针的使用也是非常经典，也注意dummy指针的必要性


### lc234 回文链表
```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL) return true;//有些奇怪的用例，写出来比较好
        ListNode* halfTail = find_half_of_list(head);
        ListNode* halfHead = reverseList(halfTail->next);
        while(head!=NULL && halfHead!=NULL){
            if(head->val!=halfHead->val) return false;
            head = head->next;
            halfHead=halfHead->next;
        }
        return true;
    }
    ListNode* find_half_of_list(ListNode* head){
        ListNode* fast=head;
        ListNode* slow=head;
        while ( fast->next && fast->next->next){
            fast=fast->next->next;
            slow=slow->next;
        }
        return  slow;
    }

    ListNode* reverseList(ListNode* head){
        ListNode* prev = NULL;
        ListNode* temp = head;
        ListNode* reverseNext;
        while(temp){
            reverseNext=temp->next;
            temp->next=prev;
            prev=temp;
            temp=reverseNext;
        }
        return prev;
    }
};
```
使用了快慢指针来找链表最中间的位置，注意考虑下奇偶数的问题；然后将后半段进行比较。

## 链表类 基本型
### lc61 旋转链表
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==NULL) return head;
        ListNode* temp = head;
        int length=1;
        while(temp->next!=NULL){
            temp=temp->next;
            length++;
        }
        temp->next=head;
        k%=length;
        int opt = length-k;
        temp=head;
        while(opt>1){
            temp=temp->next;
            opt--;
        }
        head=temp->next;
        temp->next=NULL;
        return head;
    }
};
```
环形链表的使用，和双指针其实关系不大

### lc 分隔链表
```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* smallhead=(ListNode*)malloc(sizeof(ListNode));
        ListNode* largehead=(ListNode*)malloc(sizeof(ListNode));
        ListNode* temp=head;
        ListNode* small=smallhead;
        ListNode* large=largehead;
        while(temp){
            if(temp->val<x){
                small->next=temp;
                small=small->next;
            }else{
                large->next=temp;
                large=large->next;
                }
            temp=temp->next;  
        }
        large->next=NULL;
        small->next=largehead->next;
        return smallhead->next;   
    }

};
```
注意这中间对创建链表的启示
创建链表法出错，lc提示alloc-delloc-mismatch，所以这里就是说不能去申请新的链表而使用原链表，因为这里leetcode后台只会释放原链表：
```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* smallhead=(ListNode*)malloc(sizeof(ListNode));
        ListNode* largehead=(ListNode*)malloc(sizeof(ListNode));
        ListNode* temp=head;
        ListNode* small=smallhead;
        ListNode* large=largehead;
        while(temp){
            if(temp->val<x){
                small->next=temp;
                small=small->next;
            }else{
                large->next=temp;
                large=large->next;
                }
            temp=temp->next;  
        }
        large->next=NULL;
        small->next=largehead->next;
        return smallhead->next;   
    }

};
```

## 回文类
### lc125 验证回文串
```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int i=0;
        int j=s.size()-1;
        while(i<j){
            if (s[i]<'0'||('9'<s[i]&&s[i]<'A')||s[i]>'z'||('Z'<s[i]&&s[i]<'a')) {i++;
            continue;}
            if (s[j]<'0'||('9'<s[j]&&s[j]<'A')||s[j]>'z'||('Z'<s[j]&&s[j]<'a')) {j--;
            continue;}
            if(s[i]!=s[j] && tolower(s[i])!=tolower(s[j])  ) return false;
            i++;
            j--;
            
        }
        return true;
        
    }
};    
```
### lc344 反转字符串
```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        int length = s.size();
        int i=0;
        int j=length -1 ;
        char temp = 0;
        while (i<j)
        {
            temp=s[i];
            s[i]=s[j];
            s[j]=temp;
            i++;
            j--;
        }
    }
};
```
