#include <iostream>
#include <string>
#include <vector>

using namespace std;

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


int main() {
    Solution sol;
    string s = "leetcode";
    string res = sol.reverseVowels(s);
    return 0;
}
