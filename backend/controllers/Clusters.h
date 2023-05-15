#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class Clusters : public drogon::HttpSimpleController<Clusters>
{
   public:
    void main(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    PATH_LIST_BEGIN
    METHOD_ADD(Clusters::main, "/", Get);
    PATH_LIST_END
};
