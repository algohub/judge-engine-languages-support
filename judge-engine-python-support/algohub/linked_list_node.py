class LinkedListNode:
    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        p = self
        q = other
        while p is not None and q is not None:
            if p.value is None and q.value is None:
                return True
            if p.value is None or q.value is None:
                return False
            if p.value != q.value:
                return False
            p = p.next
            q = q.next
        return p is None and q is None

    def __ne__(self, other):
        return not self.__eq__(other)

    # just for debug
    def __str__(self):
        result = '['
        result += str(self.value) if self.value is not None else 'null'

        cur = self.next
        while cur is not None:
            result += ', '
            result += str(cur.value) if cur.value is not None else 'null'
            cur = cur.next
        result += ']'
        return result

    def __hash__(self):
        hash_code = 1
        p = self
        while p is not None:
            hash_code = 31 * hash_code + (0 if p.value is None else hash(p.value))
            p = p.next
        return hash_code

