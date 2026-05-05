#include "GridSearch.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;
GridSearch::GridSearch(int numGames, int numCards, double ticketPrice)
    : numGames(numGames), numCards(numCards), ticketPrice(ticketPrice)
{}

// ─────────────────────────────────────────────
//  Chạy nhanh numGames ván với tổ hợp (b, x, k)
// ─────────────────────────────────────────────
GridPoint GridSearch::runOne(double b, double x, int k) const {
    PrizeCalculator prize(ticketPrice, b, x, k);
    BingoGame        game(numCards);

    double totalProfit = 0;
    double minP =  1e18;
    double maxP = -1e18;
    int    lossVans = 0;

    for (int i = 0; i < numGames; i++) {
        GameResult r = game.play(false);
        double profit = prize.houseProfit(numCards, r.drawCount);
        totalProfit += profit;
        if (profit < minP) minP = profit;
        if (profit > maxP) maxP = profit;
        if (profit < 0)    lossVans++;
    }

    double revenue    = prize.totalCollected(numCards) * numGames;
    double avgP       = totalProfit / numGames;
    double profitRate = (revenue > 0) ? (totalProfit / revenue * 100.0) : 0.0;
    double lossRate   = 100.0 * lossVans / numGames;

    // Phân vùng
    string zone;
    if (minP > 0)       zone = "LUON LOI";
    else if (maxP < 0)  zone = "LUON LO";
    else                zone = "TRUNG GIAN";

    return { b, x, k, avgP, minP, maxP, profitRate, lossRate, zone };
}

// ─────────────────────────────────────────────
//  Quét toàn bộ tổ hợp
// ─────────────────────────────────────────────
vector<GridPoint> GridSearch::run(
    double bMin, double bMax, double bStep,
    double xMin, double xMax, double xStep,
    vector<int> kValues) const
{
    vector<GridPoint> results;

    // Đếm tổng số tổ hợp để hiển thị tiến độ
    int bSteps = (int)round((bMax - bMin) / bStep) + 1;
    int xSteps = (int)round((xMax - xMin) / xStep) + 1;
    int total  = bSteps * xSteps * (int)kValues.size();
    int done   = 0;

    cout << "\n  Dang quet " << total << " to hop tham so...\n";

    for (double b = bMin; b <= bMax + 1e-9; b += bStep)
    for (double x = xMin; x <= xMax + 1e-9; x += xStep)
    for (int    k : kValues) {
        results.push_back(runOne(
            round(b * 100) / 100,   // làm tròn tránh float noise
            round(x * 10)  / 10,
            k
        ));
        done++;
        // Thanh tiến độ đơn giản
        int pct = done * 100 / total;
        cout << "\r  [";
        for (int p = 0; p < 20; p++)
            cout << (p < pct/5 ? "#" : ".");
        cout << "] " << setw(3) << pct << "% ("
                  << done << "/" << total << ")" << flush;
    }
    cout << "\n  Hoan tat!\n";
    return results;
}

// ─────────────────────────────────────────────
//  Xuất CSV
//  Cột: b, x, k, avgProfit, minProfit, maxProfit,
//       profitRate, lossRate, zone
// ─────────────────────────────────────────────
void GridSearch::exportCSV(const vector<GridPoint>& results,
                           const string& filename) {
    ofstream f(filename);
    if (!f.is_open()) {
        cerr << "Khong mo duoc file: " << filename << "\n";
        return;
    }

    // Header
    f << "b,x,k,avgProfit,minProfit,maxProfit,profitRate,lossRate,zone\n";

    f << fixed << setprecision(4);
    for (auto& p : results) {
        f << p.b        << ","
          << p.x        << ","
          << p.k        << ","
          << p.avgProfit << ","
          << p.minProfit << ","
          << p.maxProfit << ","
          << p.profitRate << ","
          << p.lossRate  << ","
          << p.zone      << "\n";
    }
    f.close();
    cout << "  Da xuat CSV: " << filename << "\n";
}

// ─────────────────────────────────────────────
//  In tóm tắt số lượng từng vùng
// ─────────────────────────────────────────────
void GridSearch::printSummary(const vector<GridPoint>& results) {
    int luonLoi = 0, luonLo = 0, trungGian = 0;
    double bestRate = -1e18;
    GridPoint bestPoint{};

    for (auto& p : results) {
        if      (p.zone == "LUON LOI")    luonLoi++;
        else if (p.zone == "LUON LO")     luonLo++;
        else                              trungGian++;

        if (p.zone == "LUON LOI" && p.profitRate > bestRate) {
            bestRate  = p.profitRate;
            bestPoint = p;
        }
    }

    int total = (int)results.size();
    cout << "\n================================================\n";
    cout << "  KET QUA GRID SEARCH — " << total << " TO HOP\n";
    cout << "================================================\n";
    cout << fixed << setprecision(1);
    cout << "  [LUON LOI]    : " << setw(5) << luonLoi
              << " to hop (" << (100.0 * luonLoi    / total) << "%)\n";
    cout << "  [TRUNG GIAN]  : " << setw(5) << trungGian
              << " to hop (" << (100.0 * trungGian / total) << "%)\n";
    cout << "  [LUON LO]     : " << setw(5) << luonLo
              << " to hop (" << (100.0 * luonLo    / total) << "%)\n";
    cout << "================================================\n";

    if (luonLoi > 0) {
        cout << "\n  To hop LOI NHUAN CAO NHAT trong vung LUON LOI:\n";
        cout << "    b = " << setprecision(2) << bestPoint.b
                  << ",  x = " << bestPoint.x << "%"
                  << ",  k = " << bestPoint.k << "\n";
        cout << "    Ti suat loi nhuan trung binh : "
                  << setprecision(1) << bestPoint.profitRate << "%\n";
        cout << "    Loi nhuan thap nhat / van    : "
                  << setprecision(0) << bestPoint.minProfit << " dong\n";
    }
    cout << "================================================\n";
    cout << "  (Xem file CSV de ve bieu do chi tiet)\n";
}
