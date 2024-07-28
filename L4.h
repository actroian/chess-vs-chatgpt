#ifndef L4_H
#define L4_H

#include "L3.h"

using namespace std;

class L4: public L3 {
    int attempts;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::string callChatGPT(const std::string& prompt, const std::string& apiKey);
  public:
    L4(bool);
    unique_ptr<Move> chooseMove(unique_ptr<Board>& b) override;
    vector<unique_ptr<Move>> checkmateMoves();
    vector<unique_ptr<Move>> avoidCaptureMoves();
};

#endif
