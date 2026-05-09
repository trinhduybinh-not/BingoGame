#pragma once
#include "NumberBag.h"
#include "BingoCard.h"
#include "WinCondition.h"
#include "GameResult.h"
#include <vector>
using namespace std;

class BingoGame {
private:
    NumberBag         tui;
    vector<BingoCard> phieu;
    WinCondition      dieuKien;
    int               soPhieu;

public:
    explicit BingoGame(int soPhieu);

    // Truy cập túi số để cấu hình trọng số từ bên ngoài
    NumberBag& layTui() { return tui; }

    GameResult play(bool verbose = false);
};
