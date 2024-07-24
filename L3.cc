#include "L3.h"
#include "apikey.h"
#include "curl/curl.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <string>
#include <sstream>

using json = nlohmann::json;
using namespace std;

size_t L3::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string L3::callChatGPT(const std::string& prompt, const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://api.openai.com/v1/chat/completions";
        json postData = {
            {"model", "gpt-4o-mini"},
            {"messages", json::array({{
                {"role", "user"},
                {"content", prompt}
            }})},
            {"temperature", 0.5}
        };

        std::string postFields = postData.dump();

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            ++attempts;
            if (attempts > 3) {
                cout << "Issues making API request... terminating program." << endl;
                exit(0);
            }
            callChatGPT(prompt, apiKey);
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    return readBuffer;
}

L3::L3(bool isWhite) : L2{isWhite}, attempts{0} {}

Move L3::chooseMove(unique_ptr<Board>& b) {
    ostringstream s;
    b->print(s);
    
    string prompt = "Here is the current chess board:\n";
    prompt += s.str();
    prompt += "\nYou are playing as ";
    prompt += isWhite ? "White (capital letters)" : "Black (lowercase letters)";
    prompt += ".\nOnly provide moves for ";
    prompt += isWhite ? "White pieces (capital letters)" : "Black pieces (lowercase letters)";
    prompt += ".\nYour move should be exactly 4 characters, describing the best move in the format 'a1a2'. For example, if you are moving a White piece, provide a move like 'E2E4', and if you are moving a Black piece, provide a move like 'e7e5'.";
    prompt += "\nPlease ensure you only move the correct pieces based on your color.";
    prompt += "\np = pawn, k = king, q = queen, b = bishop, n = knight, r = rook";

    string response = callChatGPT(prompt, API_KEY);
    if (response.find("error") != string::npos) {
        ++attempts;
        if (attempts > 3) {
            cout << "Error: " << response << endl;
            cout << "Terminating program." << endl;
            exit(0);
        }
    }
    auto jsonResponse = json::parse(response);

    // Extract the text field from the response
    string extractedText = jsonResponse["choices"][0]["message"]["content"].get<std::string>();
    
    string start, end;
    if (extractedText.length() == 4) {
        start = extractedText.substr(0,2);
        start[0] = tolower(start[0]);
        end = extractedText.substr(2,2);
        end[0] = tolower(end[0]);
        if (std::find(boardLocations.begin(), boardLocations.end(), start) == boardLocations.end() ||
            std::find(boardLocations.begin(), boardLocations.end(), end) == boardLocations.end()) {
            ++attempts;
            if (attempts > 3) {
                cout << "Too many incorrect outputs... terminating program." << endl;
                exit(0);
            }
            return chooseMove(b);
        }
    }

    attempts = 0;

    Move move{posToInd[start], posToInd[end]};
    vector<Move> validMoves = possibleMoves(b);
    if (std::find(validMoves.begin(), validMoves.end(), move) == validMoves.end()) {
        ++attempts;
        if (attempts > 3) {
            cout << "Too many invalid moves... terminating program." << endl;
            exit(0);
        }
        cout << "ChatGPT valid move attempt #" << attempts << "..." << endl;
        return chooseMove(b);
    }

    return move;
}

vector<Move> L3::checkmateMoves() {
    // Implementation of getting checkmate moves for L3
    return {};
}

vector<Move> L3::avoidCaptureMoves() {
    // Implementation of getting avoid capture moves for L3
    return {};
}
