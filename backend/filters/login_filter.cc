/**
 *
 *  login_filter.cc
 *
 */

#include "login_filter.h"

using namespace drogon;

void login_filter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) {
    Json::Value json;
    auto request_body = req->getJsonObject();

    if (!(request_body->isMember("login")) || !(request_body->isMember("email"))) {
        json["status"] = "error";
        json["message"] = "missing login/email/password";

        auto response = HttpResponse::newHttpJsonResponse(json);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        fcb(response);
        return;
    }

    fccb();
}
