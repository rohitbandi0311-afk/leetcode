import java.util.*;

class Solution {
    private int[] newParent;
    private int[] lastSeen;
    private List<Integer>[] origAdj;
    private List<Integer>[] newAdj;
    private int[] ans;

    @SuppressWarnings("unchecked")
    public int[] findSubtreeSizes(int[] parent, String s) {
        int n = parent.length;
        newParent = new int[n];
        lastSeen = new int[26];
        Arrays.fill(lastSeen, -1);

        origAdj = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            origAdj[i] = new ArrayList<>();
        }
        for (int i = 1; i < n; i++) {
            origAdj[parent[i]].add(i);
        }

        // Pass 1: Determine new parent for every node
        dfsFindParents(0, parent, s);

        // Build final tree adjacency list
        newAdj = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            newAdj[i] = new ArrayList<>();
        }
        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].add(i);
        }

        // Pass 2: Compute subtree sizes in the final tree
        ans = new int[n];
        dfsSubtreeSize(0);
        return ans;
    }

    private void dfsFindParents(int u, int[] parent, String s) {
        int idx = s.charAt(u) - 'a';
        if (u == 0) {
            newParent[u] = -1;
        } else {
            newParent[u] = (lastSeen[idx] != -1) ? lastSeen[idx] : parent[u];
        }

        int prev = lastSeen[idx];
        lastSeen[idx] = u;

        for (int v : origAdj[u]) {
            dfsFindParents(v, parent, s);
        }

        lastSeen[idx] = prev;
    }

    private int dfsSubtreeSize(int u) {
        int size = 1;
        for (int v : newAdj[u]) {
            size += dfsSubtreeSize(v);
        }
        ans[u] = size;
        return size;
    }
}