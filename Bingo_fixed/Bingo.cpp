#include "BingoCard.h"
#include "WinCondition.h"
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;
BingoCard::BingoCard(int maSo) : MaSo(maSo) {
    DatLai();
}

void BingoCard::DatLai() {
    DSS.clear();
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            DaDanhDau[i][j] = false;
    TaoBang();
}

void BingoCard::TaoBang() {
    // Bước 1: chuẩn bị pool 1–99 và lấy 24 số ngẫu nhiên
    vector<int> temp;
    for (int i = 1; i <= 99; i++) temp.push_back(i);
    random_device rd;
    mt19937 g(rd());
    shuffle(temp.begin(), temp.end(), g);
    DSS.assign(temp.begin(), temp.begin() + 24);

    // Bước 2: chọn ô trống ban đầu
    uniform_int_distribution<int> dist(0, 4);
    HangTrong = dist(g);
    CotTrong  = dist(g);

    // Bước 3: điền 24 số vào bảng, bỏ trống 1 ô
    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            bang[i][j] = (i == HangTrong && j == CotTrong) ? 0 : DSS[k++];

    // Bước 4: chọn vị trí ô đặc biệt X ngẫu nhiên
    HangDB = dist(g);
    CotDB  = dist(g);

    // Nếu X trùng ô có số → chuyển số đó sang ô trống, rồi đặt X
    if (!(HangDB == HangTrong && CotDB == CotTrong)) {
        bang[HangTrong][CotTrong] = bang[HangDB][CotDB]; // di chuyển số
    }
    bang[HangDB][CotDB] = -1; // đặt X
}

bool BingoCard::DanhDau(int so) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (bang[i][j] == so) {
                DaDanhDau[i][j] = true;
                return true;
            }
    return false;
}

bool BingoCard::KiemTraThang(const WinCondition& dk) const {
    return dk.Check(*this);
}

void BingoCard::HienThi(const WinCondition& dk) const {
    auto OThang = dk.LayOThang(*this);
    cout << "\n=== PHIEU BINGO SO: " << MaSo << " ===\n";
    cout << "      [0]   [1]   [2]   [3]   [4]\n";
    for (int i = 0; i < 5; i++) {
        cout << "  [" << i << "]";
        for (int j = 0; j < 5; j++) {
            // Kiểm tra ô này có trên đường thắng không
            bool laOThang = false;
            for (auto& p : OThang)
                if (p.first == i && p.second == j) { laOThang = true; break; }

            if (i == HangDB && j == CotDB)
                cout << "    X ";               // ô đặc biệt
            else if (laOThang)
                cout << "  [" << bang[i][j] << "]"; // ô thắng
            else if (DaDanhDau[i][j])
                cout << "  " << bang[i][j] << "* "; // đã đánh dấu
            else if (bang[i][j] == -1)
                cout << "    . ";               // trống (không nên xảy ra)
            else
                cout << "   " << bang[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "  (O dac biet X tai: hang " << HangDB << ", cot " << CotDB << ")\n";
}
