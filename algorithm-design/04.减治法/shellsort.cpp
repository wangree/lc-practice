#include <vector>
#include <iostream>
using namespace std;
void insert_sort(vector<int>& nums,int gap,int start){
    if(nums.size()<=1) return;
    int j =0;
    int V=0;
    for (int i = start+gap; i <nums.size() ; i+=gap) {
            V=nums[i];
            j = i-gap;
            while (j>=0 && nums[j]>V ){
               nums[j+gap]=nums[j];
               j-=gap;
            }
            nums[j+gap]=V;
        }
    }
int main(){
    vector<int> input={10,3,7,13,99,7,4};
    vector<int> gap={4,1};
    for(auto gapi:gap){
        for (int start = 0; start <gapi ; ++start) {//注意这里的start<gapi,不要整什么余数）
         insert_sort(input,gapi,start);
        }
    }
    return 0;

}
