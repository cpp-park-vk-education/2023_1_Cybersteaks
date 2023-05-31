#include "web.hpp"

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