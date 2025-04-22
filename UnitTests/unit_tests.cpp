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

TEST(MyShared, copy_constructor) {
    SharedPtr<int> ptr_a(1);
    SharedPtr<int> ptr_b = ptr_a;

    ASSERT_EQ(*ptr_b, 1);
    ASSERT_EQ(ptr_b.use_refs(), 2);
}

TEST(MyShared, assigment_copy) {
    SharedPtr<int> ptr_a(1);
    {
        SharedPtr<int> ptr_b;
        ptr_b = ptr_a;

        ASSERT_EQ(*ptr_b, 1);
        ASSERT_EQ(ptr_b.use_refs(), 2);
    }
}

TEST(MyShared, dereference_operator) {
    SharedPtr<std::string> ptr("Hello");
    ASSERT_EQ(*ptr, "Hello");

    SharedPtr<int> ptr2(1);
    *ptr2 = 2;
    ASSERT_EQ(*ptr2, 2);
}

TEST(MyShared, get) {
    SharedPtr<int> ptr;
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(MyShared, use_refs) {
    SharedPtr<int> ptr_a;
    ASSERT_EQ(ptr_a.use_refs(), 0);

    ptr_a = 3;
    ASSERT_EQ(*ptr_a, 3);

    SharedPtr<int> ptr_b = ptr_a;
    ASSERT_EQ(ptr_a.use_refs(), 2);

}

TEST(MyShared, interface_stress_test) {
    const int N = 10000;

    SharedPtr<int> base(42);
    EXPECT_EQ(*base, 42);
    EXPECT_NE(base.get(), nullptr);
    EXPECT_EQ(base.use_refs(), 1);

    std::vector<SharedPtr<int>> vec;

    for (int i = 0; i < N; ++i) {
        vec.push_back(base);
        EXPECT_EQ(*vec.back(), 42);
        EXPECT_EQ(vec.back().get(), base.get());
    }

    EXPECT_EQ(base.use_refs(), N + 1);

    for (int i = 0; i < N; ++i) {
        vec[i] = SharedPtr<int>(100 + i);
        EXPECT_EQ(*vec[i], 100 + i);
        EXPECT_EQ(vec[i].use_refs(), 1);
    }

    EXPECT_EQ(base.use_refs(), 1);
    SharedPtr<int> empty;
    EXPECT_EQ(empty.get(), nullptr);
    EXPECT_EQ(empty.use_refs(), 0);
    EXPECT_THROW(*empty, std::logic_error);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}