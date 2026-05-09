#pragma once
#include "BingoGame.h"
#include "Statistics.h"
#include "PrizeCalculator.h"
#include "SoCategory.h"
#include <string>
using namespace std;

class Simulator {
private:
    int              numGames;
    int              numCards;
    Statistics       stats;
    PrizeCalculator  prize;
    const SoCategory* category;   // nullptr = không dùng nhóm
    double           trongSoNhom;

public:
    Simulator(int numGames, int numCards,
              const PrizeCalculator& prize,
              const SoCategory* cat    = nullptr,
              double            trongSo = 1.0);

    void run(bool showProgress = true);
    void printFrequencyTable()                      const;
    void exportFrequencyCSV(const string& filename) const;
    void exportProfitCSV   (const string& filename) const;
    void report()                                   const;
};
