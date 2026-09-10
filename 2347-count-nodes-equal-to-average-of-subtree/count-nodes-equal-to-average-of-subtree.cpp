/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int count = 0;

    // Helper function returns a pair: {sum_of_subtree, count_of_nodes}
    pair<int, int> postOrder(TreeNode* root) {
        if (!root) return {0, 0};

        auto left = postOrder(root->left);
        auto right = postOrder(root->right);

        int currentSum = root->val + left.first + right.first;
        int currentCount = 1 + left.second + right.second;

        // Check if the node's value equals the average of its subtree
        if (currentSum / currentCount == root->val) {
            count++;
        }

        return {currentSum, currentCount};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        postOrder(root);
        return count;
    }
};