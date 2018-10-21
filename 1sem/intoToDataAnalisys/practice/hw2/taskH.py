class Node:
    left = None
    right = None
    parent = None
    value: int = None

    def __init__(self, val, parent):
        self.value = val
        self.parent = parent

    def next(self, val: int):
        if val > self.value:
            return self.right
        else:
            if val != self.value:
                return self.left
            else:
                return self

    def append_child(self, val: int):
        if val > self.value:
            self.right = Node(val, self)
        else:
            if val != self.value:
                self.left = Node(val, self)

    def __contains__(self, value: int):
        if value == self.value:
            return True
        else:
            if self.right is not None and self.right.__contains__(value):
                return True
            if self.left is not None and self.left.__contains__(value):
                return True
            return False


class TreeIterator:
    cur_node: Node = None
    left: bool = False
    right: bool = False

    def __init__(self, node: Node):
        self.cur_node = node


class BinarySearchTree:
    root: Node = None

    def __init__(self, root_value=None):
        if root_value is not None:
            self.append(root_value)

    def __contains__(self, value: int):
        if self.root is None:
            return False
        return self.root.__contains__(value)

    def __iter__(self):
        if self.root is None:
            self.__iterators__ = []
        else:
            self.__iterators__ = [self.root]
        return self

    def __next__(self):
        if len(self.__iterators__) == 0:
            raise StopIteration
        node = self.__iterators__[0]
        if node.left is not None:
            self.__iterators__.append(node.left)
        if node.right is not None:
            self.__iterators__.append(node.right)
        del self.__iterators__[0]
        return node.value

    def append(self, value: int):
        if self.root is None:
            self.root = Node(value, None)
        else:
            cur = self.root
            while True:
                next_el = cur.next(value)
                if next_el is None or next_el == cur:
                    break
                cur = next_el
            if cur != next_el:
                cur.append_child(value)
        return self


if __name__ == '__main__':
    tree = BinarySearchTree()
    for v in [8]:
        tree.append(v)

    for v in [8, 12, 13]:
        print(v in tree)

    print(*tree)
