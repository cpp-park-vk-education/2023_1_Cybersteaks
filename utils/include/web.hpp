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

class FilterConverter {
public:
    static std::string ConvertFiltersSet(FilterSet filterset);
    static std::string ConvertFilter(Filter filter);

private:
    static std::string CreateCheckBoxFilter(Filter filter);
    static std::string CreateIntegerFilter(Filter filter);
    static std::string CreateTextFilter(Filter filter);
};