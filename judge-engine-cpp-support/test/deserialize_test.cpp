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
    std::vector<int> arrayIntTmp;
    from_json(arrayIntJson, arrayIntTmp);
    EXPECT_EQ(arrayInt, arrayIntTmp);

    std::vector<int> listIntTmp;
    from_json(arrayIntJson, listIntTmp);
    EXPECT_EQ(listInt, listIntTmp);

    std::unordered_set<int> intSetTmp;
    from_json(arrayIntJson, intSetTmp);
    EXPECT_EQ(setInt, intSetTmp);

    std::shared_ptr<LinkedListNode<int>> linkedListTmp;
    from_json(arrayIntJson, linkedListTmp);
    EXPECT_EQ(linkedListInt, linkedListTmp);

    // empty linked list
    std::shared_ptr<LinkedListNode<int>> emptyLinkedListTmp;
    from_json(emptyArrayJson, emptyLinkedListTmp);
    EXPECT_EQ(nullptr, emptyLinkedListTmp);

    std::unordered_map<std::string, int> mapStringIntTmp;
    from_json(mapStringIntJson, mapStringIntTmp);
    EXPECT_EQ(mapStringInt, mapStringIntTmp);

    std::unordered_map<int, double> mapIntDoubleTmp;
    from_json(mapIntDoubleJson, mapIntDoubleTmp);
    EXPECT_EQ(mapIntDouble, mapIntDoubleTmp);

    // empty binary tree
    std::shared_ptr<BinaryTreeNode<int>> emptyBinaryTreeTmp;
    from_json(emptyArrayJson, emptyBinaryTreeTmp);
    EXPECT_EQ(nullptr, emptyBinaryTreeTmp);

    std::shared_ptr<BinaryTreeNode<int>> binaryTreeTmp;
    from_json(binaryTreeJson, binaryTreeTmp);
    EXPECT_EQ(binaryTree, binaryTreeTmp);

    std::vector<std::vector<int>> arrayArrayIntTmp;
    from_json(arrayArrayIntJson, arrayArrayIntTmp);
    EXPECT_EQ(arrayArrayInt, arrayArrayIntTmp);

    std::vector<std::vector<int>> listListIntTmp;
    from_json(arrayArrayIntJson, listListIntTmp);
    EXPECT_EQ(listListInt, listListIntTmp);

    std::vector<std::shared_ptr<LinkedListNode<int>>> arrayLinkedListTmp;
    from_json(arrayArrayIntJson, arrayLinkedListTmp);
    EXPECT_EQ(arrayLinkedListInt, arrayLinkedListTmp);

    std::unordered_set<std::shared_ptr<LinkedListNode<int>>> setLinkedListTmp;
    from_json(arrayArrayIntJson, setLinkedListTmp);
    EXPECT_EQ(setLinkedListInt, setLinkedListTmp);

    std::shared_ptr<LinkedListNode<std::shared_ptr<LinkedListNode<int>>>> linkedListLinkedListTmp;
    from_json(arrayArrayIntJson, linkedListLinkedListTmp);
    EXPECT_EQ(linkedListLinkedListInt, linkedListLinkedListTmp);

    std::unordered_map<std::string, std::shared_ptr<LinkedListNode<int>>> mapStringLinkedListTmp;
    from_json(mapStringLinkedListIntJson, mapStringLinkedListTmp);
    EXPECT_EQ(mapStringLinkedListInt, mapStringLinkedListTmp);
}
