#pragma once
#include "NumberBag.h"
#include "BingoCard.h"
#include "WinCondition.h"
#include "GameResult.h"
#include <vector>
using namespace std;
//  BingoGame điều phối 1 ván chơi hoàn chỉnh.
//  Nối NumberBag + BingoCard + WinCondition thành 1 ván.
//  Trả về GameResult chứa đầy đủ thông tin cho
//  Statistics xử lý (heatmap, BCR, tài chính...).
// ══════════════════════════════════════════════════════
class BingoGame {
private:
    NumberBag             tui;
    vector<BingoCard> phieu;
    WinCondition          dieuKien;
    int                   soPhieu;

public:
    explicit BingoGame(int soPhieu);

    // Chạy 1 ván. verbose=true: in từng bước ra màn hình
    GameResult play(bool verbose = false);
};
