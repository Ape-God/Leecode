#include <vector>
#include <string>
#include <unordered_map>
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<string, char> str2ch;
        unordered_map<char, string> ch2str;
        int m = str.length();
        int i = 0;
        for (auto ch : pattern) {
            if (i >= m) {
                return false;
            }
            int j = i;
            while (j < m && str[j] != ' ') j++;
            const string& tmp = str.substr(i, j - i);
            if (str2ch.count(tmp) && str2ch[tmp] != ch) {
                return false;
            }
            if (ch2str.count(ch) && ch2str[ch] != tmp) {
                return false;
            }
            str2ch[tmp] = ch;
            ch2str[ch] = tmp;
            i = j + 1;
        }
        return i >= m;
    }
};


int main() {
    Solution solution;
    string pattern = "abba";
    string str = "dog cat cat dog";

    bool isMatch = solution.wordPattern(pattern, str);
    cout << (isMatch ? "Pattern matches string" : "Pattern does not match string") << endl;

    return 0;
}