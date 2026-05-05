#include "Simulator.h"
#include <iostream>
#include <iomanip>
using namespace std;
Simulator::Simulator(int numGames, int numCards, const PrizeCalculator& prize)
    : numGames(numGames), numCards(numCards), stats(numCards, prize), prize(prize)
{}

void Simulator::run(bool showProgress) {
    cout << "\n================================================\n";
    cout << "  BAT DAU MO PHONG " << numGames << " VAN LO TO\n";
    cout << "  Luat thang : Hang ngang / Cot doc\n";
    cout << "  So phieu   : " << numCards << "\n";
    cout << "  Gia ve     : " << fixed << setprecision(0)
              << prize.getTicketPrice() << " dong\n";
    cout << "  He so thuong (b): " << prize.getBonusMultiplier() << "x\n";
    cout << "  Giam thuong : " << prize.getDecayPercent()
              << "% moi " << prize.getDecayInterval() << " lan boc\n";
    cout << "================================================\n\n";

    BingoGame game(numCards);
    int milestone = max(1, numGames / 20);

    for (int i = 0; i < numGames; i++) {
        GameResult result = game.play(false);

        // Tính tài chính và gắn vào result
        result.totalCollected = prize.totalCollected(numCards);
        result.prizePaid      = prize.actualPrize(numCards, result.drawCount);
        result.houseProfit    = prize.houseProfit(numCards, result.drawCount);

        stats.record(result);

        if (showProgress && (i + 1) % milestone == 0) {
            int pct    = (i + 1) * 100 / numGames;
            int filled = pct / 5;
            cout << "\r  Tien do: [";
            for (int b = 0; b < 20; b++)
                cout << (b < filled ? "#" : ".");
            cout << "] " << setw(3) << pct << "%" << flush;
        }
    }
    cout << "\n  Hoan tat!\n";
}

void Simulator::printFrequencyTable() const { stats.printFrequencyTable(); }
void Simulator::report()              const { stats.printSummary(); }
