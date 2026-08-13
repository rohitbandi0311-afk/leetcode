class Solution {
    
    // Segment tree node
    class Node {
        int maxLen;      // Max length of a repeating character substring in this segment
        int prefLen;     // Max length of repeating characters at the prefix of this segment
        int suffLen;     // Max length of repeating characters at the suffix of this segment
        char prefChar;   // The prefix character itself
        char suffChar;   // The suffix character itself
        int size;        // Total size of the segment
    }

    Node[] tree;

    public int[] longestRepeating(String s, String queryCharacters, int[] queryIndices) {
        int n = s.length();
        tree = new Node[4 * n];
        char[] chars = s.toCharArray();
        
        // Build the initial segment tree
        build(0, 0, n - 1, chars);

        int k = queryIndices.length;
        int[] ans = new int[k];

        // Process each query
        for (int i = 0; i < k; i++) {
            update(0, 0, n - 1, queryIndices[i], queryCharacters.charAt(i));
            // After each update, the root of the tree contains the overall max length
            ans[i] = tree[0].maxLen;
        }

        return ans;
    }

    private void build(int node, int l, int r, char[] chars) {
        if (l == r) {
            tree[node] = new Node();
            tree[node].maxLen = 1;
            tree[node].prefLen = 1;
            tree[node].suffLen = 1;
            tree[node].prefChar = chars[l];
            tree[node].suffChar = chars[l];
            tree[node].size = 1;
            return;
        }
        
        int mid = l + (r - l) / 2;
        build(2 * node + 1, l, mid, chars);
        build(2 * node + 2, mid + 1, r, chars);
        
        // Merge children to create the parent node
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    private void update(int node, int l, int r, int idx, char c) {
        // Reached the leaf node to be updated
        if (l == r) {
            tree[node].prefChar = c;
            tree[node].suffChar = c;
            return;
        }
        
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(2 * node + 1, l, mid, idx, c);
        } else {
            update(2 * node + 2, mid + 1, r, idx, c);
        }
        
        // Backtrack and update current node by merging its updated children
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    private Node merge(Node left, Node right) {
        Node res = new Node();
        res.size = left.size + right.size;
        res.prefChar = left.prefChar;
        res.suffChar = right.suffChar;

        // Calculate Prefix Length
        res.prefLen = left.prefLen;
        if (left.prefLen == left.size && left.prefChar == right.prefChar) {
            res.prefLen += right.prefLen;
        }

        // Calculate Suffix Length
        res.suffLen = right.suffLen;
        if (right.suffLen == right.size && right.suffChar == left.suffChar) {
            res.suffLen += left.suffLen;
        }

        // Calculate Max Length in the merged segment
        res.maxLen = Math.max(left.maxLen, right.maxLen);
        if (left.suffChar == right.prefChar) {
            res.maxLen = Math.max(res.maxLen, left.suffLen + right.prefLen);
        }

        return res;
    }
}