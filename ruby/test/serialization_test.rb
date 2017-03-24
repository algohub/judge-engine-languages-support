require 'test/unit'
require_relative '../algohub'
require_relative './shared_data'


class SerializationTest < SharedData
  def test_primitive
    assert_equal(true, Algohub::to_json(true, TypeNode.from_json('{"value":"bool"}')))
    assert_equal(false, Algohub::to_json(false, TypeNode.from_json('{"value":"bool"}')))
    assert_equal('a', Algohub::to_json('a', TypeNode.from_json('{"value":"char"}')))
    assert_equal(123, Algohub::to_json(123, TypeNode.from_json('{"value":"int"}')))
    assert_equal(123, Algohub::to_json(123, TypeNode.from_json('{"value":"long"}')))
    assert_equal(123.0, Algohub::to_json(123.0, TypeNode.from_json('{"value":"double"}')))
    assert_equal('algohub', Algohub::to_json('algohub', TypeNode.from_json('{"value":"string"}')))
  end

  def test_collection
    assert_equal(@array_int_json, Algohub::to_json(@array_int, @array_int_type))
    assert_equal(@array_int_json, Algohub::to_json(@list_int, @list_int_type))
    assert_equal(@array_int_json, Algohub::to_json(@set_int, @set_int_type))
    assert_equal(@array_int_json, Algohub::to_json(@linked_list_int, @linked_list_int_type))
    # empty linked list
    assert_equal(@empty_array_int_json,Algohub::to_json(nil, @linked_list_int_type))

    assert_equal(@map_string_int_json, Algohub::to_json(@map_string_int, @map_string_int_type))
    assert_equal(@map_int_double_json, Algohub::to_json(@map_int_double, @map_int_double_type))

    # empty binary tree
    assert_equal(@empty_array_int_json, Algohub::to_json(nil, @binary_tree_type))
    assert_equal(@binary_tree_json, Algohub::to_json(@binary_tree, @binary_tree_type))

    assert_equal(@array_array_int_json, Algohub::to_json(@array_array_int, @array_array_int_type))
    assert_equal(@array_array_int_json, Algohub::to_json(@list_list_int, @list_list_int_type))
    assert_equal(@array_array_int_json,
                     Algohub::to_json(@linked_list_linked_list_int, @linked_list_linked_list_int_type))
    assert_equal(@array_array_int_json, Algohub::to_json(@array_linked_list_int, @array_linked_list_int_type))

    assert_equal(@map_string_linked_list_int_json,
                     Algohub::to_json(@map_string_linked_list_int, @map_string_linked_list_int_type))
  end
end
