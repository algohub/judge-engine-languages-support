#include <gtest/gtest.h>
#include "../include/algohub/serialize.h"
#include "shared_data.h"


TEST(serialize_test, primitive_types) {
    rapidjson::Document d;
    auto& allocator = d.GetAllocator();

    EXPECT_EQ(rapidjson::Value(rapidjson::kTrueType), to_json(true, allocator));
    EXPECT_EQ(rapidjson::Value(rapidjson::kFalseType), to_json(false, allocator));

    auto charNode = rapidjson::Value(std::string("a"), allocator);
    EXPECT_EQ(true, charNode == to_json('a', allocator));

    EXPECT_EQ(true, rapidjson::Value(123) == to_json(123, allocator));
    EXPECT_EQ(true, rapidjson::Value((int64_t)123) == to_json((int64_t)123, allocator));
    EXPECT_EQ(true, rapidjson::Value(123.0) == to_json(123.0, allocator));

    auto stringNode = rapidjson::Value(std::string("algohub"), allocator);
    EXPECT_EQ(true, stringNode == to_json(std::string("algohub"), allocator));
}

TEST_F(SharedData, serialize_collection_test) {
    EXPECT_EQ(true, intArrayNode == to_json(intArray, allocator));

//    unordered_set<int> intSetTmp;
//    from_json(to_json(intSet, allocator), intSetTmp);
//    EXPECT_EQ(intSet, intSetTmp);

    EXPECT_EQ(true, rapidjson::Value(rapidjson::kArrayType) == to_json(emptyLinkedList, allocator));

    EXPECT_EQ(true, intArrayNode == to_json(linkedList, allocator));

    EXPECT_EQ(true, mapStringIntNode == to_json(mapStringInt, allocator));

    EXPECT_EQ(true, mapIntDoubleNode == to_json(mapIntDouble, allocator));

    EXPECT_EQ(true, rapidjson::Value(rapidjson::kArrayType) == to_json(emptyBinaryTree, allocator));

    EXPECT_EQ(true, binaryTreeNode == to_json(binaryTree, allocator));

    EXPECT_EQ(true, arrayArrayNode == to_json(intArrayArray, allocator));

    EXPECT_EQ(true, arrayArrayNode == to_json(arrayLinkedList, allocator));

    EXPECT_EQ(true, arrayArrayNode == to_json(linkedListLinkedList, allocator));

    EXPECT_EQ(true, mapStringLinkedListNode == to_json(mapStringLinkedList, allocator));
}
