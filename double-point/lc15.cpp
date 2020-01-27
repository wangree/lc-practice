#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> temp;
        int len = nums.size();
        int j =0;
        int k=0;
        for (size_t i = 0; i < len; i++)
        {
            j=i+1;
            k=len-1;
            if(nums[i]>0) continue;
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
                
                    if (j-1>i && nums[j]==nums[j-1])//避开第一次遇到nums[j]
                    {
                        j++;
                        continue;
                    }else if(k+1<len && nums[k]==nums[k+1] )//避开第一次遇到nums[k]
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

int main(){
    Solution sol;
    vector<int> input={-1,-1,0,0,0,0,1,1};
    vector<vector<int>> res=sol.threeSum(input);
    for (auto v: res)
    {
        for (auto vv: v)
        {
            cout<<vv<<" ";
        }
        cout<<endl;
    }
    system("pause");
}