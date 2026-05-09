#include "Simulator.h"
#include <iostream>
#include <iomanip>
using namespace std;

Simulator::Simulator(int numGames, int numCards,
                     const PrizeCalculator& prize,
                     const SoCategory* cat,
                     double trongSo)
    : numGames(numGames), numCards(numCards),
      stats(numCards, prize), prize(prize),
      category(cat), trongSoNhom(trongSo)
{}

void Simulator::run(bool showProgress) {
    cout << "\n================================================\n";
    cout << "  BAT DAU MO PHONG " << numGames << " VAN LO TO\n";
    cout << "  So phieu   : " << numCards << "\n";
    cout << "  Gia ve     : " << fixed << setprecision(0)
         << prize.getTicketPrice() << " dong\n";
    cout << "  He so b    : " << prize.getBonusMultiplier()
         << "x   Giam: " << prize.getDecayPercent()
         << "% / " << prize.getDecayInterval() << " lan\n";

    if (category) {
        auto ds = category->laySoThuocNhom();
        cout << "  Nhom so    : " << category->tenNhom()
             << " (" << ds.size() << " so)"
             << " — trong so " << setprecision(2) << trongSoNhom << "x";
        cout << (trongSoNhom < 1.0 ? "  [BOC MUON]\n" : "  [BOC SOM]\n");

        cout << "  Danh sach  : ";
        for (int i = 0; i < (int)ds.size(); i++) {
            cout << ds[i];
            if (i < (int)ds.size() - 1) cout << " ";
            if ((i + 1) % 20 == 0 && i < (int)ds.size() - 1)
                cout << "\n             ";
        }
        cout << "\n";
    }
    cout << "================================================\n\n";

    BingoGame game(numCards);
    if (category)
        game.layTui().apDungNhom(category, trongSoNhom);

    int milestone = max(1, numGames / 20);
    for (int i = 0; i < numGames; i++) {
        GameResult result = game.play(false);
        result.totalCollected = prize.totalCollected(numCards);
        result.prizePaid      = prize.actualPrize(numCards, result.drawCount);
        result.houseProfit    = prize.houseProfit(numCards, result.drawCount);
        stats.record(result);

        if (showProgress && (i + 1) % milestone == 0) {
            int pct = (i + 1) * 100 / numGames;
            cout << "\r  Tien do: [";
            for (int b = 0; b < 20; b++) cout << (b < pct/5 ? "#" : ".");
            cout << "] " << setw(3) << pct << "%" << flush;
        }
    }
    cout << "\n  Hoan tat!\n";
}

void Simulator::printFrequencyTable()                  const { stats.printFrequencyTable(); }
void Simulator::exportFrequencyCSV(const string& fn)   const { stats.exportFrequencyCSV(fn); }
void Simulator::exportProfitCSV   (const string& fn)   const { stats.exportProfitCSV(fn); }
void Simulator::report()                               const { stats.printSummary(); }
