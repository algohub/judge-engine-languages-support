require 'json'
require 'set'


module Algohub
  module IntermediateType
    BOOL = 'bool'.freeze
    CHAR = 'char'.freeze
    STRING = 'string'.freeze
    DOUBLE = 'double'.freeze
    INT = 'int'.freeze
    LONG = 'long'.freeze
    ARRAY = 'array'.freeze
    LIST = 'list'.freeze
    SET = 'set'.freeze
    MAP = 'map'.freeze
    LINKED_LIST_NODE = 'LinkedListNode'.freeze
    BINARY_TREE_NODE = 'BinaryTreeNode'.freeze
  end

  module StatusCode
    ACCEPTED = 4
    WRONG_ANSWER = 5
    RUNTIME_ERROR = 6
    TIME_LIMIT_EXCEEDED = 7
    MEMORY_LIMIT_EXCEEDED = 8
    OUTPUT_LIMIT_EXCEEDED = 9
    RESTRICTED_CALL = 10
  end


  class TypeNode
    attr_reader :value
    attr_reader :element_type
    attr_reader :key_type

    def initialize(value, element_type = nil, key_type = nil)
      @value = value
      @element_type = element_type
      @key_type = key_type
    end

    def self.to_json(type_node)
      json_str = '{"value":"' + type_node.value.to_s + '"'
      json_str += ',"element_type":' + TypeNode.to_json(type_node.element_type) unless type_node.element_type.nil?
      json_str += ',"key_type":' + TypeNode.to_json(type_node.key_type) unless type_node.key_type.nil?
      json_str + '}'
    end

    def self.from_json(json_str)
      obj = JSON.load(json_str)
      TypeNode.from_json_internal(obj)
    end

    def self.from_json_internal(obj)
      element_type = obj['element_type'].nil? ? nil : TypeNode.from_json_internal(obj['element_type'])
      key_type = obj['key_type'].nil? ? nil : TypeNode.from_json_internal(obj['key_type'])
      TypeNode.new(obj['value'], element_type, key_type)
    end

    def self.has_customized_type(type_node)
      cur = type_node
      until cur.nil?
        if cur.value == IntermediateType::LINKED_LIST_NODE ||
           cur.value == IntermediateType::BINARY_TREE_NODE ||
           cur.value == IntermediateType::SET ||
           cur.value == IntermediateType::MAP
          return true
        end
        cur = cur.element_type
      end
      cur = type_node
      until cur.nil?
        if cur.value == IntermediateType::LINKED_LIST_NODE ||
           cur.value == IntermediateType::BINARY_TREE_NODE ||
           cur.value == IntermediateType::SET ||
           cur.value == IntermediateType::MAP
          return true
        end
        cur = cur.key_type
      end
      false
    end
  end

  class JudgeResult
    attr_accessor :status_code
    attr_accessor :error_message
    attr_accessor :input
    attr_accessor :output
    attr_accessor :expected_output
    attr_accessor :testcase_passed_count
    attr_accessor :testcase_total_count
    attr_accessor :elapsed_time
    attr_accessor :consumed_memory

    def initialize(status_code, error_message=nil, input=nil,
                   output=nil, expected_output=nil, testcase_passed_count=0,
                   testcase_total_count=0, elapsed_time=0, consumed_memory=0)
      @status_code = status_code
      @error_message = error_message
      @input = input
      @output = output
      @expected_output = expected_output
      @testcase_passed_count = testcase_passed_count
      @testcase_total_count = testcase_total_count
      @elapsed_time = elapsed_time
      @consumed_memory = consumed_memory
    end

    def to_s
      result = { 'status_code' => @status_code }
      result['@error_message'] = @error_message unless @error_message.nil?
      result['input'] = @input unless @input.nil?
      result['output'] = @output unless @output.nil?
      result['expected_output'] = @expected_output unless @expected_output.nil?
      result['testcase_passed_count'] = @testcase_passed_count if @testcase_passed_count > 0
      result['testcase_total_count'] = @testcase_total_count if @testcase_total_count > 0
      result['elapsed_time'] = @elapsed_time if @elapsed_time > 0
      result['consumed_memory'] = @consumed_memory if @consumed_memory > 0
      JSON.dump(result)
    end
  end

  class LinkedListNode
    attr_accessor :value
    attr_accessor :next

    def initialize(value = nil, _next = nil)
      @value = value
      @next = _next
    end

    # just for debug
    def to_s
      result = '['
      result += value.nil? ? 'null' : value.to_s
      cur = @next
      until cur.nil?
        result += ', '
        result += cur.value.to_s
        cur = cur.next
      end
      result += ']'
      result
    end

    def ==(other)
      eql?(other)
    end

    def eql?(other)
      return false unless other.class == self.class
      p = self
      q = other
      while !p.nil? && !q.nil?
        return true if p.nil? && q.nil?
        return false if p.nil? || q.nil?
        return false unless p.value == q.value
        p = p.next
        q = q.next
      end

      p.nil? && q.nil?
    end

    def hash
      hash_code = 1
      p = self
      until p.nil?
        hash_code = 31 * hash_code + p.value.hash
        p = p.next
      end
      hash_code
    end
  end

  class BinaryTreeNode
    attr_accessor :value
    attr_accessor :left
    attr_accessor :right
    attr_accessor :left_is_null
    attr_accessor :right_is_null


    def initialize(value = nil, left = nil, right = nil, left_is_null=false, right_is_null=false)
      @value = value
      @left = left
      @right = right
      @left_is_null = left_is_null
      @right_is_null = right_is_null
    end

    class NodeAndFather
      attr_reader :node
      attr_reader :father
      attr_reader :is_right

      def initialize(node, father, is_right=false)
        @node = node
        @father = father
        @is_right = is_right
      end
    end

    def _tail
      queue = Queue.new
      queue << NodeAndFather.new(self, nil, true) unless @value.nil?

      until queue.empty?
        pos = queue.pop
        unless pos.node.nil?
          if !pos.node.left.nil? or pos.node.left_is_null
            queue << NodeAndFather.new(pos.node.left, pos.node, false)
          else
            return NodeAndFather.new(pos.node.left, pos.node, false)
          end
          if !pos.node.right.nil? or pos.node.right_is_null
            queue << NodeAndFather.new(pos.node.right, pos.node, true)
          else
            return NodeAndFather.new(pos.node.right, pos.node, true)
          end
        end
      end
      nil
    end

    def add(value)
      last = _tail
      if last.nil?
        @value = value
        return
      end

      if last.is_right
        if value.nil?
          last.father.right_is_null = true
        else
          last.father.right = BinaryTreeNode.new(value)
        end
      else
        if value.nil?
          last.father.left_is_null = true
        else
          last.father.left = BinaryTreeNode.new(value)
        end
      end
    end

    def to_s
      result = '['
      current = Queue.new
      _next = Queue.new

      current << self unless @value.nil?

      until current.empty?
        level = []
        until current.empty?
          level << current.pop
        end

        last_not_nil_index = -1
        (0..level.size()-1).reverse_each.each do |i|
          unless level[i].nil?
            last_not_nil_index = i
            break
          end
        end
        (0..last_not_nil_index).each do |i|
          node = level[i]
          if node.nil?
            result += 'null,'
          else
            result += node.value.to_s + ','
          end

          unless node.nil?
            _next << node.left
            _next << node.right
          end
        end

        # swap current and _next
        tmp = current
        current = _next
        _next = tmp
      end

      result.chomp(',') + ']'
    end

    def ==(other)
      eql?(other)
    end

    def eql?(other)
      return false unless other.class == self.class
      BinaryTreeNode.same_tree?(self, other)
    end

    def self.same_tree?(p, q)
      if p.nil? && q.nil?
        return true
      end
      if p.nil? || q.nil?
        return false
      end

      return p.value == q.value && p.left_is_null == q.left_is_null \
        && p.right_is_null == q.right_is_null && same_tree?(p.left, q.left) \
        && same_tree?(p.right, q.right)
    end

    def hash
      hash_code = 1
      stack = [self]

      until stack.empty?
        p = stack.pop
        hash_code = 31 * hash_code + p.value.hash
        stack << p.right unless cur.p.nil?
        stack << p.left unless cur.p.nil?
      end
      hash_code
    end

    private :_tail
  end


  def self.from_json(json_object, type_node)
    return json_object unless TypeNode.has_customized_type(type_node)

    case type_node.value
      when IntermediateType::ARRAY, IntermediateType::LIST
        _result = []
        json_object.each do |x|
          _result << from_json(x, type_node.element_type)
        end
        _result
      when IntermediateType::SET
        _result = Set.new
        json_object.each do |x|
          _result << from_json(x, type_node.element_type)
        end
        _result
      when IntermediateType::MAP
        _result = {}
        json_object.each do |key, value|
          real_key = from_json(JSON.load(key), type_node.key_type)
          real_value = from_json(value, type_node.element_type)
          _result[real_key] = real_value
        end
        _result
      when IntermediateType::LINKED_LIST_NODE
        if json_object.empty?
          nil
        else
          dummy = LinkedListNode.new
          tail = dummy
          json_object.each do |x|
            tail.next = LinkedListNode.new(from_json(x, type_node.element_type))
            tail = tail.next
          end
          dummy.next
        end
      when IntermediateType::BINARY_TREE_NODE
        if json_object.empty?
          nil
        else
          _result = BinaryTreeNode.new
          json_object.each do |x|
            _result.add(from_json(x, type_node.element_type))
          end
          _result
        end
      else
        raise 'Unsupported type: ' + type_node.value.to_s
    end
  end

  def self.to_json(obj, type_node)
    return obj unless TypeNode.has_customized_type(type_node)

    case type_node.value
      when IntermediateType::ARRAY, IntermediateType::LIST, IntermediateType::SET
        _result = []
        obj.each do |x|
          _result << to_json(x, type_node.element_type)
        end
        _result
      when IntermediateType::MAP
        _result = {}
        obj.each do |key, value|
          real_key = JSON.dump(to_json(key, type_node.key_type))
          real_value = to_json(value, type_node.element_type)
          _result[real_key] = real_value
        end
        _result
      when IntermediateType::LINKED_LIST_NODE
        _result = []
        cur = obj
        until cur.nil?
          _result << to_json(cur.value, type_node.element_type)
          cur = cur.next
        end
        _result
      when IntermediateType::BINARY_TREE_NODE
        _result = []
        current = Queue.new
        _next = Queue.new
        current << obj unless obj.nil?

        until current.empty?
          level = []
          level << current.pop until current.empty?

          last_not_nil_index = -1
          (0..(level.size - 1)).reverse_each.each do |i|
            unless level[i].nil?
              last_not_nil_index = i
              break
            end
          end
          (0..last_not_nil_index).each do |i|
            node = level[i]
            _result << if node.nil?
                         nil
                       else
                         to_json(node.value, type_node.element_type)
                       end
            unless node.nil?
              _next << node.left
              _next << node.right
            end
          end

          # swap current and _next
          tmp = current
          current = _next
          _next = tmp
        end
        _result
      else
        raise 'Unsupported type: ' + type_node.value.to_s
    end
  end
end
