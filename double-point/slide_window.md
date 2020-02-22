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
这是典型的滑窗题目：滑窗一般要求是最长的，所以我们可以整体移动滑窗而不用在左指针移动时重置右指针；此题的特别之处在于maxcount,maxcount是历史上
滑窗内某字母最大出现次数而不是当前滑窗的最大次数，也就是说只有在当前滑窗内的某字母出现次数大于某字母历史最大次数，maxcount才会更新，否则历史
maxcount,能这么做的原因在满足right-left+1-maxcount>k)条件时，left++,此时的right-left+1=k+maxcount,后面新滑窗的位置right-left+1<K+maxcount时
说明这时的res不够大不需要更新，只有maxcount更新时res才会更新。另外要说一点写代码的技巧，不需要再真正更新的时候将条件单列出来更新，这样会很难
写容易出错，只需要随着一次迭代写进去即可，像res=res=max(res,right-left+1),很多时候res并没有更新，而if(right-left+1-maxcount>k)也不必写成while
