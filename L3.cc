#include "L3.h"
#include "apikey.h"
#include "curl/curl.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <string>
#include <sstream>

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

L3::L3(bool isWhite) : L2{isWhite}, attempts{0} {}

Move L3::chooseMove(unique_ptr<Board>& b) {
    ostringstream s;
    b->print(s);
    string prompt = "Here is my board (my piece are ";
    prompt += isWhite ? "Capital letters" : "Lowercase letters";
    prompt += " ): ";
    prompt += s.str();
    prompt += "\nprint out exactly 4 characters describing my best move (i.e a1a2)";

    string response = callChatGPT(prompt, API_KEY);
    auto jsonResponse = json::parse(response);

    // Extract the text field from the response
    string extractedText = jsonResponse["choices"][0]["text"].get<std::string>();
    
    string start, end;
    if (extractedText.length() == 4) {
        string start = extractedText.substr(0,2);
        string end = extractedText.substr(2,2);
        if (std::find(boardLocations.begin(), boardLocations.end(), start) == boardLocations.end() ||
            std::find(boardLocations.begin(), boardLocations.end(), end) == boardLocations.end()) {
            ++attempts;
            if (attempts > 3) {
                cout << "AI bot having issues... terminating program." << endl;
                exit(0);
            }
            return chooseMove(b);
        }
    }

    attempts = 0;
    return Move{posToInd[start], posToInd[end]};
}

vector<Move> L3::checkmateMoves() {
    // Implementation of getting checkmate moves for L3
    return {};
}

vector<Move> L3::avoidCaptureMoves() {
    // Implementation of getting avoid capture moves for L3
    return {};
}
