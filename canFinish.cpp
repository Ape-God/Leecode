#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    // 判断是否可能完成所有课程
    bool canFinish(int numCourses, const vector<vector<int>>& prerequisites) {
        // 初始化图中每个节点的入度为0
        vector<int> indegrees(numCourses, 0);
        // 初始化图的邻接表
        vector<vector<int>> graph(numCourses);

        // 构建图并计算每个节点的入度
        for (const auto& pre : prerequisites) {
            graph[pre[0]].push_back(pre[1]);
            indegrees[pre[1]]++;
        }

        // 使用队列进行拓扑排序
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) {
                q.push(i);
            }
        }

        // 计数器，记录完成的课程数量
        int count = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            ++count;
            // 遍历当前课程的所有先修课程
            for (int pre : graph[course]) {
                if (--indegrees[pre] == 0) {
                    q.push(pre);
                }
            }
        }

        // 如果完成的课程数量等于总课程数量，则可以完成所有课程
        return count == numCourses;
    }
};

// 示例调用
int main() {
    Solution solution;
    // 示例1
    vector<vector<int>> prerequisites1 = { {1, 0} };
    bool result1 = solution.canFinish(2, prerequisites1);
    cout << "Example 1 can finish: " << (result1 ? "true" : "false") << endl;

    // 示例2
    vector<vector<int>> prerequisites2 = { {1, 0}, {0, 1} };
    bool result2 = solution.canFinish(2, prerequisites2);
    cout << "Example 2 can finish: " << (result2 ? "true" : "false") << endl;

    return 0;
}