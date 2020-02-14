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

### lc 二维数组中的查找
```cpp
class Solution {
 public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int leni=matrix[0].size();
        int i=leni-1;
        int lenj = matrix.size();
        int j=0;
        
        while(i>=0 && j<lenj)
            {
                if(matrix[j][i]==target) return true;
                if(matrix[j][i]>target) {
                    i--;
                }else{
                    j++;
                    }
            }
        return false;
    }
};
```
这是对和差双指针的借鉴   
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

## 荷兰国旗算法
```cpp
class Solution {
 public:
    void sortColors(vector<int>& nums) {
         int p0=0;
         int p2=nums.size()-1;
         int curr=0;
         int temp=0;
         while (curr<=p2){
             if(nums[curr]==2){
                 nums[curr]=nums[p2];
                 nums[p2]=2;
                 p2--;
             } else if(nums[curr]==0){
                 if(nums[p0]==1){
                 nums[curr]=nums[p0];//p0位置上只会是0或者1，2都会被换走,可能都不是，所以这个if条件可有可无
                 nums[p0]=0;}
                 p0++;
                 curr++;
                 
                 
             }else {
                 curr++;
             }
         }
    }
};
```
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

