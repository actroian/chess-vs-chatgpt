#include "L3.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string callChatGPT(const std::string& prompt, const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://api.openai.com/v1/engines/davinci-codex/completions";
        std::string postFields = R"({"prompt":")" + prompt + R"(","max_tokens":50})";

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

L3::L3(bool isWhite) : L2{isWhite} {}

Move L3::chooseMove(unique_ptr<Board>& b) {
    string prompt = "Here is my board (my piece are " + (isWhite ? "Capital letters" : "Lowercase letters") + " ): " + b->print();
    prompt += "\nprint out exactly 4 characters describing my best move (i.e a1a2)";
    
    string apiKey = "your_openai_api_key_here";

    string response = callChatGPT(prompt, apiKey);

    auto jsonResponse = json::parse(response);

    return {{0, 0}, {0, 0}};
}

vector<Move> L3::checkmateMoves() {
    // Implementation of getting checkmate moves for L3
    return {};
}

vector<Move> L3::avoidCaptureMoves() {
    // Implementation of getting avoid capture moves for L3
    return {};
}
