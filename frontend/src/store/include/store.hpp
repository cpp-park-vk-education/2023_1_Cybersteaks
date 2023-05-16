#pragma once
#include <string>
#include <vector>
#include "model.hpp"

class StoreObject {
public:
    void SetType();
private:
    std::string type;
};

class Store {
public:
    Store();
    void AddGroup(const Group& group);
    
    ~Store();
private:
    std::vector<Group> groups;
};