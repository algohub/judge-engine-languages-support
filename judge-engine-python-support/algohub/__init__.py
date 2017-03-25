from .type_node import TypeNode
from .intermediate_type import IntermediateType
from .linked_list_node import LinkedListNode
from .binary_tree_node import BinaryTreeNode
from .status_code import StatusCode
from .judge_result import JudgeResult
from collections import deque
import json

__version__ = '1.0'
__all__ = [
    'TypeNode', 'IntermediateType', 'LinkedListNode', 'BinaryTreeNode', 'from_json', 'to_json',
    'JudgeResult', 'StatusCode',
]


def from_json(json_object, type_node, father_type=None):
    if not TypeNode.has_customized_type(type_node):
        return json_object

    if type_node.value == IntermediateType.ARRAY or type_node.value == IntermediateType.LIST:
        result = []
        for x in json_object:
            result.append(from_json(x, type_node.element_type, type_node.value))
        if father_type == IntermediateType.SET:
            result = tuple(result)  # set can only contain immutable objects
    elif type_node.value == IntermediateType.SET:
        result = set()
        for x in json_object:
            result.add(from_json(x, type_node.element_type, type_node.value))
        if father_type == IntermediateType.SET:  # set can only contain immutable objects
            result = frozenset(result)
    elif type_node.value == IntermediateType.MAP:
        result = {}
        for key, value in json_object.items():
            real_key = from_json(json.loads(key), type_node.key_type)
            real_value = from_json(value, type_node.element_type, type_node.value)
            result[real_key] = real_value
        if father_type == IntermediateType.SET:  # set can only contain immutable objects
            result = frozenset(result.items())
    elif type_node.value == IntermediateType.LINKED_LIST_NODE:
        if json_object:
            dummy = LinkedListNode()
            tail = dummy
            for x in json_object:
                tail.next = LinkedListNode(from_json(x, type_node.element_type, type_node.value))
                tail = tail.next
            result = dummy.next
        else:
            result = None
    elif type_node.value == IntermediateType.BINARY_TREE_NODE:
        if json_object:
            result = BinaryTreeNode(None)
            for x in json_object:
                result.add(from_json(x, type_node.element_type, type_node.value))
        else:
            result = None
    else:
        raise TypeError("Unsupported type: " + str(type_node.value))

    return result


def to_json(obj, type_node):
    if not TypeNode.has_customized_type(type_node):
        return obj

    if type_node.value in (IntermediateType.ARRAY, IntermediateType.LIST, IntermediateType.SET):
        result = []
        for x in obj:
            result.append(to_json(x, type_node.element_type))
    elif type_node.value == IntermediateType.MAP:
        result = {}
        for key, value in obj.items():
            real_key = json.dumps(to_json(key, type_node.key_type))
            result[real_key] = to_json(obj[key], type_node.element_type)
    elif type_node.value == IntermediateType.LINKED_LIST_NODE:
        result = []
        cur = obj
        while cur is not None:
            result.append(to_json(cur.value, type_node.element_type))
            cur = cur.next
    elif type_node.value == IntermediateType.BINARY_TREE_NODE:
        result = []
        current = deque()
        next = deque()
        if obj is not None:
            current.append(obj)

        while len(current) > 0:
            level = []

            while len(current) > 0:
                level.append(current.popleft())

            last_not_null_index = -1
            for i in reversed(range(len(level))):
                if level[i] is not None:
                    last_not_null_index = i
                    break

            for i in range(last_not_null_index + 1):
                node = level[i]
                if node is not None:
                    result.append(to_json(node.value, type_node.element_type))
                else:
                    result.append(None)

                if node is not None:
                    next.append(node.left)
                    next.append(node.right)

            # swap current and next
            tmp = current
            current = next
            next = tmp
    else:
        raise TypeError("Unsupported type: " + str(type_node.value))

    return result

