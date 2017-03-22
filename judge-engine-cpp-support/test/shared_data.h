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
            arrayIntJson.PushBack(i+1, allocator);
        }

        mapStringIntJson.AddMember("\"hello\"", 1, allocator);
        mapStringIntJson.AddMember("\"world\"", 2, allocator);

        mapIntDoubleJson.AddMember("1", 1.0, allocator);
        mapIntDoubleJson.AddMember("2", 2.0, allocator);

        binaryTreeJson.PushBack(2, allocator);
        binaryTreeJson.PushBack(1, allocator);
        binaryTreeJson.PushBack(10, allocator);
        binaryTreeJson.PushBack(rapidjson::Value(rapidjson::kNullType).Move(), allocator);
        binaryTreeJson.PushBack(rapidjson::Value(rapidjson::kNullType).Move(), allocator);
        binaryTreeJson.PushBack(5, allocator);

        for(int i = 0; i < 5; ++i) {
            arrayIntJson2.PushBack(i+6, allocator);
        }

        arrayArrayIntJson.PushBack(rapidjson::Value(arrayIntJson, allocator).Move(), allocator);
        arrayArrayIntJson.PushBack(rapidjson::Value(arrayIntJson2, allocator).Move(), allocator);

        mapStringLinkedListIntJson.AddMember("\"hello\"", rapidjson::Value(arrayIntJson, allocator).Move(), allocator);
        mapStringLinkedListIntJson.AddMember("\"world\"", rapidjson::Value(arrayIntJson2, allocator).Move(), allocator);
    }

    rapidjson::Value arrayIntJson = rapidjson::Value(rapidjson::kArrayType);
    std::vector<int> arrayInt { 1, 2, 3, 4, 5 };
    const std::vector<int>& listInt  = arrayInt;
    std::unordered_set<int> setInt { 1, 2, 3, 4, 5 };
    std::shared_ptr<LinkedListNode<int>> linkedListInt = std::make_shared<LinkedListNode<int>>(
            1, std::make_shared<LinkedListNode<int>>(
                    2, std::make_shared<LinkedListNode<int>>(
                            3, std::make_shared<LinkedListNode<int>>(
                                    4, std::make_shared<LinkedListNode<int>>(5)))));

    std::unordered_map<std::string, int> mapStringInt { { "hello", 1 } , { "world", 2 }};
    rapidjson::Value mapStringIntJson = rapidjson::Value(rapidjson::kObjectType);

    std::unordered_map<int, double> mapIntDouble { { 1, 1.0 } , { 2, 2.0 }};
    rapidjson::Value mapIntDoubleJson = rapidjson::Value(rapidjson::kObjectType);

    std::shared_ptr<BinaryTreeNode<int>> binaryTree = std::make_shared<BinaryTreeNode<int>>(
            2, std::make_shared<BinaryTreeNode<int>>(
                    1), std::make_shared<BinaryTreeNode<int>>(
                    10, std::make_shared<BinaryTreeNode<int>>(5), nullptr));
    rapidjson::Value binaryTreeJson = rapidjson::Value(rapidjson::kArrayType);

    rapidjson::Value arrayIntJson2 = rapidjson::Value(rapidjson::kArrayType);
    std::vector<int> arrayInt2 { 6, 7, 8, 9, 10 };
    const std::vector<int>& listInt2 = arrayInt2;
    std::shared_ptr<LinkedListNode<int>> linkedListInt2 = std::make_shared<LinkedListNode<int>>(
            6, std::make_shared<LinkedListNode<int>>(
                    7, std::make_shared<LinkedListNode<int>>(
                            8, std::make_shared<LinkedListNode<int>>(
                                    9, std::make_shared<LinkedListNode<int>>(10)))));

    rapidjson::Value arrayArrayIntJson = rapidjson::Value(rapidjson::kArrayType);
    std::vector<std::vector<int>> arrayArrayInt  {arrayInt, arrayInt2};
    const std::vector<std::vector<int>>& listListInt = arrayArrayInt;
    std::shared_ptr<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>> linkedListLinkedListInt =
            std::make_shared<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>>(
                    linkedListInt, std::make_shared<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>>(linkedListInt2));
    std::vector<std::shared_ptr<LinkedListNode<int>>> arrayLinkedListInt {linkedListInt, linkedListInt2};
    std::unordered_set<std::shared_ptr<LinkedListNode<int>>> setLinkedListInt {linkedListInt, linkedListInt2};

    std::unordered_map<std::string, std::shared_ptr<LinkedListNode<int>>> mapStringLinkedListInt {
            {"hello", linkedListInt},
            {"world", linkedListInt2} };
    rapidjson::Value mapStringLinkedListIntJson = rapidjson::Value(rapidjson::kObjectType);

    // empty linked list
    std::shared_ptr<LinkedListNode<int>> emptyLinkedList{nullptr};
    // empty binary tree
    std::shared_ptr<BinaryTreeNode<int>> emptyBinaryTree{nullptr};
    // for empty linked list and empty binary tree
    rapidjson::Value emptyArrayJson = rapidjson::Value(rapidjson::kArrayType);

    rapidjson::Document d;
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
};

#endif //JUDGE_ENGINE_CPP_SUPPORT_SHARED_DATA_H
