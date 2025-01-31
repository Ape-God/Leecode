#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> vis(26), num(26);
        for (char ch : s) {
            num[ch - 'a']++;
        }

        string stk;
        for (char ch : s) {
            if (!vis[ch - 'a']) {
                while (!stk.empty() && stk.back() > ch) {
                    if (num[stk.back() - 'a'] > 0) {
                        vis[stk.back() - 'a'] = 0;
                        stk.pop_back();
                    }
                    else {
                        break;
                    }
                }
                vis[ch - 'a'] = 1;
                stk.push_back(ch);
            }
            num[ch - 'a'] -= 1;
        }
        return stk;
    }
};



int main() {
    string s = "bcabc";
    Solution solution;
    string result = solution.removeDuplicateLetters(s);
    cout << "The string after removing duplicate letters is: " << result << endl;
    return 0;
}