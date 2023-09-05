#include "../include/ORM.hpp"
#include <vector>

template<typename Model>
class IModelManager 
{
public:
    std::vector<Model> All()
    {
        std::vector<Model> result;
        auto rows = ORM::Select( GetModelName() );
        for(auto& row : rows)
            result.push_back(Model(row));
        return result;
    }

    std::vector<Model> Filter(const Model& model)
    {
        std::vector<Model> result;
        auto expression = GetFilterExpression(model);
        auto rows = ORM::Filter(expression);
        for(auto& row : rows)
            result.push_back(Model(row));
        return result;
    }

    void Delete(const Model& model)
    {
        std::vector<Model> result;
        auto expression = GetFilterExpression(model);
        auto rows = ORM::Filter(expression);
        for(auto& row : rows)
        {
            auto model = Model(row);
            Delete(model.GetModelName(), model.id);
        }
    }

    void Insert(const Model& model)
    {
        std::vector<Model> result;
        auto expression = GetFilterExpression(model);
        auto rows = ORM::Filter(expression);
        for(auto& row : rows)
        {
            auto model = Model(row);
            Insert(model.GetModelName(), model.Deserialize());
        }
    }
};


