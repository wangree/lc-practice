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
