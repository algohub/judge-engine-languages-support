from .shared_data import SharedData
from algohub import *


class Deserialization(SharedData):
    def test_primitive(self):
        self.assertTrue(from_json(True, TypeNode.from_json('{"value":"bool"}')))
        self.assertFalse(from_json(False, TypeNode.from_json('{"value":"bool"}')))
        self.assertEqual('a', from_json('a', TypeNode.from_json('{"value":"char"}')))
        self.assertEqual(123, from_json(123, TypeNode.from_json('{"value":"int"}')))
        self.assertEqual(123, from_json(123, TypeNode.from_json('{"value":"long"}')))
        self.assertEqual(123.0, from_json(123.0, TypeNode.from_json('{"value":"double"}')))
        self.assertEqual('algohub', from_json('algohub', TypeNode.from_json('{"value":"string"}')))

    def test_collection(self):
        self.assertEqual(self.array_int, from_json(self.array_int_json, self.array_int_type))
        self.assertEqual(self.list_int, from_json(self.array_int_json, self.list_int_type))
        self.assertEqual(self.linked_list_int, from_json(self.array_int_json, self.linked_list_int_type))
        self.assertEqual(self.set_int, from_json(self.array_int_json, self.set_int_type))
        # empty linked list
        self.assertEqual(None, from_json(self.empty_array_int_json, self.linked_list_int_type))

        self.assertEqual(self.map_string_int, from_json(self.map_string_int_json, self.map_string_int_type))
        self.assertEqual(self.map_int_double, from_json(self.map_int_double_json, self.map_int_double_type))

        self.assertEqual(self.binary_tree, from_json(self.binary_tree_json, self.binary_tree_type))
        # empty binary tree
        self.assertEqual(None, from_json(self.empty_array_int_json, self.binary_tree_type))

        self.assertEqual(self.array_array_int, from_json(self.array_array_int_json, self.array_array_int_type))
        self.assertEqual(self.list_list_int, from_json(self.array_array_int_json, self.list_list_int_type))
        self.assertEqual(self.linked_list_linked_list_int,
                         from_json(self.array_array_int_json, self.linked_list_linked_list_int_type))
        self.assertEqual(self.array_linked_list_int,
                         from_json(self.array_array_int_json, self.array_linked_list_int_type))

        self.assertEqual(self.map_string_linked_list_int,
                         from_json(self.map_string_linked_list_int_json, self.map_string_linked_list_int_type))
