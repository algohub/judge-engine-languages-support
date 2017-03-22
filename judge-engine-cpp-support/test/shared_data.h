#ifndef JUDGE_ENGINE_CPP_SUPPORT_SHARED_DATA_H
#define JUDGE_ENGINE_CPP_SUPPORT_SHARED_DATA_H

#ifndef RAPIDJSON_HAS_STDSTRING
#define RAPIDJSON_HAS_STDSTRING 1
#endif
#include <rapidjson/document.h>
#include <gtest/gtest.h>


class SharedData : public ::testing::Test {
protected:
    virtual void SetUp() {
        for(int i = 0; i < 5; ++i) {
            intArrayNode.PushBack(i+1, allocator);
        }

        mapStringIntNode.AddMember("\"hello\"", 1, allocator);
        mapStringIntNode.AddMember("\"world\"", 2, allocator);

        mapIntDoubleNode.AddMember("1", 1.0, allocator);
        mapIntDoubleNode.AddMember("2", 2.0, allocator);

        binaryTreeNode.PushBack(2, allocator);
        binaryTreeNode.PushBack(1, allocator);
        binaryTreeNode.PushBack(10, allocator);
        binaryTreeNode.PushBack(rapidjson::Value(rapidjson::kNullType).Move(), allocator);
        binaryTreeNode.PushBack(rapidjson::Value(rapidjson::kNullType).Move(), allocator);
        binaryTreeNode.PushBack(5, allocator);

        for(int i = 0; i < 5; ++i) {
            intArrayNode2.PushBack(i+6, allocator);
        }

        arrayArrayNode.PushBack(rapidjson::Value(intArrayNode, allocator).Move(), allocator);
        arrayArrayNode.PushBack(rapidjson::Value(intArrayNode2, allocator).Move(), allocator);

        mapStringLinkedListNode.AddMember("\"hello\"", rapidjson::Value(intArrayNode, allocator).Move(), allocator);
        mapStringLinkedListNode.AddMember("\"world\"", rapidjson::Value(intArrayNode2, allocator).Move(), allocator);
    }

    rapidjson::Value intArrayNode = rapidjson::Value(rapidjson::kArrayType);
    std::vector<int> intArray { 1, 2, 3, 4, 5 };
    std::unordered_set<int> intSet { 1, 2, 3, 4, 5 };

    // empty linked list
    std::shared_ptr<LinkedListNode<int>> emptyLinkedList{nullptr};

    std::shared_ptr<LinkedListNode<int>> linkedList = std::make_shared<LinkedListNode<int>>(
            1, std::make_shared<LinkedListNode<int>>(
                    2, std::make_shared<LinkedListNode<int>>(
                            3, std::make_shared<LinkedListNode<int>>(
                                    4, std::make_shared<LinkedListNode<int>>(5)))));

    std::unordered_map<std::string, int> mapStringInt { { "hello", 1 } , { "world", 2 }};
    rapidjson::Value mapStringIntNode = rapidjson::Value(rapidjson::kObjectType);

    std::unordered_map<int, double> mapIntDouble { { 1, 1.0 } , { 2, 2.0 }};
    rapidjson::Value mapIntDoubleNode = rapidjson::Value(rapidjson::kObjectType);

    // empty binary tree
    std::shared_ptr<BinaryTreeNode<int>> emptyBinaryTree{nullptr};

    std::shared_ptr<BinaryTreeNode<int>> binaryTree = std::make_shared<BinaryTreeNode<int>>(
            2, std::make_shared<BinaryTreeNode<int>>(
                    1), std::make_shared<BinaryTreeNode<int>>(
                    10, std::make_shared<BinaryTreeNode<int>>(5), nullptr));
    rapidjson::Value binaryTreeNode = rapidjson::Value(rapidjson::kArrayType);

    std::vector<int> intArray2 { 6, 7, 8, 9, 10 };
    rapidjson::Value intArrayNode2 = rapidjson::Value(rapidjson::kArrayType);

    std::vector<std::vector<int>> intArrayArray  {intArray, intArray2};
    rapidjson::Value arrayArrayNode = rapidjson::Value(rapidjson::kArrayType);

    std::shared_ptr<LinkedListNode<int>> linkedList2 = std::make_shared<LinkedListNode<int>>(
            6, std::make_shared<LinkedListNode<int>>(
                    7, std::make_shared<LinkedListNode<int>>(
                            8, std::make_shared<LinkedListNode<int>>(
                                    9, std::make_shared<LinkedListNode<int>>(10)))));
    std::vector<std::shared_ptr<LinkedListNode<int>>> arrayLinkedList {linkedList, linkedList2};

    std::unordered_set<std::shared_ptr<LinkedListNode<int>>> setLinkedList {linkedList, linkedList2};

    std::shared_ptr<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>> linkedListLinkedList =
            std::make_shared<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>>(
            linkedList, std::make_shared<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>>(linkedList2));

    std::unordered_map<std::string, std::shared_ptr<LinkedListNode<int>>> mapStringLinkedList { {"hello", linkedList},
                                                                                 {"world", linkedList2} };
    rapidjson::Value mapStringLinkedListNode = rapidjson::Value(rapidjson::kObjectType);

    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
};

#endif //JUDGE_ENGINE_CPP_SUPPORT_SHARED_DATA_H
