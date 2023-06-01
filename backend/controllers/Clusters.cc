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

void Clusters::posts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, const std::string &type) {
        LOG_DEBUG << "someone is trying to get posts of the " << type << " group";

    std::vector<std::string> posts;

    Json::Value json;
    if (type == "MusiciansClusterBastards") {
        posts = {"Hi everyone, we are Coldplay and we are excited to announce our new album, Music of the Spheres, coming out on October 15th. It’s a cosmic journey through space and sound, and we can’t wait for you to hear it. Pre-order now and get access to exclusive content and merch. Thank you for your support and love",
        "Greetings from Metallica! We are thrilled to share with you our latest collaboration with the San Francisco Symphony Orchestra, S&M2. It’s a live album and concert film that captures the energy and intensity of our two-night performance at the Chase Center in 2019. You can stream it now on all platforms or get your copy on vinyl, CD, DVD or Blu-ray. Rock on!", 
        "Hello, we are BTS and we have a special surprise for you. We have just released a remix of our hit song Butter featuring Megan Thee Stallion. It’s a fun and funky track that will make you dance and smile. Check it out now on Spotify, Apple Music, YouTube and more. We hope you like it as much as we do"};
    }
    if (type == "NoPainNoGain") {
        posts = {"Hey guys, we are Imagine Dragons and we have some exciting news for you. We have just launched our own podcast, Origins, where we talk about our music, our inspirations, our stories and more. You can listen to it now on Spotify, Apple Podcasts, Google Podcasts and wherever you get your podcasts. We hope you enjoy it and let us know what you think", 
        "Hello, we are Maroon 5 and we want to thank you for your amazing support of our new single, Beautiful Mistakes, featuring Megan Thee Stallion. It’s a song about love, regret and forgiveness, and we are glad you connected with it. We have also released a stunning music video for it, directed by Sophie Muller. You can watch it now on YouTube and Vevo. Don’t forget to like, comment and subscribe.",
        "Hi there, we are One Direction and we have a special announcement for you. We are celebrating our 10th anniversary as a band with a special website that features all our memories, achievements, songs and videos. You can also access some exclusive content and merchandise that we have created for you. Visit www.onedirection10.com now and join us in this celebration. We love you all."};
    }
    if (type == "HardRockPayesOff") {
        posts = {"Hi there, we are One Direction and we have a special announcement for you. We are celebrating our 10th anniversary as a band with a special website that features all our memories, achievements, songs and videos. You can also access some exclusive content and merchandise that we have created for you. Visit www.onedirection10.com now and join us in this celebration. We love you all.",
        "Hi there, we are One Direction and we have a special announcement for you. We are celebrating our 10th anniversary as a band with a special website that features all our memories, achievements, songs and videos. You can also access some exclusive content and merchandise that we have created for you. Visit www.onedirection10.com now and join us in this celebration. We love you all.",
        "Hi everyone, we are U2 and we are happy to announce our new album, Songs of Experience, coming out on December 1st. It’s a companion piece to our previous album, Songs of Innocence, and it reflects our personal and political views on the world today. It features 13 songs, including the singles You’re The Best Thing About Me and Get Out Of Your Own Way. Pre-order now and get access to exclusive content and merch. Thank you for your support and love"};
    }

    for (const std::string& post : posts) {
        json["group_posts"].append(post);
    }

    json["status"] = "ok";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    callback(resp);

    LOG_DEBUG << "got group posts list successfully";
}
