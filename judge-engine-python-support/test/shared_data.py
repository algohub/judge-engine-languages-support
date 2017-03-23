import unittest
from algohub import LinkedListNode, BinaryTreeNode, TypeNode


class SharedData(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.array_int_json = [1, 2, 3, 4, 5]
        cls.array_int = [1, 2, 3, 4, 5]
        cls.list_int = cls.array_int
        cls.set_int = set(cls.array_int)
        cls.linked_list_int = LinkedListNode(1, LinkedListNode(2, LinkedListNode(
            3, LinkedListNode(4, LinkedListNode(5)))))

        cls.map_string_int = {'hello': 1, 'world': 2}
        cls.map_string_int_json = {'"hello"': 1, '"world"': 2}

        cls.map_int_double = {1: 1.0, 2: 2.0}
        cls.map_int_double_json = {'1': 1.0, '2': 2.0}

        cls.binary_tree = BinaryTreeNode(2, BinaryTreeNode(1), BinaryTreeNode(10))
        cls.binary_tree.left.left_is_null = True
        cls.binary_tree.left.right_is_null = True
        cls.binary_tree.right.left = BinaryTreeNode(5)
        cls.binary_tree_json = [2, 1, 10, None, None, 5]

        cls.array_int_json2 = [6, 7, 8, 9, 10]
        cls.array_int2 = [6, 7, 8, 9, 10]
        cls.list_int2 = cls.array_int2
        cls.linked_list_int2 = LinkedListNode(6, LinkedListNode(7, LinkedListNode(
            8, LinkedListNode(9, LinkedListNode(10)))))

        cls.array_array_int_json = [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]
        cls.array_array_int = [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]
        cls.list_list_int = cls.array_array_int
        cls.linked_list_linked_list_int = LinkedListNode(cls.linked_list_int, LinkedListNode(cls.linked_list_int2))
        cls.array_linked_list_int = [cls.linked_list_int, cls.linked_list_int2]
        cls.set_linked_list_int = set(cls.array_linked_list_int)

        cls.map_string_linked_list_int = {'hello': cls.linked_list_int, 'world': cls.linked_list_int2}
        cls.map_string_linked_list_int_json = {'"hello"': cls.array_int_json, '"world"': cls.array_int_json2}

        cls.empty_array_int_json = []  # for empty linked list and empty binary tree

        # type nodes
        cls.array_int_type = TypeNode.from_json('{"value":"array", "element_type": {"value":"int"}}')
        cls.list_int_type = TypeNode.from_json('{"value":"list", "element_type": {"value":"int"}}')
        cls.set_int_type = TypeNode.from_json('{"value":"set", "element_type": {"value":"int"}}')
        cls.linked_list_int_type = TypeNode.from_json('{"value":"LinkedListNode", "element_type": {"value":"int"}}')
        cls.map_string_int_type =  TypeNode.from_json(
            '{"value":"map", "key_type": {"value":"string"}, "element_type": {"value":"int"}}')
        cls.map_int_double_type = TypeNode.from_json(
            '{"value":"map", "key_type": {"value":"int"}, "element_type": {"value":"double"}}')
        cls.binary_tree_type = TypeNode.from_json('{"value":"BinaryTreeNode", "element_type": {"value":"int"}}')
        cls.array_array_int_type = TypeNode.from_json(
                '{"value":"array", "element_type": {"value":"array", "element_type": {"value":"int"}}}')
        cls.list_list_int_type = TypeNode.from_json(
            '{"value":"list", "element_type": {"value":"list", "element_type": {"value":"int"}}}')
        cls.linked_list_linked_list_int_type = TypeNode.from_json(
            '{"value":"LinkedListNode", "element_type": {"value":"LinkedListNode", "element_type": {"value":"int"}}}')
        cls.array_linked_list_int_type = TypeNode.from_json(
            '{"value":"array", "element_type": {"value":"LinkedListNode", "element_type": {"value":"int"}}}')
        cls.map_string_linked_list_int_type = TypeNode.from_json(
                '{"value":"map", "key_type": {"value":"string"}, "element_type": {"value":"LinkedListNode"}}')
