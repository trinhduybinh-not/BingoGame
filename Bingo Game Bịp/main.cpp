#include <iostream>
#include <memory>
#include "Simulator.h"
#include "PrizeCalculator.h"
#include "GridSearch.h"
#include "BingoGame.h"
#include "SoCategory.h"
using namespace std;


static unique_ptr<SoCategory> chonNhomSo(double& trongSoOut) {
    char c;
    cout << "\nAp dung trong so theo nhom so? (y/n): "; cin >> c;
    if (c != 'y' && c != 'Y') return nullptr;

    cout << "\nChon nhom so:\n";
    cout << "  1. So nguyen to     (2,3,5,...,97)     25 so\n";
    cout << "  2. So doi xung      (11,22,...,99)      9 so\n";
    cout << "  3. So chan          (2,4,...,98)        49 so\n";
    cout << "  4. So le            (1,3,...,99)        50 so\n";
    cout << "  5. So chia het 5    (5,10,...,95)       19 so\n";
    cout << "  6. So Fibonacci     (1,2,3,5,...,89)   11 so\n";
    cout << "  7. So chinh phuong  (1,4,9,...,81)      9 so\n";
    cout << "  8. So chia het 7    (7,14,...,98)       14 so\n";
    cout << "  9. Tu chon dai so\n";
    cout << "Lua chon (1-9): ";

    int choice; cin >> choice;

    unique_ptr<SoCategory> cat;
    switch (choice) {
        case 1: cat = make_unique<SoNguyenTo>();    break;
        case 2: cat = make_unique<SoDoiXung>();     break;
        case 3: cat = make_unique<SoChan>();        break;
        case 4: cat = make_unique<SoLe>();          break;
        case 5: cat = make_unique<SoChiaHet5>();    break;
        case 6: cat = make_unique<SoFibonacci>();   break;
        case 7: cat = make_unique<SoChinhPhuong>(); break;
        case 8: cat = make_unique<SoChiaHet7>();    break;
        default: {
            int s, e;
            cout << "  So bat dau: "; cin >> s;
            cout << "  So ket thuc: "; cin >> e;
            cat = make_unique<SoTuyChon>(s, e);
            break;
        }
    }

    // Hiển thị danh sách số bị ảnh hưởng
    auto ds = cat->laySoThuocNhom();
    cout << "\n  Nhom \"" << cat->tenNhom() << "\" gom " << ds.size() << " so:\n  ";
    for (int i = 0; i < (int)ds.size(); i++) {
        cout << ds[i];
        if (i < (int)ds.size() - 1) cout << " ";
        if ((i + 1) % 20 == 0) cout << "\n  ";
    }
    cout << "\n";

    cout << "\nTrong so:\n";
    cout << "  0.1-0.5 : Nhom nay boc MUON → nguoi choi kho bingo\n";
    cout << "  0.5-0.9 : Nhom nay boc hoi muon\n";
    cout << "  2.0-5.0 : Nhom nay boc SOM → nguoi choi de bingo\n";
    cout << "  Trong so: ";
    cin >> trongSoOut;

    return cat;
}

static void printMenu() {
    cout << "\nChon che do:\n";
    cout << "  1. Mo phong 1 bo tham so\n";
    cout << "  2. Grid Search (xuat grid_result.csv)\n";
    cout << "Lua chon: ";
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

    double trongSo = 1.0;
    auto cat = chonNhomSo(trongSo);  // unique_ptr<SoCategory>

    // Tên file CSV tần suất
    string freqFile = "so_xuat_hien.csv";
    cout << "\n--- FILE CSV XUAT RA ---\n";
    cin.ignore();
    cout << "File tan suat so (Enter = so_xuat_hien.csv): ";
    string inp; getline(cin, inp); if (!inp.empty()) freqFile = inp;

    char demo;
    cout << "\nXem demo 1 van? (y/n): "; cin >> demo;
    if (demo == 'y' || demo == 'Y') {
        cout << "\n--- DEMO 1 VAN ---\n";
        BingoGame g(numCards);
        if (cat) g.layTui().apDungNhom(cat.get(), trongSo);
        g.play(true);
    }

    PrizeCalculator prize(n, b, x, k);
    Simulator sim(numGames, numCards, prize, cat.get(), trongSo);
    sim.run();
    sim.report();

    cout << "\n--- XUAT FILE CSV ---\n";
    sim.exportFrequencyCSV(freqFile);
}

static void runGridSearch() {
    int numCards; double n;
    cout << "\nSo phieu moi van (VD: 4)    : "; cin >> numCards;
    cout << "Gia ve n (VD: 10000)        : "; cin >> n;
    cout << "So van moi to hop (VD: 2000): ";
    int simPerPoint; cin >> simPerPoint;

    double bMin, bMax, bStep;
    cout << "\n-- Dai b --\n";
    cout << "  b tu   : "; cin >> bMin;
    cout << "  b den  : "; cin >> bMax;
    cout << "  b buoc : "; cin >> bStep;

    double xMin, xMax, xStep;
    cout << "\n-- Dai x% --\n";
    cout << "  x tu   : "; cin >> xMin;
    cout << "  x den  : "; cin >> xMax;
    cout << "  x buoc : "; cin >> xStep;

    cout << "\n-- Gia tri k (-1 de ket thuc) -- k = ";
    vector<int> kVals; int kv;
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
    cout << "============================================\n";
    printMenu();
    int choice; cin >> choice;
    if (choice == 2) runGridSearch();
    else             runNormal();
    return 0;
}
