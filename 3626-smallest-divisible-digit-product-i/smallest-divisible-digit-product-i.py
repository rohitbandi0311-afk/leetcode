class Solution(object):
    def smallestNumber(self, n, t):
        """:type n: int
        :type t: int
        :rtype: int
        """
        x = n
        while True:
            # Calculate product of digits
            product = 1
            temp = x
            while temp > 0:
                product *= temp % 10
                temp //= 10
            
            # Check if the product is divisible by t
            if product % t == 0:
                return x
            
            x += 1
            