#include <gtest/gtest.h>
#include "../include/algohub/deserialize.h"
#include "shared_data.h"


TEST(deserialize_test, primitive_types) {
    rapidjson::Document doc;
    auto& allocator = doc.GetAllocator();

    bool bool_value;
    from_json(rapidjson::Value(rapidjson::kTrueType), bool_value);
    EXPECT_EQ(true, bool_value);
    from_json(rapidjson::Value(rapidjson::kFalseType), bool_value);
    EXPECT_EQ(false, bool_value);

    char ch;
    auto charNode = rapidjson::Value(rapidjson::kStringType);
    charNode.SetString("a", 1, allocator);
    from_json(charNode, ch);
    EXPECT_EQ('a', ch);

    int n;
    from_json(rapidjson::Value(123), n);
    EXPECT_EQ(123, n);

    int64_t l;
    from_json(rapidjson::Value((int64_t)123), l);
    EXPECT_EQ((int64_t)123, l);

    double d;
    from_json(rapidjson::Value(123.0), d);
    EXPECT_EQ(123.0, d);

    std::string s;
    auto stringNode = rapidjson::Value(std::string("algohub"), allocator);
    from_json(stringNode, s);
    EXPECT_EQ(std::string("algohub"), s);
}

TEST_F(SharedData, deserialize_collection_test) {
    std::vector<int> intArrayTmp;
    from_json(intArrayNode, intArrayTmp);
    EXPECT_EQ(intArray, intArrayTmp);

    std::unordered_set<int> intSetTmp;
    from_json(intArrayNode, intSetTmp);
    EXPECT_EQ(intSet, intSetTmp);

    std::shared_ptr<LinkedListNode<int>> linkedListTmp;
    from_json(intArrayNode, linkedListTmp);
    EXPECT_EQ(linkedList, linkedListTmp);

    std::unordered_map<std::string, int> mapStringIntTmp;
    from_json(mapStringIntNode, mapStringIntTmp);
    EXPECT_EQ(mapStringInt, mapStringIntTmp);

    std::unordered_map<int, double> mapIntDoubleTmp;
    from_json(mapIntDoubleNode, mapIntDoubleTmp);
    EXPECT_EQ(mapIntDouble, mapIntDoubleTmp);

    std::shared_ptr<BinaryTreeNode<int>> binaryTreeTmp;
    from_json(binaryTreeNode, binaryTreeTmp);
    EXPECT_EQ(binaryTree, binaryTreeTmp);

    std::vector<std::vector<int>> intArrayArrayTmp;
    from_json(arrayArrayNode, intArrayArrayTmp);
    EXPECT_EQ(intArrayArray, intArrayArrayTmp);

    std::vector<std::shared_ptr<LinkedListNode<int>>> arrayLinkedListTmp;
    from_json(arrayArrayNode, arrayLinkedListTmp);
    EXPECT_EQ(arrayLinkedList, arrayLinkedListTmp);

    std::unordered_set<std::shared_ptr<LinkedListNode<int>>> setLinkedListTmp;
    from_json(arrayArrayNode, setLinkedListTmp);
    EXPECT_EQ(setLinkedList, setLinkedListTmp);

    std::shared_ptr<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>> linkedListLinkedListTmp;
    from_json(arrayArrayNode, linkedListLinkedListTmp);
    EXPECT_EQ(linkedListLinkedList, linkedListLinkedListTmp);

    std::unordered_map<std::string, std::shared_ptr<LinkedListNode<int>>> mapStringLinkedListTmp;
    from_json(mapStringLinkedListNode, mapStringLinkedListTmp);
    EXPECT_EQ(mapStringLinkedList, mapStringLinkedListTmp);
}
