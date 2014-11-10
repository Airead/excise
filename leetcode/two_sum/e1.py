class Solution:
    # @return a tuple, (index1, index2)

    def twoSum(self, num, target):
        ti, tj = None, None
        num_index = {}
        min_val = min(num)
        for index, elem in enumerate(num):
#            print index, elem, num_index
            if elem in num_index:
                if elem * 2 == target:
                    ti, tj = num_index[elem], index
                    break
            else:
                num_index[elem] = index

        if ti is not None and tj is not None:
            ret = [ti+1, tj+1]
            ret.sort()
            return ret

        for i in xrange(min_val, target / 2 + 1):
            if i not in num_index:
                continue

            needNum = target - i
            if needNum == i:
                continue
            if needNum in num_index:
                ret = [num_index[i] + 1, num_index[needNum] + 1]
                ret.sort()
                return ret
        return -1, -1


def main():
    num = [-3,4,3,90]
    target = 0
    s = Solution()
    ti, tj = s.twoSum(num, target)
    print 'ti: %s, tj: %s, sum: %s' % (ti, tj, num[ti-1] + num[tj-1])


if __name__ == '__main__':
    main()
# [0,4,3,0], 0
