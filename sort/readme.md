### lc56 [合并区间](https://leetcode-cn.com/problems/merge-intervals/submissions/)
```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        
        int len = intervals.size();
        if(len<2) return intervals;
        sort(intervals.begin(),intervals.end(),comp);
        vector<int> temp_res=intervals[0];
        vector<int> temp;
         vector<vector<int>> res;
        for(int i=1;i<len;i++){
            temp=intervals[i];
            if(temp_res[1]<temp[0]/*|| temp[1]<temp_res[0]*/){
                res.push_back(temp_res);
                temp_res=temp;
            }
            else {
                temp_res={/*min(temp_res[0],*/temp[0]/*)*/,max(temp_res[1],temp[1])};
            }

        }
        /*if(!temp_res.empty())*/ res.push_back(temp_res);
        return res;
    }
    static bool comp(vector<int>& a,vector<int>& b){
        //if(a.at(0)==b.at(0)) return a.at(1)<b.at(1); 
        return a.at(0)<b.at(0);
    }
};
```
注意优化的地方
