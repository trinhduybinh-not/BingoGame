#include "WinCondition.h"
#include "BingoCard.h"
using namespace std;
// ─────────────────────────────────────────────
//  Kiểm tra thắng:
//  Hàng ngang hoặc cột dọc có đủ 5 ô đánh dấu
//  VÀ không chứa ô đặc biệt X
//
//  Lưu ý: ô X (bang = -1) không bao giờ được đánh dấu
//  nên dem <= 4 nếu X nằm trong hàng/cột đó.
//  Kiểm tra coX là bảo vệ tường minh, tránh edge case.
// ─────────────────────────────────────────────
bool WinCondition::Check(const BingoCard& card) const {
    // Kiểm tra hàng ngang
    for (int i = 0; i < 5; i++) {
        int  dem = 0;
        bool coX = false;
        for (int j = 0; j < 5; j++) {
            if (i == card.LayHangDacBiet() && j == card.LayCotDacBiet())
                coX = true;
            if (card.DaDanhDauChua(i, j)) dem++;
        }
        if (dem == 5 && !coX) return true;
    }
    // Kiểm tra cột dọc
    for (int j = 0; j < 5; j++) {
        int  dem = 0;
        bool coX = false;
        for (int i = 0; i < 5; i++) {
            if (i == card.LayHangDacBiet() && j == card.LayCotDacBiet())
                coX = true;
            if (card.DaDanhDauChua(i, j)) dem++;
        }
        if (dem == 5 && !coX) return true;
    }
    return false;
}

// ─────────────────────────────────────────────
//  Trả về toạ độ các ô trên đường thắng
// ─────────────────────────────────────────────
vector<pair<int,int>> WinCondition::LayOThang(const BingoCard& card) const {
    vector<pair<int,int>> ds;

    for (int i = 0; i < 5; i++) {
        int  dem = 0;
        bool coX = false;
        for (int j = 0; j < 5; j++) {
            if (i == card.LayHangDacBiet() && j == card.LayCotDacBiet()) coX = true;
            if (card.DaDanhDauChua(i, j)) dem++;
        }
        if (dem == 5 && !coX)
            for (int j = 0; j < 5; j++) ds.push_back({i, j});
    }
    for (int j = 0; j < 5; j++) {
        int  dem = 0;
        bool coX = false;
        for (int i = 0; i < 5; i++) {
            if (i == card.LayHangDacBiet() && j == card.LayCotDacBiet()) coX = true;
            if (card.DaDanhDauChua(i, j)) dem++;
        }
        if (dem == 5 && !coX)
            for (int i = 0; i < 5; i++) ds.push_back({i, j});
    }
    return ds;
}
