#include "Clusters.h"
#include <vector>
#include <string>

void Clusters::main(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_DEBUG << "someone is trying to get clusters list";

    std::vector<std::string> clusters; // from db

    json["clusters"] = Json::arrayValue;

    for (const std::string& cluster : clusters) {
        json["clusters"].append(cluster);
    }

    json["status"] = "ok";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    callback(resp);

    LOG_DEBUG << "got clusters list successfully";

}
