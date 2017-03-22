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
    EXPECT_EQ(true, arrayIntJson == to_json(arrayInt, allocator));
    EXPECT_EQ(true, arrayIntJson == to_json(listInt, allocator));
//    EXPECT_EQ(true, arrayIntJson == to_json(setInt, allocator));
    EXPECT_EQ(true, arrayIntJson == to_json(linkedListInt, allocator));

    EXPECT_EQ(true, rapidjson::Value(rapidjson::kArrayType) == to_json(emptyLinkedList, allocator));

    EXPECT_EQ(true, mapStringIntJson == to_json(mapStringInt, allocator));
    EXPECT_EQ(true, mapIntDoubleJson == to_json(mapIntDouble, allocator));

    EXPECT_EQ(true, rapidjson::Value(rapidjson::kArrayType) == to_json(emptyBinaryTree, allocator));
    EXPECT_EQ(true, binaryTreeJson == to_json(binaryTree, allocator));

    EXPECT_EQ(true, arrayArrayIntJson == to_json(arrayArrayInt, allocator));
    EXPECT_EQ(true, arrayArrayIntJson == to_json(listListInt, allocator));
    EXPECT_EQ(true, arrayArrayIntJson == to_json(linkedListLinkedListInt, allocator));
    EXPECT_EQ(true, arrayArrayIntJson == to_json(arrayLinkedListInt, allocator));
//    EXPECT_EQ(true, arrayArrayIntJson == to_json(setLinkedListInt, allocator));

    EXPECT_EQ(true, mapStringLinkedListIntJson == to_json(mapStringLinkedListInt, allocator));
}
