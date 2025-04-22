#include <gtest/gtest.h>
#include <shared_ptr.hpp>

TEST(MyShared, default_constructor) {
    SharedPtr<int> ptr;
    ASSERT_THROW(*ptr, std::logic_error);
}

TEST(MyShared, construtor_with_parameter) {
    SharedPtr<int> ptr(1);
    ASSERT_EQ(*ptr, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}