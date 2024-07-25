#ifndef L3_H
#define L3_H

#include "L2.h"

using namespace std;

class L3: public L2 {
    int attempts;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::string callChatGPT(const std::string& prompt, const std::string& apiKey);
  public:
    L3(bool);
    Move chooseMove(unique_ptr<Board>& b) override;
    vector<Move> checkmateMoves();
    vector<Move> avoidCaptureMoves();
};

#endif
