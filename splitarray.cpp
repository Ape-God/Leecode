#include <vector>
#include <algorithm>
#include<iostream>
#include <numeric> 

using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<long long>> f(n + 1, vector<long long>(m + 1, LLONG_MAX));
        vector<long long> sub(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sub[i + 1] = sub[i] + nums[i];
        }
        f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, m); j++) {
                for (int k = 0; k < i; k++) {
                    f[i][j] = min(f[i][j], max(f[k][j - 1], sub[i] - sub[k]));
                }
            }
        }
        return (int)f[n][m];
    }
};



//class Solution {
//public:
//    bool check(vector<int>& nums, int x, int m) {
//        long long sum = 0;
//        int cnt = 1;
//        for (int i = 0; i < nums.size(); i++) {
//            if (sum + nums[i] > x) {
//                cnt++;
//                sum = nums[i];
//            }
//            else {
//                sum += nums[i];
//            }
//        }
//        return cnt <= m;
//    }
//
//    int splitArray(vector<int>& nums, int m) {
//        long long left = 0, right = 0;
//        for (int i = 0; i < nums.size(); i++) {
//            right += nums[i];
//            if (left < nums[i]) {
//                left = nums[i];
//            }
//        }
//        while (left < right) {
//            long long mid = (left + right) >> 1;
//            if (check(nums, mid, m)) {
//                right = mid;
//            }
//            else {
//                left = mid + 1;
//            }
//        }
//        return left;
//    }
//};




// 主函数，用于测试
int main() {
    Solution solution;
    vector<int> nums = { 7, 2, 5, 10, 8 };
    int k = 2;
    cout << "The minimum maximum sum is: " << solution.splitArray(nums, k) << endl; // 应输出 18

    return 0;
}