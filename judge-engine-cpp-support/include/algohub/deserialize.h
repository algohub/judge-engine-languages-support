#ifndef ALGOHUB_DESERIALIZE_H
#define ALGOHUB_DESERIALIZE_H

#include "common.h"
#ifndef RAPIDJSON_HAS_STDSTRING
#define RAPIDJSON_HAS_STDSTRING 1
#endif
#include <rapidjson/document.h>


template<typename T>
inline void from_json(const rapidjson::Value &json, T &result);

template<>
inline void from_json(const rapidjson::Value &json, bool &result) {
    result = json.GetBool();
}

template<>
 inline void from_json(const rapidjson::Value &json, char &result) {
    result = json.GetString()[0];
}

template<>
inline void from_json(const rapidjson::Value &json, int &result) {
    result = json.GetInt();
}

template<>
 inline void from_json(const rapidjson::Value &json, int64_t &result) {
    result = json.GetInt64();
}

template<>
inline void from_json(const rapidjson::Value &json, double &result) {
    result = json.GetDouble();
}

template<>
 inline void from_json(const rapidjson::Value &json, std::string &result) {
    result = std::string(json.GetString());
}

template<typename T>
inline void from_json(const rapidjson::Value &json, std::vector<T> &vec) {
    assert(json.IsArray());

    for (rapidjson::SizeType i = 0; i < json.Size(); i++) {
        T element;
        from_json(json[i], element);
        vec.push_back(element);
    }
}

template<typename T>
inline void from_json(const rapidjson::Value &json, std::unordered_set<T> &my_set) {
    assert(json.IsArray());

    for (rapidjson::SizeType i = 0; i < json.Size(); i++) {
        T element;
        from_json(json[i], element);
        my_set.insert(element);
    }
}


template<typename K, typename V>
inline void from_json(const rapidjson::Value &json, std::unordered_map<K, V> &my_map) {
    assert(json.IsObject());

    for (rapidjson::Value::ConstMemberIterator i = json.MemberBegin(); i != json.MemberEnd(); ++i) {
        // only allow strings as keys
        assert(i->name.IsString());
        rapidjson::Document document;
        document.Parse(i->name.GetString());
        K key;
        from_json(document, key);
        V value;
        from_json(i->value, value);
        my_map.insert({ key, value });
    }
}

template<typename T>
inline void from_json(const rapidjson::Value &json, std::shared_ptr<LinkedListNode<T>> &list) {
    assert(json.IsArray());

    auto dummy = std::make_shared<LinkedListNode<T>>();
    auto cur(dummy);
    for (rapidjson::SizeType i = 0; i < json.Size(); i++) {
        T element;
        from_json(json[i], element);
        cur->next = std::make_shared<LinkedListNode<T>>(element);
        cur = cur->next;
    }
    list = dummy->next;
}

template<typename T>
inline void from_json(const rapidjson::Value &json, std::shared_ptr<BinaryTreeNode<T>> &root) {
    assert(json.IsArray());
    if (json.Size() == 0) return;

    //TODO: can not put here, why?
    //    std::queue<std::shared_ptr<BinaryTreeNode<T>>> current, next;
    {
        T first_element;
        from_json(json[0], first_element);
        root = std::make_shared<BinaryTreeNode<T>>(first_element);
    }
    std::queue<std::shared_ptr<BinaryTreeNode<T>>> current, next;

    current.push(root);
    int i = 1;
    while (!current.empty() && i < json.Size()) {
        bool isRightChild = false;
        while (!current.empty() && i < json.Size()) {
            std::shared_ptr<BinaryTreeNode<T>> newNode;
            if (!json[i].IsNull()) {
                T element;
                from_json(json[i], element);
                newNode = std::make_shared<BinaryTreeNode<T>>(element);
            }

            decltype(root) father = current.front();
            if (isRightChild) current.pop();

            if (newNode) {
                next.push(newNode);
                if (isRightChild) {
                    father->right = newNode;
                }
                else {
                    father->left = newNode;
                }
            }
            isRightChild = !isRightChild;
            ++i;
        }
        std::swap(current, next);
    }
}



#endif //ALGOHUB_DESERIALIZE_H
