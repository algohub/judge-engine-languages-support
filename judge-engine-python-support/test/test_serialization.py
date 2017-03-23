from .shared_data import SharedData
from algohub import to_json, TypeNode


class Serialization(SharedData):

    def test_primitive(self):
        self.assertTrue(to_json(True, TypeNode.from_json('{"value":"bool"}')))
        self.assertFalse(to_json(False, TypeNode.from_json('{"value":"bool"}')))
        self.assertEqual('a', to_json('a', TypeNode.from_json('{"value":"char"}')))
        self.assertEqual(123, to_json(123, TypeNode.from_json('{"value":"int"}')))
        self.assertEqual(123, to_json(123, TypeNode.from_json('{"value":"long"}')))
        self.assertEqual(123.0, to_json(123.0, TypeNode.from_json('{"value":"double"}')))
        self.assertEqual("algohub", to_json("algohub", TypeNode.from_json('{"value":"string"}')))

    def test_collection(self):
        self.assertEqual(self.array_int_json, to_json(self.array_int, self.array_int_type))
        self.assertEqual(self.array_int_json, to_json(self.list_int, self.list_int_type))
        self.assertEqual(self.array_int_json, to_json(self.set_int, self.set_int_type))
        self.assertEqual(self.array_int_json, to_json(self.linked_list_int, self.linked_list_int_type))
        # empty linked list
        self.assertEqual(self.empty_array_int_json,to_json(None, self.linked_list_int_type))

        self.assertEqual(self.map_string_int_json, to_json(self.map_string_int, self.map_string_int_type))
        self.assertEqual(self.map_int_double_json, to_json(self.map_int_double, self.map_int_double_type))

        # empty binary tree
        self.assertEqual(self.empty_array_int_json, to_json(None, self.binary_tree_type))
        self.assertEqual(self.binary_tree_json, to_json(self.binary_tree, self.binary_tree_type))

        self.assertEqual(self.array_array_int_json, to_json(self.array_array_int, self.array_array_int_type))
        self.assertEqual(self.array_array_int_json, to_json(self.list_list_int, self.list_list_int_type))
        self.assertEqual(self.array_array_int_json,
                         to_json(self.linked_list_linked_list_int, self.linked_list_linked_list_int_type))
        self.assertEqual(self.array_array_int_json, to_json(self.array_linked_list_int, self.array_linked_list_int_type))

        self.assertEqual(self.map_string_linked_list_int_json,
                         to_json(self.map_string_linked_list_int, self.map_string_linked_list_int_type))
