#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "../models/models.hpp"

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

FilterConverter filterconv;

std::string programmer_result = "<div class='Programmers'>\n<div><input type='checkbox' /><label>Gamedev</label></div>\n</div>\n";