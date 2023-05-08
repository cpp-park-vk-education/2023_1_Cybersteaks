#pragma once
#include <iostream>
#include <string>

class ORMGenerator
{
public:
    const std::string model_file;
    void GenerateFilters();
    void GenerateModelManager();
    void GenerateModels();
    void FillModels(); //ToDO in late
};