#include <iostream>
#include <vector>
#include "config/config.cpp"
#include <curl/curl.h>
#include "json.hpp"

struct StockData {
    std::string timestamp;
    double close;
};

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    ((std::string*)userdata)->append(ptr, size*nmemb);
    return size*nmemb;
};

std::string getUrl(std::string symb, const int interv, const std::string start, const std::string end){    
    std::string outsize = "compact";
    if(interv > 100){
        outsize = "full";
    }
    const std::string url = "https://api.polygon.io/v2/aggs/ticker/" + symb + "/range/1/day/" + start+"/"+ end + "?adjusted=true&sort=asc&apiKey=o5Yub929mEnEQxeyOsZ4fV9wZTA8cMTD";
    return url;
};


std::vector<StockData> fetchStockData(const std::string symb, const int shortwind, const int longwind){
    CURL* curl;
    CURLcode res;
    std::string buf;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    // TODO: Figure out how to get current day string in C++
    const std::string url = getUrl(symb, longwind);
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed!%s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    auto Json = nlohmann::json::parse(buf);
    std::vector<StockData> stockData;
    for (auto& [key, value] : Json["results"].items()) {
        stockData.push_back({ key, value["c"]});
    }
    return stockData;

}