class Solution(object):
    def isMatch(self, s, p):
        """
        :type s:str
        :type p:str
        :rtype :bool
        """
        idx_s, idx_p = 0, 0
        for char_s in s:
            if idx_p < len(p):
                char_p = p[idx_p]
                if char_p == '?':
                    pass
                elif char_p == '*':
                    for t_p in p[idx_p:]:
                        if t_p != '*':
                            break
                        idx_p += 1
                    for i in xrange(0, len(s) - idx_s + 1):
                        if self.isMatch(s[idx_s+i:], p[idx_p:]):
                            return True
                    return False
                else:
                    if char_p != char_s:
                        return False
            else:
                return False

            idx_s += 1
            idx_p += 1

        if p[idx_p:] != '':
            for char in p[idx_p:]:
                if char != '*':
                    return False
            return True
        return True
