from .intermediate_type import IntermediateType
import json


class TypeNode:
    def __init__(self, value, element_type=None,
                 key_type=None):
        self.value = value
        self.key_type = key_type
        self.element_type = element_type

    @staticmethod
    def to_json(type_node):
        json_str = '{"value":"' + str(type_node.value) + '"'
        if type_node.key_type is not None:
            json_str += ', "key_type": ' + TypeNode.to_json(type_node.key_type)
        if type_node.element_type is not None:
            json_str += ', "element_type": ' + TypeNode.to_json(type_node.element_type)
        return json_str + '}'

    @staticmethod
    def from_json(json_str):
        return json.loads(json_str, object_hook=typenode_object_hook)

    @staticmethod
    def has_customized_type(type_node):
        cur = type_node
        while cur is not None:
            if cur.value == IntermediateType.LINKED_LIST_NODE or \
                            cur.value == IntermediateType.BINARY_TREE_NODE or \
                            cur.value == IntermediateType.SET or \
                            cur.value == IntermediateType.MAP:
                return True
            cur = cur.element_type

        cur = type_node
        while cur is not None:
            if cur.value == IntermediateType.LINKED_LIST_NODE or \
                            cur.value == IntermediateType.BINARY_TREE_NODE or \
                            cur.value == IntermediateType.SET or \
                            cur.value == IntermediateType.MAP:
                return True
            cur = cur.key_type
        return False

# Map keys to classes
__mapping = {frozenset(('value', 'key_type', 'element_type')): TypeNode}


def typenode_object_hook(d):
    for keys, cls in __mapping.items():
        if keys.issuperset(d.keys()):
            d["value"] = IntermediateType(d["value"])
            return cls(**d)
    else:
        # Raise exception instead of silently returning None
        raise ValueError('Unable to find a matching class for object: {!s}'.format(d))

