class Solution(object):
    def remainingMethods(self, n, k, invocations):
        """
        :type n: int
        :type k: int
        :type invocations: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        # Build adjacency list
        adj = defaultdict(list)
        for u, v in invocations:
            adj[u].append(v)

        # Step 1: Find all suspicious methods reachable from method k (directly or indirectly)
        suspicious = set()
        queue = deque([k])
        suspicious.add(k)

        while queue:
            curr = queue.popleft()
            for neighbor in adj[curr]:
                if neighbor not in suspicious:
                    suspicious.add(neighbor)
                    queue.append(neighbor)

        # Step 2: Check if any method outside the suspicious set invokes any method inside the suspicious set
        is_isolated = True
        for u, v in invocations:
            if u not in suspicious and v in suspicious:
                is_isolated = False
                break

        # Step 3: If isolated, remove all suspicious methods; otherwise, keep all methods
        if is_isolated:
            return [i for i in range(n) if i not in suspicious]
        else:
            return list(range(n))