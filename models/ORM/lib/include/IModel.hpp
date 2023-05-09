#include <string>
#include <map>

class IModel {
    virtual static std::string GetModelName() = 0;
    virtual static std::string GetFilterExpression(IModel filter_object) = 0;
    virtual static std::map<std::string, std::string> Serialize(IModel object) = 0;
    virtual static IModel Deserialize(std::map<std::string, std::string> object) = 0;
}

template<typename Model>
class ModelManager
{
public:
    std::vector<Model> All();
    std::vector<Model> Filter(Model filter_object);
    std::string<Model> Get(std::vector<size_t> objects_id);
    void Delete(Model filter_object);
    void Insert(Model object);
};

IModel ModelFabric(std::string model_name);
