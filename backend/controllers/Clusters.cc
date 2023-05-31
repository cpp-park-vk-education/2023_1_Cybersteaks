#include "Clusters.h"
#include <vector>
#include <string>

void Clusters::main(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &type) {
    LOG_DEBUG << "someone is trying to get clusters list";

    Json::Value json;

    std::vector<std::string> clusters;
    bool contains = false;

    if (type.find("musicians") != std::string::npos) {
        clusters.push_back("Musicians");
        contains = true;
    }
    if (type.find("artists") != std::string::npos) {
        clusters.push_back("Artists");
        contains = true;
    }
    if (type.find("programmers") != std::string::npos) {
        clusters.push_back("Programmers");
        contains = true;
    }

    if (!contains) {
        clusters = {"Musicians", "Artists", "Programmers"};
    }

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

void Clusters::groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &type) {
    LOG_DEBUG << "someone is trying to get clusters groups list";

    std::vector<std::string> groups;

    Json::Value json;
    if (type == "musicians") {
        groups = {"NoPainNoGain", "MusiciansClusterBastards", "HardRockPayesOff"};
    }
    if (type == "artists") {
        groups = {"LoveArt", "ArtOrDart", "ArtistsForGood"};
    }
    if (type == "programmers") {
        groups = {"BornToCoDE", "CodersForModers", "TechnoparkBMSTUGROUP"};
    }

    json["cluster_groups"] = Json::arrayValue;

    for (const std::string& group : groups) {
        json["cluster_groups"].append(group);
    }

    json["status"] = "ok";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    callback(resp);

    LOG_DEBUG << "got clusters groups list successfully";
}
