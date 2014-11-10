class Solution:
    # @return a tuple, (index1, index2)

    def twoSum(self, num, target):
        ti, tj = None, None
        num_index = [None] * (target + 1)
        for index, elem in enumerate(num):
            if elem > target:
                continue

            if num_index[elem] is not None:
                if elem * 2 == target:
                    ti, tj = num_index[elem], index
            else:
                num_index[elem] = index

        if ti is not None and tj is not None:
            return ti + 1, tj + 1

        for i in xrange(0, target / 2 + 1):
            needNum = target - num[i]
            if needNum == num[i]:
                continue
            if needNum in num_index:
                return i + 1, num_index[needNum] + 1
        return -1, -1


def main():
    num = [3,2,4]
    target = 6
    s = Solution()
    ti, tj = s.twoSum(num, target)
    print 'ti: %s, tj: %s, sum: %s' % (ti, tj, num[ti-1] + num[tj-1])


if __name__ == '__main__':
    main()
# [0,4,3,0], 0
