#pragma once
#include "BingoGame.h"
#include "Statistics.h"
#include "PrizeCalculator.h"

// ══════════════════════════════════════════════════════
//  Simulator nhận thêm PrizeCalculator để tính tiền
//  sau mỗi ván và truyền vào Statistics thống kê.
// ══════════════════════════════════════════════════════
class Simulator {
private:
    int              numGames;
    int              numCards;
    Statistics       stats;
    PrizeCalculator  prize;  // đóng gói logic tài chính

public:
    Simulator(int numGames, int numCards, const PrizeCalculator& prize);

    void run(bool showProgress = true);
    void printFrequencyTable() const;
    void report()              const;
};
