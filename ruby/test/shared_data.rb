require 'test/unit'
require 'set'
require_relative '../algohub'


TypeNode = Algohub::TypeNode
LinkedListNode = Algohub::LinkedListNode
BinaryTreeNode = Algohub::BinaryTreeNode


class SharedData < Test::Unit::TestCase
  def setup
    @array_int_json = [1, 2, 3, 4, 5]
    @array_int = [1, 2, 3, 4, 5]
    @list_int = @array_int
    @set_int = Set.new(@array_int)
    @linked_list_int = LinkedListNode.new(1, LinkedListNode.new(2, LinkedListNode.new(
        3, LinkedListNode.new(4, LinkedListNode.new(5)))))

    @map_string_int = {'hello' => 1, 'world' => 2}
    @map_string_int_json = {'"hello"'=> 1, '"world"'=> 2}

    @map_int_double = {1 => 1.0, 2 => 2.0}
    @map_int_double_json = {'1' => 1.0, '2' => 2.0}

    @binary_tree = BinaryTreeNode.new(2, BinaryTreeNode.new(1), BinaryTreeNode.new(10))
    @binary_tree.left.left_is_null = true
    @binary_tree.left.right_is_null = true
    @binary_tree.right.left = BinaryTreeNode.new(5)
    @binary_tree_json = [2, 1, 10, nil, nil, 5]

    @array_int_json2 = [6, 7, 8, 9, 10]
    @array_int2 = [6, 7, 8, 9, 10]
    @list_int2 = @array_int2
    @linked_list_int2 = LinkedListNode.new(6, LinkedListNode.new(7, LinkedListNode.new(
        8, LinkedListNode.new(9, LinkedListNode.new(10)))))

    @array_array_int_json = [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]
    @array_array_int = [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10]]
    @list_list_int = @array_array_int
    @linked_list_linked_list_int = LinkedListNode.new(@linked_list_int, LinkedListNode.new(@linked_list_int2))
    @array_linked_list_int = [@linked_list_int, @linked_list_int2]
    @set_linked_list_int = Set.new(@array_linked_list_int)

    @map_string_linked_list_int = {'hello' => @linked_list_int, 'world'=> @linked_list_int2}
    @map_string_linked_list_int_json = {'"hello"' => @array_int_json, '"world"'=> @array_int_json2}

    @empty_array_int_json = []  # for empty linked list and empty binary tree

    # type nodes
    @array_int_type = TypeNode.from_json('{"value":"array", "element_type": {"value":"int"}}')
    @list_int_type = TypeNode.from_json('{"value":"list", "element_type": {"value":"int"}}')
    @set_int_type = TypeNode.from_json('{"value":"set", "element_type": {"value":"int"}}')
    @linked_list_int_type = TypeNode.from_json('{"value":"LinkedListNode", "element_type": {"value":"int"}}')
    @map_string_int_type =  TypeNode.from_json(
        '{"value":"map", "key_type": {"value":"string"}, "element_type": {"value":"int"}}')
    @map_int_double_type = TypeNode.from_json(
        '{"value":"map", "key_type": {"value":"int"}, "element_type": {"value":"double"}}')
    @binary_tree_type = TypeNode.from_json('{"value":"BinaryTreeNode", "element_type": {"value":"int"}}')
    @array_array_int_type = TypeNode.from_json(
        '{"value":"array", "element_type": {"value":"array", "element_type": {"value":"int"}}}')
    @list_list_int_type = TypeNode.from_json(
        '{"value":"list", "element_type": {"value":"list", "element_type": {"value":"int"}}}')
    @linked_list_linked_list_int_type = TypeNode.from_json(
        '{"value":"LinkedListNode", "element_type": {"value":"LinkedListNode", "element_type": {"value":"int"}}}')
    @array_linked_list_int_type = TypeNode.from_json(
        '{"value":"array", "element_type": {"value":"LinkedListNode", "element_type": {"value":"int"}}}')
    @map_string_linked_list_int_type = TypeNode.from_json(
        '{"value":"map", "key_type": {"value":"string"}, "element_type": {"value":"LinkedListNode"}}')
  end
end
