#ifndef ALGOHUB_SERIALIZE_H
#define ALGOHUB_SERIALIZE_H

#include "common.h"
#ifndef RAPIDJSON_HAS_STDSTRING
#define RAPIDJSON_HAS_STDSTRING 1
#endif
#include <rapidjson/document.h>


#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
static inline std::string json_value_to_string(const rapidjson::Value &value) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);

    return std::string(buffer.GetString());
}


typedef rapidjson::Document::AllocatorType AllocatorType;


static inline  rapidjson::Value to_json(bool value, AllocatorType& allocator) {
    return rapidjson::Value(value);
}

static inline  rapidjson::Value to_json(char value, AllocatorType& allocator) {
    auto result = rapidjson::Value(rapidjson::kStringType);
    char buffer[2];
    buffer[0] = value;
    buffer[1] = '\0';
    result.SetString(buffer, 1, allocator);
    return result;
}

static inline  rapidjson::Value to_json(int value, AllocatorType& allocator) {
    return rapidjson::Value(value);
}


static inline  rapidjson::Value to_json(int64_t value, AllocatorType& allocator) {
    return rapidjson::Value(value);
}


static inline  rapidjson::Value to_json(double value, AllocatorType& allocator) {
    return rapidjson::Value(value);
}


static inline  rapidjson::Value to_json(const std::string& value, AllocatorType& allocator) {
    return rapidjson::Value(value, allocator);
}


template <typename T>
static inline rapidjson::Value to_json(const std::vector<T>& vec, AllocatorType& allocator) {
    auto result = rapidjson::Value(rapidjson::kArrayType);
    for (const auto &x : vec) {
        result.PushBack(to_json(x, allocator).Move(), allocator);
    }

    return result;
}


template <typename T>
static inline rapidjson::Value to_json(const std::unordered_set<T>& mySet, AllocatorType& allocator) {
    auto result = rapidjson::Value(rapidjson::kArrayType);
    for (const auto &x : mySet) {
        result.PushBack(to_json(x, allocator).Move(), allocator);
    }

    return result;
}


template <typename K, typename V>
static inline rapidjson::Value to_json(const std::unordered_map<K, V>& myMap, AllocatorType& allocator) {
    auto result = rapidjson::Value(rapidjson::kObjectType);
    for (const auto &x : myMap) {
        result.AddMember(rapidjson::Value(json_value_to_string(to_json(x.first, allocator)), allocator).Move(),
                         to_json(x.second, allocator).Move(), allocator);
    }

    return result;
}


template <typename T>
static inline rapidjson::Value to_json(const std::shared_ptr<LinkedListNode<T>> &head, AllocatorType& allocator) {
    auto result = rapidjson::Value(rapidjson::kArrayType);

    for (std::shared_ptr<LinkedListNode<T>> cur = head; cur; cur = cur->next) {
        result.PushBack(to_json(cur->value, allocator).Move(), allocator);
    }
    return result;
}


template <typename T>
static inline rapidjson::Value to_json(const std::shared_ptr<BinaryTreeNode<T>>& root, AllocatorType& allocator) {
    auto result = rapidjson::Value(rapidjson::kArrayType);
    std::queue<std::shared_ptr<BinaryTreeNode<T>>> current, next;

    if (root) current.push(root);
    while (!current.empty()) {
        std::vector<std::shared_ptr<BinaryTreeNode<T>>> level;
        while (!current.empty()) {
            auto node = current.front();
            current.pop();
            level.push_back(node);
        }

        int lastNotNullIndex = -1;
        for (int i = level.size() - 1; i >= 0; i--) {
            if (level[i] != nullptr) {
                lastNotNullIndex = i;
                break;
            }
        }

        for (int i = 0; i <= lastNotNullIndex; ++i) {
            auto node = level[i];
            if (node) {
                result.PushBack(to_json(node->value, allocator).Move(), allocator);
            } else {
                result.PushBack(rapidjson::Value(rapidjson::kNullType).Move(), allocator);
            }
            if (node != nullptr) {
                next.push(node->left);
                next.push(node->right);
            }
        }
        std::swap(next, current);
    }

    return result;
}



#endif //ALGOHUB_SERIALIZE_H
