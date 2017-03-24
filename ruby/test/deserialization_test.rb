require 'test/unit'
require_relative '../algohub'
require_relative './shared_data'


class DeserializationTest < SharedData
  def test_primitive
    assert_equal(true, Algohub::from_json(true, TypeNode.from_json('{"value":"bool"}')))
    assert_equal(false, Algohub::from_json(false, TypeNode.from_json('{"value":"bool"}')))
    assert_equal('a', Algohub::from_json('a', TypeNode.from_json('{"value":"char"}')))
    assert_equal(123, Algohub::from_json(123, TypeNode.from_json('{"value":"int"}')))
    assert_equal(123, Algohub::from_json(123, TypeNode.from_json('{"value":"long"}')))
    assert_equal(123.0, Algohub::from_json(123.0, TypeNode.from_json('{"value":"double"}')))
    assert_equal('algohub', Algohub::from_json('algohub', TypeNode.from_json('{"value":"string"}')))
  end

  def test_collection
    assert_equal(@array_int, Algohub::from_json(@array_int_json, @array_int_type))
    assert_equal(@list_int, Algohub::from_json(@array_int_json, @list_int_type))
    assert_equal(@linked_list_int, Algohub::from_json(@array_int_json, @linked_list_int_type))
    assert_equal(@set_int, Algohub::from_json(@array_int_json, @set_int_type))
    # empty linked list
    assert_equal(nil, Algohub::from_json(@empty_array_int_json, @linked_list_int_type))

    assert_equal(@map_string_int, Algohub::from_json(@map_string_int_json, @map_string_int_type))
    assert_equal(@map_int_double, Algohub::from_json(@map_int_double_json, @map_int_double_type))

    assert_equal(@binary_tree, Algohub::from_json(@binary_tree_json, @binary_tree_type))
    # empty binary tree
    assert_equal(nil, Algohub::from_json(@empty_array_int_json, @binary_tree_type))

    assert_equal(@array_array_int, Algohub::from_json(@array_array_int_json, @array_array_int_type))
    assert_equal(@list_list_int, Algohub::from_json(@array_array_int_json, @list_list_int_type))
    assert_equal(@linked_list_linked_list_int,
                     Algohub::from_json(@array_array_int_json, @linked_list_linked_list_int_type))
    assert_equal(@array_linked_list_int,
                     Algohub::from_json(@array_array_int_json, @array_linked_list_int_type))

    assert_equal(@map_string_linked_list_int,
                     Algohub::from_json(@map_string_linked_list_int_json, @map_string_linked_list_int_type))
  end
end
