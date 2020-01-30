# 双指针
对于双指针，大循环while里有两种循环，一种用if continue,这可以只需要给出移动一步的条件再continue即可，而另外一种需要while滑到头的，需要在这层while里加上
外层while的循环条件
对比lc-345.cpp与lc-345compare.cpp，可以看看其他人是怎么写的，应该有所借鉴
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
                S[index++]=i;
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
