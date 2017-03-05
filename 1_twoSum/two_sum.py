class Solution(object):
    def  twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        sorted_nums = sorted(nums)
        f, l = 0, len(sorted_nums) - 1

        while f < l:
            t_sum = sorted_nums[f] + sorted_nums[l]
            if t_sum == target:
                a, b = sorted_nums[f], sorted_nums[l]
                print a, b
                ix_a = nums.index(a)
                ix_b = nums.index(b) if a != b else nums.index(b, ix_a + 1)
                return [ix_a, ix_b]

            elif t_sum < target:
                f += 1
            elif t_sum > target:
                l -= 1

        return []


class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        nums_map = {x:(x,i) for i,x in enumerate(nums)}
        for i, num in enumerate(nums):
            y = nums_map.get(target - num)
            if y:
                return [i, y[1]]

        return []
