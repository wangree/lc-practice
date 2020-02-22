### lc424 替换后的最长重复字符
```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        int left=0;
        int right=0;
        int maxcount=0;
        int count[26]={0};
        int res = 0;
        while(right<s.size()){
            count[s[right]-'A']++;
            maxcount=max(maxcount,count[s[right]-'A']);
            if(right-left+1-maxcount>k){
                count[s[left]-'A']--;
                left++;
     
            }
            
            res=max(res,right-left+1);
            right++;  
        }
        return res;
    }
};
```
这是典型的滑窗题目：滑窗一般要求是最长的，而且本题的滑窗只要求出最大的结果，不需要序列本身，所以我们可以整体移动滑窗而不用在左指针移动时重置右指针；此题的特别之处在于maxcount,maxcount是历史上
滑窗内某字母最大出现次数而不是当前滑窗的最大次数，也就是说只有在当前滑窗内的某字母出现次数大于某字母历史最大次数，maxcount才会更新，否则历史
maxcount,能这么做的原因在满足right-left+1-maxcount>k)条件时，left++,此时的right-left+1=k+maxcount,后面新滑窗的位置right-left+1<K+maxcount时
说明这时的res不够大不需要更新，只有maxcount更新时res才会更新。另外要说一点写代码的技巧，不需要再真正更新的时候将条件单列出来更新，这样会很难
写容易出错，只需要随着一次迭代写进去即可，像res=res=max(res,right-left+1),很多时候res并没有更新，而if(right-left+1-maxcount>k)也不必写成while

### lc3 无重复字符的最长子串
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

### lc209 长度最小的子数组
```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int i=0;
        int j=0;
        int len=nums.size();
        if(len==0) return 0;
        int sum=nums[0];
        int res=len+1;
        while(/*i<len && */j<len){
            if(sum<s){
                j++;
                if(j<len)sum+=nums[j];
            }else{
                res=min(res,j-i+1); 
                sum-=nums[i];
                i++;
                /*if(i>j && i<len) {
                    j=i;
                    sum=nums[j];
                }*/没必要，思维误区
            }
        }
        if(res>len) res=0;//改成条件表达式会快很多
        return res;
    }
};
```
类似于滑窗，但是要注意i++,j++之后的越界问题，i追上j之后的问题（这个问题其实并不存在）和res为初始值的问题，这个代码写的并不好。

官方题解：
```cpp
int minSubArrayLen(int s, vector<int>& nums)
{
    int n = nums.size();
    int ans = INT_MAX;
    int left = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        while (sum >= s) {
            ans = min(ans, i + 1 - left);
            sum -= nums[left++];
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}
```
官方解法有几个好处：1.nums[0]被直接加进sum里，不需要给初值，也不需要对nums长度做判断；2不需要i++之后再对i做判断，而我的写法是不能避免的
```cpp
//类似官方题解的方法
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int i=0;
        int j=0;
        int len=nums.size();
        if(len==0) return 0;
        int sum=0;
        int res=len+1;
        /*while(i<len && j<len){
            sum+=nums[j];
            if(sum>=s){
                res=min(res,j-i+1); 
                sum-=nums[i];
                i++;
                continue;
            }
           j++;
        }
        */
        while (i < len) {
        if(sum<s){
            sum += nums[i];
        }
        if(sum>=s) {
            res = min(res, i + 1 - j);
            sum -= nums[j++];
        }
        if(sum<s)
        {
            i++;
        }
    }
        res=res<=len?res: 0;
        return res;
    }
};//需要注意的是每一次对ij的改变即对sum的改变紧接着下一步都应该作以判断。
```
