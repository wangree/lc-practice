# 双指针
对于双指针，大循环while里有两种循环，一种用if continue,这可以只需要给出移动一步的条件再continue即可，而另外一种需要while滑到头的，需要在这层while里加上
外层while的循环条件
对比lc-345.cpp与lc-345compare.cpp，可以看看其他人是怎么写的，应该有所借鉴
### lc977 有序数组的平方
双指针的话，类似于两个有序数组的拼接算法，该算法比较两个数组某位置上的数字大小，小的压入结果数组，并移动指针，大的指针不挪动，再进行比较，如此循环直到其中一个数组指针遍历结束，再把未结束的末尾部分放进结果数组中去；这里的区别主要是这个例子需要找出第一个大于0的位置把正负数分成两个数组。
体会到双指针的核心就是怎么挪指针。
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
### lc532
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
### lc844
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
                //return false;按题意不会出现这种情况
            index++;
            i++;
        }
        return true;
    }
};
```
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
