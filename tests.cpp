#include "web.cpp"
#include <gtest/gtest.h>

TEST(WebTest, Programmer) {
    ASSERT_EQ(programmer_result, filterconv.ConvertFiltersSet(filtersets[2]));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}