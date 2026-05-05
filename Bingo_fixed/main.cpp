#include <iostream>
#include "Simulator.h"
#include "PrizeCalculator.h"
#include "GridSearch.h"
#include "BingoGame.h"
#include "WinCondition.h"
using namespace std;
static void printMenu() {
    cout << "\nChon che do:\n";
    cout << "  1. Mo phong 1 bo tham so (xem ket qua chi tiet)\n";
    cout << "  2. Grid Search (quet nhieu tham so, xuat CSV)\n";
    cout << "Lua chon (1/2): ";
}

static void runNormal() {
    int numGames, numCards;
    cout << "\nSo van mo phong (VD: 10000): "; cin >> numGames;
    cout << "So phieu moi van  (VD: 4)  : "; cin >> numCards;

    double n, b, x; int k;
    cout << "\n--- THONG SO TAI CHINH ---\n";
    cout << "Gia ve n (VD: 10000): "; cin >> n;
    cout << "He so thuong b       : "; cin >> b;
    cout << "Giam thuong x%       : "; cin >> x;
    cout << "Giam moi k lan       : "; cin >> k;

    char demo;
    cout << "\nXem demo 1 van? (y/n): "; cin >> demo;
    if (demo == 'y' || demo == 'Y') {
        cout << "\n--- DEMO 1 VAN ---\n";
        BingoGame g(numCards);
        g.play(true);
    }

    PrizeCalculator prize(n, b, x, k);
    Simulator sim(numGames, numCards, prize);
    sim.run();
    sim.printFrequencyTable();
    sim.report();
}

static void runGridSearch() {
    int numCards; double n;
    cout << "\nSo phieu moi van (VD: 4)    : "; cin >> numCards;
    cout << "Gia ve n (VD: 10000)        : "; cin >> n;
    cout << "So van moi to hop (VD: 2000): ";
    int simPerPoint; cin >> simPerPoint;

    double bMin, bMax, bStep;
    cout << "\n-- Dai b --\n";
    cout << "  b tu (VD: 0.3)  : "; cin >> bMin;
    cout << "  b den (VD: 1.2) : "; cin >> bMax;
    cout << "  b buoc (VD: 0.05): "; cin >> bStep;

    double xMin, xMax, xStep;
    cout << "\n-- Dai x% --\n";
    cout << "  x tu (VD: 1) : "; cin >> xMin;
    cout << "  x den (VD: 15): "; cin >> xMax;
    cout << "  x buoc (VD: 2): "; cin >> xStep;

    cout << "\n-- Gia tri k (nhap, -1 de ket thuc) --\n  k = ";
    vector<int> kVals;
    int kv;
    while (cin >> kv && kv != -1) kVals.push_back(kv);
    if (kVals.empty()) kVals = {5, 10, 15};

    string csvFile = "grid_result.csv";
    cout << "\nTen file CSV (Enter = grid_result.csv): ";
    cin.ignore();
    string inp; getline(cin, inp);
    if (!inp.empty()) csvFile = inp;

    GridSearch gs(simPerPoint, numCards, n);
    auto results = gs.run(bMin, bMax, bStep, xMin, xMax, xStep, kVals);
    GridSearch::exportCSV(results, csvFile);
    GridSearch::printSummary(results);
}

int main() {
    cout << "============================================\n";
    cout << "   MO PHONG LO TO — OOP C++\n";
    cout << "   Bang 5x5: 24 so + 1 o dac biet X\n";
    cout << "   Thang: hang ngang hoac cot doc\n";
    cout << "   (hang/cot chua X khong tinh Bingo)\n";
    cout << "============================================\n";

    printMenu();
    int choice; cin >> choice;
    if (choice == 2) runGridSearch();
    else             runNormal();
    return 0;
}
