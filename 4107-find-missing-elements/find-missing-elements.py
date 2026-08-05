class Solution(object):
    def findMissingElements(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        ll=min(nums)
        ul=max(nums)
        rl=[]
        for i in range(ll,ul):
            if i not in nums:
                rl.append(i)
        return rl
    
#*the complexity of this code is O(n^2) so it takes longer to run
'''alternate solution with O(n) complexity is as follows:
class Solution(object):
    def findDisappearedNumbers(self, nums):

        for num in nums:
            index = abs(num) - 1
            nums[index] = -abs(nums[index])

        ans = []

        for i in range(len(nums)):
            if nums[i] > 0:
                ans.append(i + 1)

        return ans'''
#! set lookup is FASTER than list lookup thus, use set for repeated membership tests

#TODO:give input through code as nothing actually calls the function
obj = Solution()
result = obj.findMissingElements([1, 2, 4, 6, 7])
print(result)