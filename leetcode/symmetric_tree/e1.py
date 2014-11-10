# Definition for a  binary tree node
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    # @param root, a tree node
    # @return a boolean

    def isSymmetric(self, root):
        if root is None:
            return True
        return self.isSubSymmetric(root.left, root.right)

    def isSubSymmetric(self, p, q):
        if p is None or q is None:
            return p == q

        if p.val != q.val:
            return False

        if not self.isSubSymmetric(p.left, q.right):
            return False

        if not self.isSubSymmetric(p.right, q.left):
            return False

        return True
