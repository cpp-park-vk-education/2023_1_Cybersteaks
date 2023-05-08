#include "web.cpp"
#include "orm.cpp"
#include <gtest/gtest.h>

TEST(WebTest, Programmer) {
    ASSERT_EQ(programmer_result, filterconv.ConvertFiltersSet(filtersets[2]));
}

TEST(ORMTest, ModelTest) {
    ASSERT_EQ("{login: user}", model.Serialize());
    ASSERT_EQ("user", model.Deserialize());
}

TEST(ORMTest, FeedTest) {
    ASSERT_EQ(models.size(), feed.GetFeed(user).size());
}

TEST(ORMTest, ModelFabricTest) {
    ASSERT_EQ(model.Serialize(), fabric.CreateModel("model").Serialize());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
