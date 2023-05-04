#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

struct Filter {
    std::string name;
    std::string type;
    std::string model_field;
    Filter(const std::string& name, const std::string& type, const std::string& model_field) {
        this->name = name;
        this->type = type;
        this->model_field = model_field;
    }
};

struct FilterSet {
    std::vector<Filter> filters;
    std::string model;
    FilterSet(const std::string& model, std::vector<Filter> filters) {
        this->filters = filters;
        this->model = model;
    }
};

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
    FilterSet("Prorammers", {
        Filter("Геймдев", "checkbox", "type"),
        Filter("Количество участников", "integer", "member_count"),
        Filter("Сфера программирования", "text", "dev_field")
    })
};

class FilterConverter {
public:
    static std::string ConvertFiltersSet(FilterSet filterset);

    static std::string ConvertFilter(Filter filter);

private:
    static std::string CreateCheckBoxFilter(Filter filter);

    static std::string CreateIntegerFilter(Filter filter);

    static std::string CreateTextFilter(Filter filter);
};

std::string FilterConverter::ConvertFiltersSet(FilterSet filterset) {
    std::string result_page = "<div class='" + filterset.model + "'>";
    result_page += "\n";
    for (int i = 0; i < filterset.filters.size(); i++) {
        result_page += ConvertFilter(filterset.filters[i]);
    }
    result_page += "</div>";
    result_page += "\n";
    return result_page;
}

std::string FilterConverter::ConvertFilter(Filter filter) {
    std::string result_element = "";
    if (filter.type == "checkbox") {
        result_element = CreateCheckBoxFilter(filter);
    }
    if (filter.type == "integer") {
        result_element = CreateIntegerFilter(filter);
    }
    if (filter.type == "text") {
        result_element = CreateTextFilter(filter);
    }
    result_element += "\n";
    return result_element;
};

std::string FilterConverter::CreateCheckBoxFilter(Filter filter) {
    std::string result_filter = "";
    result_filter = "<div><input type='checkbox' /><label>" + filter.name + "</label></div>";
    return result_filter;
}

std::string FilterConverter::CreateIntegerFilter(Filter filter) {
    std::string result_filter = "";
    result_filter = "<div>" + filter.name + ": <span>" + filter.model_field + "</span></div>";
    return result_filter;
}

std::string FilterConverter::CreateTextFilter(Filter filter) {
    std::string result_filter = "";
    result_filter = "<div>" + filter.name + ": <input type='text' placeholder='Введите текст' /></div>";
    return result_filter;
}

int main()
{
    FilterConverter filterconv;
    std::string page = filterconv.ConvertFiltersSet(filtersets[2]);
    std::cout << page;
}