# 双指针
对于双指针，大循环while里有两种循环，一种用if continue,这可以只需要给出移动一步的条件再continue即可，而另外一种需要while滑到头的，需要在这层while里加上
外层while的循环条件
对比lc-345.cpp与lc-345compare.cpp，可以看看其他人是怎么写的，应该有所借鉴

### lc3
无重复字符的最长子串
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        static int slice[128];
        memset(slice, 0, sizeof(slice));
        int res = 0;
        for (int i=0,j=0; j < s.size(); ++j) {
            i = max(i, slice[s[j]]);
            slice[s[j]] = j + 1;
            res = max(res, j - i+1);
        }
        return res;
    }
};
```
使用slice[128]是因为ASCII码里共有128个，从0开始至127；这个算法的关键是左指针i的移动；一开始我写的时候会用hashmap记录右指针遍历过的字母及其位置+1，如果发现重复就挪动左指针向右一位，hashmap删除i,右指针不动继续;后来改进为发生上述情况后左指针挪动到发生重复的字母上次位置的右边（hashmap已经记录）；后来引入了slice的方法，不再查找hashmap而是比较i和slice[s[j]]的大小，s[j]在i之前出现则说明i开始的子串无重复，在i之后出现则说明已经重复了，那就把i跳到s[j]前一次出现位置+1的位置;每次更新到slice[s[j]]且更新res。
此题的比较典型的子串使用双指针的情况，关键还是i怎么挪动，j需不需要每次i挪动的时候再重置，用slice[s[j]]作用和hashmap是一样的，max这句是使得我们不需要在遍历一个新的子串时清空hashmap
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
        if(head!=NULL) temp=temp->next;
        while(slow!= NULL && temp!=NULL && temp->next!=NULL){
             if(temp==slow && temp!=NULL) return true;
             slow = slow->next;
             temp = temp->next->next;
        }
        return false;
    }
};
```
链表中快慢指针的使用非常经典
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
## 和差类
### lc532 K-diff
几种解法：
#### hasmap
```cpp
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) return 0;
        map<int, int> hash;
        int counter = 0;
        for (int value: nums) hash[value]++;
        if (k == 0){
            for(auto it = hash.begin(); it != hash.end(); it++){
                if (it->second > 1) counter++;
            }
        }else{
            for(auto it = hash.begin(); it != hash.end(); it++){
                int value = it->first + k;
                if (hash.find(value) != hash.end()) counter++;
            }
        }
        return counter;
    }
};
```
#### 双指针（在暴力的基础上改进,左指针版）
```cpp
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int len=nums.size();
        int res=0;
        int j=1;
        for (int i = 0; i <len-1 ; ++i) {
            if(i>0 && nums[i]==nums[i-1]) {
                //i++;
                continue;
            }
            j=j>=i+1?j:i+1;
            while(j<len){
                if(j>i+1 && nums[j]==nums[j-1]){
                    j++;
                    continue;
                }
                if(nums[j]-nums[i]>k) break;
                if(nums[j]-nums[i]==k) {
                    res++;
                    break;
                }
                j++;
            }
            
        }
        return res;

    }
};
```

#### 右指针版
之所以更快是因为有low<high这条，不仅使得low遍历时不用到len长度，而且high在增加时low不用改变
```cpp
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int len=nums.size();
        int res=0;
        int high=1;
        int low=0;
        for (; high <len ; ++high) {
            if(high>low+1 && nums[high]==nums[high-1]) continue;
            while (low<high){
                if(low>0 && nums[low]==nums[low-1]) {
                    low++;
                    continue;
                }
                if((nums[high]-nums[low])>k){
                    low++;
                } else if((nums[high]-nums[low])<k){
                    break;
                }else{
                    res++;
                    break;
                }
            }
        }
        return  res;

    }
};
```
### lc167 两数之和||-输入有序数组
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int temp = 0;
        int i=0;
        int j=numbers.size()-1;
        while(i<j){
            temp = numbers[i]+numbers[j];
            if(temp == target) return {i+1,j+1};
            else if(temp<target) i++;
            else j--;
        }
        return {i+1,j+1};
    }
};
```
此为此类题目的经典算法
### lc15 三数之和
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> temp;
        int len = nums.size();
        int j = 0;
        int k = 0;
        for (size_t i = 0; i < len; i++)
        {
            if(nums[i]>0) continue;
            j=i+1;
            k=len-1;
            while (j<k)
            {
                if(i>0 && nums[i]==nums[i-1]){
                    break;
                }
                if (nums[j]+nums[k]>0-nums[i])
                {
                    k--;
                }else if(nums[j]+nums[k]<0-nums[i])
                {
                    j++;
                }else
                {
                    if (j-1>i && nums[j]==nums[j-1])
                    {
                        j++;
                        continue;
                    }else if(k+1<len && nums[k]==nums[k+1] )
                    {
                        k--;
                        continue; 
                    }
                    res.push_back({nums[i],nums[j],nums[k]});
                    k--;                                       
                }
           }
            
        }
        return res; 
    }
};
```
### lc18 四数之和
此题为此类题的究极形态，和三数之和的思路相似，由此可以掌握通用的去重（尤其是l>i+1这样的条件），求几数之和的方法，另外max和min的剪枝也是通用的，也是亮点;用纸梳理各种不同的用例情况，做到严密也是个好习惯
```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums,int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int len = nums.size();
        if(len<4) return res;
        int j = 0;
        int k = 0;
        int sum = 0;
        int max = 0;
        int min = 0;
        for (size_t i = 0; i < len - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            min=nums[i]+nums[i+1]+nums[i+2]+nums[i+3];
            if(target<min) break;
            max=nums[i]+nums[len-3]+nums[len-2]+nums[len-1];
            if(target>max) continue;

            for (int l = i + 1; l < len - 2; ++l) {
                if (l > i+1 && nums[l] == nums[l - 1]) {
                    continue;
                }
                min=nums[i]+nums[l]+nums[l+1]+nums[l+2];
                if(target<min) break;
                max=nums[i]+nums[l]+nums[len-2]+nums[len-1];
                if(target>max) continue;
                j = l + 1;
                k = len - 1;
                while (j < k) {
                    sum=nums[i]+nums[j]+nums[k]+nums[l];
                    if (sum > target) {
                        k--;
                    } else if (sum < target) {
                        j++;
                    } else {
                        if (j - 1 > l && nums[j] == nums[j - 1])//避开第一次遇到nums[j]
                        {
                            j++;
                            continue;
                        } else if (k + 1 < len && nums[k] == nums[k + 1])//避开第一次遇到nums[k]
                        {
                            k--;
                            continue;
                        }
                        res.push_back({nums[i], nums[l],nums[j], nums[k]});
                        k--;
                    }
                }
            }
        }
        return res;
    }
};
```

### lc16 最接近的三数之和
``` cpp
class Solution {
public:
    int threeSumClosest(vector<int> &nums, int target) {
        sort(nums.begin(), nums.end());
        int len = nums.size();
        int temp_distance = 0;
        int distance = numeric_limits<int>::max();
        int sum = 0;
        int res_sum = 0;
        for (size_t i = 0; i < len; i++) {
            int j = i + 1;
            int k = len - 1;
            while (j < k) {
                sum = nums[i] + nums[k] + nums[j];
                if (sum == target) return target;
                if (sum > target) {
                    k--;
                } else {
                    j++;
                }

                temp_distance = abs(target - sum);
                if (temp_distance < distance) {
                    distance = temp_distance;
                    res_sum = sum;

                }
            }


        }
        return res_sum;
    }
};                                             
```
这道题一开始考虑得太细，总想着要在temp_distance < distance时停下来，而事实上这样的算法是错的；同时注意numeric_limits<int>::max()的使用。
    
### lc11 盛水最多的容器
``` cpp
class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int length = height.size();
        int i = 0;
        int j = length - 1;
        int tempres = 0;
        int res = 0;
        while (i < j)
        {
            if (height[i] <= height[j])
            {
                tempres = height[i] * (j - i);
                i++;
            }
            else
            {

                tempres = height[j] * (j - i);
                j--;
            }
            res = max(res, tempres);
        }
        return res;
    }
};
```
这道题有点像几数之和的变形，只向这最大的方向变形，同几数之和向着同一个方向变型是一个道理；补短板，也是一个可以借鉴的思路
### lc345 反转字符串中的元音字母
```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int low = 0;
        char temp = 0;
        int high = s.size() - 1;
        while (low < high) {
            if (isYuanYin(s[low]) && isYuanYin(s[high])) {
                temp = s[low];
                s[low] = s[high];
                s[high] = temp;
                low++;
                high--;
            } else if (isYuanYin(s[low]) && !isYuanYin(s[high])) {
                high--;
            } else if (!isYuanYin(s[low]) && isYuanYin(s[high])) {
                low++;
            } else {
                low++;
                high--;
            }
        }
        return s;


    }

    bool isYuanYin(char a) {
        if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u'||a=='A'||a=='E'||a=='I'||a=='O'||a=='U') return true;
        return false;
    }
};
```
像是回文和两数之和类型的变形
## 双串综合型
### lc28 实现strStr()
```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
                int lenstr = haystack.size();
        int leneedle = needle.size();
        int i = 0;
        int j = 0;
        int res = 0;
        if(leneedle==0) return 0;
        while (i < lenstr-leneedle+1) {//用lenstr-leneedle+1而不是lenstr节省了很多时间，1是为了应付lenstr==leneedle的情况
                j = 0;
                while (j < leneedle && needle[j] == haystack[j+i]){
                    j++;
                if(j==leneedle) return i;
            }
            i++;
        }
        return -1;
    }
};
```
此题算法不算特别，除了注释的部分

### lc844 比较含退格的字符串
#### 栈
```cpp
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        stack<char> s;
        int si = 0;
        stack<char> t;
        int ti = 0;
        while(S[si])
        {
            if(S[si] == '#')
            {
                if(!s.empty())
                {
                    s.pop();
                }
            }
            else
            {
                s.push(S[si]);
            }
            ++si;
        }
        while(T[ti])
        {
            if(T[ti] == '#')
            {
                if(!t.empty())
                    t.pop();
            }
            else
                t.push(T[ti]);
            ++ti;
        }
        while(!s.empty() && !t.empty())
        {
            if(s.top() != t.top())
                return false;
            s.pop();
            t.pop();
        }
        if(!s.empty() || !t.empty())
            return false;
        return true;
    }
};
```
#### 采用remove元素的策略(快慢指针）
```cpp
class Solution {
public:
    int remove (string& S){
        int index=0;
        for(auto i:S){
            if(i!='#'){
                S[index++]=i;//注意这里使得每一个index走到下一步的位置是一个可以通用的习惯
            }else{
                index==0?0:--index;
            }
        }
        return index;
    }
    bool backspaceCompare(string S, string T) {
        int findex=remove(S);
        int sindex=remove(T);
        if(findex!=sindex) return false;
        else{
            S=S.substr(0,findex);
            T=T.substr(0,findex);
            if(S.compare(T)==0)return true;
            else return false;
        }
    }
};
```
借鉴了移动类双指针的思路，但难点在于如何队多次退格进行处理
#### 双指针版本
```cpp
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1;
        int j = T.size() - 1;
        int count_i = 0;
        int count_j = 0;
        while (i >= 0 || j >= 0) {
            if (i>=0 && S[i] == '#') {
                i--;
                count_i++;
                continue;
            }
            if (j>=0 && T[j] == '#') {
                j--;
                count_j++;
                continue;
            }
            if (i>=0 && count_i){
                i--;
                count_i--;
                continue;
            }
            if (j>=0 && count_j){
                j--;
                count_j--;
                continue;
            }
            if ( i>=0 && j>=0 && S[i] != T[j]) return false;
            if ((i>=0)!=(j>=0)) return false;
            i--;
            j--;
        }
        return true;
    }

};
```
很琐碎，if continue的多次使用，count_i--的使用；从尾到头式的遍历；或的循环条件（用与的话可能count_j还不为0就结束了）都是难点
### lc925 长按键入
```cpp
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int index = 0;
        int i = 0;
        int name_len = name.size();
        int typed_len = typed.size();
        while(i<name_len || index<typed_len) {
            if(i<typed_len && index<typed_len && name[i]!=typed[index]){
                if(i>0 && typed[index]==name[i-1]) {
                    index++;
                    continue;
                }
                else return false;
            }
            if(i<name_len && index>=typed_len)
                return false;
            //if(i>=name_len && name[name_len-1]!=typed[index])
                //return false;按题意不会出现这种情况,即name结束,typed有剩余的情况
            index++;
            i++;
        }
        return true;
    }
};
```
也使用了或的循环条件，与上题有一定的相似之处
换个思路遍历typed会更快
```cpp
class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int j = 0, len = name.size();
    for(int i = 0; i < typed.size(); i++)
    {
        if(typed[i] == name[j] && j < len)
        {
            j++;
            continue;
        }
        else if(j > 0 && typed[i] == name[j-1]) //首字母不同时j-1超出索引范围
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    if (j == len)
        return true;
    else
        return false;

    }
};
```

