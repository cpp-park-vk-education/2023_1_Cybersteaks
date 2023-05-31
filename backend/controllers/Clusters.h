#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Clusters : public drogon::HttpController<Clusters>
{
  public:
    void main(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &type);
    void groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &type);

    METHOD_LIST_BEGIN
    METHOD_ADD(Clusters::main, "/?type={1}", Get);
    METHOD_ADD(Clusters::groups, "/groups/?type={1}", Get);
    METHOD_LIST_END
};
