#include "web.hpp"
#include "orm.hpp"
#include <gtest/gtest.h>

TEST(WebTest, Programmer) {
    FilterConverter filterconv;
    std::string programmer_result = "<div class='Programmers'>\n<div><input type='checkbox' /><label>Gamedev</label></div>\n</div>\n";
    std::vector<FilterSet> filtersets = {
        FilterSet("Musicians", {
            Filter("Группа", "checkbox", "type"),
            Filter("Количество участников", "integer", "member_count"),
            Filter("Жанр музыки", "text", "genre")
        }),
        FilterSet("Artists", {
            Filter("Пейзажисты", "checkbox", "type"),
            Filter("Количество участников", "integer", "member_count"),
            Filter("Жанр картин", "text", "genre")
        }),
        FilterSet("Programmers", {
            Filter("Gamedev", "checkbox", "type"),
        })
    };
    ASSERT_EQ(programmer_result, filterconv.ConvertFiltersSet(filtersets[2]));
}

TEST(ORMTest, ModelTest) {
    Model model;
    ASSERT_EQ("{login: user}", model.Serialize());
    ASSERT_EQ("user", model.Deserialize());
}

TEST(ORMTest, FeedTest) {
    User user;

    Model model1, model2;
    Feed feed;

    std::vector<Model> models = {
        model1,
        model2
    };
    ASSERT_EQ(models.size(), feed.GetFeed(user).size());
}

TEST(ORMTest, ModelFabricTest) {
    Model model;
    ModelFabric fabric;
    ASSERT_EQ(model.Serialize(), fabric.CreateModel("model").Serialize());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}